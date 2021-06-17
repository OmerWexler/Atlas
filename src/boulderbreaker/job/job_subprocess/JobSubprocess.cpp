#pragma once

#define MAX_PATH_SIZE 1024
#define SYSTEM_PATH_SEP ';'

#include "JobSubprocess.h"
#include "Singleton.h"
#include "GridNode.h"
#include "FileCore.h"
#include "windows.h"

#include <filesystem>
#include <cstdlib>

namespace fs = std::experimental::filesystem;

const string JobSubprocess::ARG_OVERRIDE_FILE = "-oif";
const string JobSubprocess::ARG_SEND_FILE = "-sif";

string JobSubprocess::GetType() const
{
    return "Job Subprocess";
}

bool JobSubprocess::IsInputValid(vector<Argument>& Input)
{
    return Input.size() >= 1;
}

string JobSubprocess::ProcessFileType(string ModuleName) 
{
    string Filename;
    if (ModuleName.substr(0, ARG_OVERRIDE_FILE.length()) == ARG_OVERRIDE_FILE)
    {
        Filename = ModuleName.substr(ARG_OVERRIDE_FILE.length() + 1);
        ModuleName = UniqueDescriptor + "\\" + fs::path(Filename).filename().string();
    }

    if (ModuleName.substr(0, ARG_SEND_FILE.length()) == ARG_SEND_FILE)
    {
        Filename = ModuleName.substr(ARG_SEND_FILE.length() + 1);
        ModuleName = Filename;
    }

    if (fs::path(ModuleName).extension().string() == ".exe")
        return ModuleName;
    
    if (fs::path(ModuleName).extension().string() == ".py")
        return ModuleName;

    return ModuleName + ".exe";
}

string JobSubprocess::FindModule(string ModuleName) 
{
    string Basename = fs::path(ModuleName).filename().string();

    // Check if runnable
    if (Utils::FileExists(ModuleName))
    {
        Output.push_back(Argument("Module was found in local Atlas folder.", false));
        return ModuleName;
    }

    // Check if in PATH
    string PATH = string(std::getenv("PATH"));
    vector<string> PathList = vector<string>();
    
    int NextIndex;
    string Dir;
    while (PATH.size() > 0)
    {
        NextIndex = PATH.find(SYSTEM_PATH_SEP);

        if (NextIndex < PATH.size() - 1 && NextIndex > 0)
        {
            Dir = PATH.substr(0, NextIndex);
            PATH = PATH.substr(NextIndex + 1);

            for(auto& p: fs::directory_iterator(Dir))
            {
                if (p.path().filename() == Basename)
                {
                    Output.push_back(Argument("Module was found in system PATH.", false));
                    return p.path().string();
                }
            }
        } 
        else 
        {
            break;
        }
    }

    // Check local cache
    if (Utils::FileExists(UniqueDescriptor + "\\" + Basename))
    {
        Output.push_back(Argument("Module was found in local Atlas cache.", false));
        return UniqueDescriptor + "\\" + Basename;
    }
    
    return "";
}

void JobSubprocess::PrepareJobToSend(vector<Argument>& Input)
{
    for (int i = 0; i < Input.size(); i++)
    {
        bool ShouldSendFile = false;
        string Filename;
        
        Argument Arg = Input[i];

        if (Arg.Value.substr(0, ARG_OVERRIDE_FILE.length()) == ARG_OVERRIDE_FILE)
        {
            Filename = Arg.Value.substr(ARG_OVERRIDE_FILE.length() + 1);

            if (i == 0) // Executeable
            {
                Filename = ProcessFileType(Filename);
            }

            Filename = FindModule(Filename);
            ShouldSendFile = true;
        }

        if (Arg.Value.substr(0, ARG_SEND_FILE.length()) == ARG_SEND_FILE)
        {
            Filename = Arg.Value.substr(ARG_SEND_FILE.length() + 1);

            if (i == 0) // Executeable
            {
                Filename = ProcessFileType(Filename);
            }

            Filename = FindModule(Filename);
            ShouldSendFile = true;
        }

        if (ShouldSendFile)
        {
            int Result = Singleton<GridNode>::GetInstance().SendFile(Filename, UniqueDescriptor + "\\" + fs::path(Filename).filename().string(), PathToTarget);
            if (Result != 0)
                Output.push_back(Argument("Error: Couldn't open input file - " + Filename, false));
        }
    }
}

string JobSubprocess::ParseArg(string Arg)
{
    string Filename;
    if (Arg.substr(0, ARG_OVERRIDE_FILE.length()) == ARG_OVERRIDE_FILE)
    {
        Filename = Arg.substr(ARG_OVERRIDE_FILE.length());
        return UniqueDescriptor + "\\" + fs::path(Filename).filename().string();
    }

    if (Arg.substr(0, ARG_SEND_FILE.length()) == ARG_SEND_FILE)
    {
        Filename = Arg.substr(ARG_SEND_FILE.length() + 1);
        return Filename;
    }

    return Arg;
}

void JobSubprocess::Execute(vector<Argument>& Input)
{
    string Args = "";
    string OutFileName = UniqueDescriptor + "\\OutputStream.txt";
    string Module = ProcessFileType(Input[0].Value);

    if (fs::path(Module).extension().string() == ".py")
    {
        Args = Module + " ";
        Module = "python";
    }

    Module = FindModule(Module);

    for (int i = 1; i < Input.size(); i++)
        Args += " " + ParseArg(Input[i].Value);
    
    SP.Create("Remote Job - JobSubprocess", Module, Args);
    int Result = SP.RedirectOutput(OutFileName);

    if (Result != 0)
        Output.push_back(Argument("Error: Couldn't open output file - " + OutFileName, false));
    else
        Output.push_back(Argument("Output file at - \"" + OutFileName + "\"", true));

    Success = SP.Run();

    if (Success != 0)
    {
        if (Success == 2)
            Output.push_back(Argument("Module \"" + Module + "\" could not be found...", false));
        
        m_IsDone = true;
        m_IsAlive = false;
    }
    else 
    {
        Output.push_back(Argument("Subprocess is now running...", false));
        m_IsAlive = true;
    }
}

bool JobSubprocess::IsDone()
{
    return SP.IsDone() || m_IsDone;
}

int JobSubprocess::Kill()
{
    if (SP.IsAlive())
    {
        SP.Kill();
        Output.push_back(Argument("Subprocess was forcefully killed.", false));
    }
    m_IsDone = true;

    return 0;
}