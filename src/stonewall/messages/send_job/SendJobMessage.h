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
    const static string TYPE;

    SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input);
    SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output);
    string GetType() const override;
    shared_ptr<IJob>& GetJob();
    vector<Argument> GetInput() const;
    void SetOutput(vector<Argument> Output);
    vector<Argument> GetOutput() const;
};