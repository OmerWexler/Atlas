#pragma once

#include "JobRegistry.h"
#include "Argument.h"

#include "JobLog.h"

using namespace std;

IJob* JobRegistry::GetJob(int Type)
{
    IJob* Job;

    switch (Type)
    {
    case 0:
        Job = (IJob*) new JobLog();
        break;
    
    case -1:
    default:
        Job = nullptr;
        break;
    }

    return Job;
}