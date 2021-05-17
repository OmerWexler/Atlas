#pragma once

#include "JobWait.h"

string JobWait::GetType() const
{
    return "JobWait";
}

bool IsNumber(const string& s)
{
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

bool JobWait::IsInputValid(vector<Argument>& Input)
{
    if (Input.size() != 1)
        return false;

    if (!IsNumber(Input[0].Value))
        return false;
    
    return true;
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
    Output.push_back(Argument("Was killed", false));
    m_IsAlive = false;
    m_IsDone = true;
    
    return 0;
}