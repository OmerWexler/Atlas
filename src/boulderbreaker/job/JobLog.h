#pragma once

#include "IJob.h"
#include "Logger.h"

using namespace std;

class JobLog: public IJob
{
private:
    int Success;
    string UniqueDescriptor;

public:
    JobLog() {};
    ~JobLog() {};
    int GetType() const
    {
        return 0;
    }
    
    vector<Argument> Execute(vector<Argument>& Inputs)
    {
        vector<Argument> Output = vector<Argument>();

        for (Argument Input: Inputs)
        {
            Singleton<Logger>::GetInstance().Info(Input.Value);
            Output.push_back(Input);
        }

        Success = 0;
        return Output;
    }

    int Kill()
    {
        return 0;
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

    IJob* Clone()
    {
        return (IJob*) new JobLog();
    }
};