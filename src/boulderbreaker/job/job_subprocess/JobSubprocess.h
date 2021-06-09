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

public: 
    string GetType() const;
    void Execute(vector<Argument>& Input);
    bool IsInputValid(vector<Argument>& Input);
    int Kill();

    IJob* Clone() { return (IJob*) DBG_NEW JobSubprocess(); }

    ~JobSubprocess() { Kill(); };
};