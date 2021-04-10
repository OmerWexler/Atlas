#pragma once

#include "JobRegistry.h"
#include "Argument.h"
#include "Utils.h"

#include "JobLog.h"
#include "JobWait.h"

#undef GetJob

using namespace std;

void JobRegistry::GetJob(const string Type, shared_ptr<IJob>& OutJob)
{
    IJob* Job = nullptr;

    if (Type =="JobLog")
        Job = (IJob*) DBG_NEW JobLog();
    
    if (Type == "JobWait")
        Job = (IJob*) DBG_NEW JobWait();
    
    if (Job != nullptr)
    {
        OutJob.reset(Job);
    }
}