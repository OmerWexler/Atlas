#pragma once

#include "IJob.h"
#include "utils.h"
#include <wx/dialog.h>

using namespace std;

class JobWait: IJob
{
private:
    int Success = 0;
    string UniqueDescriptor = "";
    wxDialog* CurrentWindow;
    bool ShouldRun;

public: 
    string GetType() const;
    void Execute(vector<Argument>& Input);
    bool IsInputValid(vector<Argument>& Input);
    int Kill();

    IJob* Clone() { return (IJob*) DBG_NEW JobWait(); }

    ~JobWait() { Kill(); };
};