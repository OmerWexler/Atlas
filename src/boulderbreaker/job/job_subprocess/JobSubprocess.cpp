#pragma once

#include "JobSubprocess.h"

string JobSubprocess::GetType() const
{
    return "JobSubprocess";
}

bool JobSubprocess::IsInputValid(vector<Argument>& Input)
{
    return true;
}

void JobSubprocess::Execute(vector<Argument>& Input)
{
    string Module = Input[0].Value;
    string OutFileName = Input[1].Value;

    string Args = "";
    for (int i = 2; i < Input.size(); i++)
        Args += " " + Input[i].Value;

    SP.Create("Remote Job - JobSubprocess", Input[0].Value, Args);
    int Result = SP.RedirectOutput(OutFileName);

    if (Result != 0)
        Output.push_back("Error: Couldn't open output file - " + OutFileName);

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
        m_IsAlive = true;
    }
}

int JobSubprocess::Kill()
{
    if (SP.IsAlive())
    {
        SP.Kill();
    }
    m_IsDone = true;

    return 0;
}