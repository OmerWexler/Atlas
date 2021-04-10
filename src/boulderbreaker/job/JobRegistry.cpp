#pragma once

#include "JobRegistry.h"
#include "Argument.h"
#include "Utils.h"

#include "JobLog.h"
#include "JobWait.h"

#undef GetJob

using namespace std;

bool JobRegistry::GetJob(const string Type, shared_ptr<IJob>& OutJob)
{
    IJob* Job = nullptr;

    if (Type =="JobLog")
        Job = (IJob*) DBG_NEW JobLog();
    
    if (Type == "JobWait")
        Job = (IJob*) DBG_NEW JobWait();
    
    if (Job != nullptr)
    {
        OutJob.reset(Job);
        return true;
    }

    return false;
}

void JobRegistry::GetJobList(vector<wxString>& OutList)
{
    OutList.push_back("JobLog");
    OutList.push_back("JobWait");
}