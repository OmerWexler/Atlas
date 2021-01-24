#pragma once

#include "JobRegistry.h"
#include "Argument.h"

#include "JobLog.h"
#include "Utils.h"

using namespace std;

void JobRegistry::GetJob(int Type, shared_ptr<IJob>& OutJob)
{
    IJob* Job = nullptr;

    switch (Type)
    {
    case 0:
        Job = (IJob*) DBG_NEW JobLog();
        break;
    
    case -1:
    default:
        Job = nullptr;
        break;
    }

    if (Job != nullptr)
    {
        OutJob.reset(Job);
    }
}