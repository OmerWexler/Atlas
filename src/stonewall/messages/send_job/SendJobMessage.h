#pragma once

#include <memory>

#include "IMessage.h"
#include "IJob.h"
#include "Argument.h"

using namespace std;

class SendJobMessage: public IMessage
{
private:
    shared_ptr<IJob> Job;
    vector<Argument> Input;
    vector<Argument> Output;

public:
    inline SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input)
    {
        this->Job = Job;
        this->Input = Input;
    }

    inline SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output)
    {
        this->Job = Job;
        this->Input = Input;
        this->Output = Output;
    }

    inline string GetType() const override
    {
        return "SendJob";
    };

    inline shared_ptr<IJob>& GetJob()
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
};