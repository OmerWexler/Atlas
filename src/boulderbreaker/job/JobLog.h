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
    JobLog() {};
    ~JobLog() {};
    int GetType() const
    {
        return 0;
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

    int Kill()
    {
        return 0;
    }

    bool IsAlive()
    {
        return false;
    }

    int GetSuccess() const
    {
        return Success;
    }

    void SetSuccess(int Success)
    {
        this->Success = Success;
    }

    string GetUniqueDescriptor() const
    {
        return UniqueDescriptor;
    }

    void SetUniqueDescriptor(string UniqueDescriptor)
    {
        this->UniqueDescriptor = UniqueDescriptor;
    }

    vector<Argument> GetOutput() const
    {
        return Output;
    }

    IJob* Clone()
    {
        return (IJob*) DBG_NEW JobLog();
    }
};