#pragma once

#include "IJob.h"
#include "utils.h"

using namespace std;

class JobWait: IJob
{
private:
    bool ShouldRun;

public: 
    string GetType() const;
    void Execute(vector<Argument>& Input);
    bool IsInputValid(vector<Argument>& Input);
    int Kill();

    IJob* Clone() { return (IJob*) DBG_NEW JobWait(); }

    ~JobWait() { Kill(); };
};