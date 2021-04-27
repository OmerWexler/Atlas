#pragma once

#include <memory>

#include "IMessage.h"
#include "IJob.h"
#include "Argument.h"
#include "Path.h"

using namespace std;

class SendJobMessage: public IMessage
{
private:
    Path PathToTarget;
    shared_ptr<IJob> Job;
    vector<Argument> Input;
    vector<Argument> Output;

public:
    const static string TYPE;

    SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, Path PathToTarget);
    SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, vector<Argument>& Output);
    SendJobMessage(shared_ptr<IJob>& Job, vector<Argument>& Input, Path PathToTarget, vector<Argument>& Output);
    string GetType() const override;
    shared_ptr<IJob>& GetJob();
    
    vector<Argument> GetInput() const;

    void SetOutput(vector<Argument> Output);
    vector<Argument> GetOutput() const;

    void SetPathToTarget(string Path);
    Path& GetPathToTarget();

    void SetSourcePath(string Path);
    Path& GetSourcePath();
};