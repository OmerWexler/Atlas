#pragma once

#include "JobRegistry.h"
#include "Argument.h"
#include "Utils.h"

#include "JobLog.h"
#include "JobWait.h"
#include "JobSubprocess.h"

#undef GetJob

using namespace std;

bool JobRegistry::GetJob(const string Type, shared_ptr<IJob>& OutJob)
{
    IJob* Job = nullptr;

    if (Type =="Job Log")
        Job = (IJob*) DBG_NEW JobLog();
    
    if (Type == "Job Wait")
        Job = (IJob*) DBG_NEW JobWait();
    
    if (Type == "Job Subprocess")
        Job = (IJob*) DBG_NEW JobSubprocess();
    
    if (Job != nullptr)
    {
        OutJob.reset(Job);
        return true;
    }

    return false;
}