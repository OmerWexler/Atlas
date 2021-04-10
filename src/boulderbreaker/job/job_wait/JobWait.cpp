#pragma once

#include "JobWait.h"

#include "AtlasApp.h"
#include "MainFrame.h"

#include "wx/xrc/xmlres.h"

string JobWait::GetType() const
{
    return "JobWait";
}

void JobWait::Execute(vector<Argument>& Input)
{
    m_IsAlive = true;
    float TimeToRun = stof(Input[0].Value.c_str());

    float TimeDone = 0.f;
    while (m_IsAlive && TimeDone < TimeToRun)
    {
        Utils::CPSleep(0.1f);
        TimeDone += 0.1f;
    }

    if (TimeDone >= TimeToRun)
    {
        Output.push_back(Argument("Finished cleanly"));
    }

    m_IsAlive = false;
    m_IsDone = true;
}

int JobWait::Kill()
{
    Output.push_back(Argument("Was killed.txt", true));
    m_IsAlive = false;
    m_IsDone = true;
    
    return 0;
}