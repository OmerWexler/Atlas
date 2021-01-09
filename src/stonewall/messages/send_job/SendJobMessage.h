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

public:
    inline SendJobMessage(IJob* Job, vector<Argument> Input)
    {
        this->Job = Job;
        this->Input = Input;
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

    inline ~SendJobMessage()
    {
        delete Job;
    }
};