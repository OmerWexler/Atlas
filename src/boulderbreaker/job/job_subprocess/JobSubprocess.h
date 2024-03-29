#pragma once

#include "IJob.h"
#include "utils.h"

#include "SmartSubprocess.h"

using namespace std;

class JobSubprocess: IJob
{
private:
    static const string ARG_OVERRIDE_FILE;
    static const string ARG_SEND_FILE;

    SmartSubprocess SP;

    bool ShouldRun;

    string ProcessFileType(string ModuleName);
    string FindModule(string ModuleName);
    string ParseArg(string Arg);

public: 
    string GetType() const;
    void PrepareJobToSend(vector<Argument>& Input);
    void Execute(vector<Argument>& Input);
    bool IsInputValid(vector<Argument>& Input);
    int Kill();

    bool IsDone() override;

    IJob* Clone() { return (IJob*) DBG_NEW JobSubprocess(); }

    ~JobSubprocess() { Kill(); };
};