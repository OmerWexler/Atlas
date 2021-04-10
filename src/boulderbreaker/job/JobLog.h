#pragma once

#include "Utils.h"
#include "IJob.h"
#include "Logger.h"

using namespace std;

class JobLog: public IJob
{
private:
    int Success;
    string UniqueDescriptor;
    vector<Argument> Output;

public:
    string GetType() const
    {
        return "JobLog";
    }
    
    void Execute(vector<Argument>& Inputs)
    {
        Output = vector<Argument>();

        for (Argument Input: Inputs)
        {
            Singleton<Logger>::GetInstance().Info(Input.Value);
            Output.push_back(Input);
        }

        Success = 0;
    }
    
    bool IsInputValid(vector<Argument>& Inputs)
    {
        return true;
    }

    int Kill()
    {
        return 0;
    }

    bool IsAlive()
    {
        return false;
    }

    IJob* Clone()
    {
        return (IJob*) DBG_NEW JobLog();
    }

    ~JobLog() {};
};