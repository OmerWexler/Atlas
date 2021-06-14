#pragma once

#define MAX_PATH_SIZE 1024
#define SYSTEM_PATH_SEP ';'

#include "JobSubprocess.h"
#include "windows.h"

#include <filesystem>
#include <cstdlib>

namespace fs = std::experimental::filesystem;

string JobSubprocess::GetType() const
{
    return "JobSubprocess";
}

bool JobSubprocess::IsInputValid(vector<Argument>& Input)
{
    return Input.size() >= 1;
}

string JobSubprocess::ProcessFileType(string ModuleName) 
{
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
    
    return "";
}

void JobSubprocess::Execute(vector<Argument>& Input)
{
    string Args = "";
    string OutFileName = UniqueDescriptor + ".txt";
    string Module = ProcessFileType(Input[0].Value);


    if (fs::path(Module).extension().string() == ".py")
    {
        Args = Module + " ";
        Module = "python";
    }

    Module = FindModule(Module);

    for (int i = 1; i < Input.size(); i++)
        Args += " " + Input[i].Value;
    
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