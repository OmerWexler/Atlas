#pragma once

#include "IJob.h"
#include "utils.h"

#include "SmartSubprocess.h"

using namespace std;

class JobSubprocess: IJob
{
private:
    SmartSubprocess SP;

    bool ShouldRun;

    string ProcessFileType(string ModuleName);
    string FindModule(string ModuleName);

public: 
    string GetType() const;
    void Execute(vector<Argument>& Input);
    bool IsInputValid(vector<Argument>& Input);
    int Kill();

    bool IsDone() override;

    IJob* Clone() { return (IJob*) DBG_NEW JobSubprocess(); }

    ~JobSubprocess() { Kill(); };
};