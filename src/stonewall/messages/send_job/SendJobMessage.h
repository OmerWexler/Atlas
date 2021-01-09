#pragma once

#include "IMessage.h"
#include "IJob.h"
#include "Argument.h"

using namespace std;

class SendJobMessage: public IMessage
{
private:
    IJob* Job;
    vector<Argument> Input;
    vector<Argument> Output;

public:
    inline SendJobMessage(IJob* Job, vector<Argument> Input)
    {
        this->Job = Job;
        this->Input = Input;
    }

    inline SendJobMessage(IJob* Job, vector<Argument> Input, vector<Argument> Output)
    {
        this->Job = Job;
        this->Input = Input;
        this->Output = Output;
    }

    inline string GetType() const override
    {
        return "SendJob";
    };

    inline IJob* GetJob() const
    {
        return Job;
    };

    inline vector<Argument> GetInput() const
    {
        return Input;
    };

    inline void SetOutput(vector<Argument> Output)
    {
        this->Output = Output;
    };

    inline vector<Argument> GetOutput() const
    {
        return Output;
    };

    inline ~SendJobMessage()
    {
        delete Job;
    }
};