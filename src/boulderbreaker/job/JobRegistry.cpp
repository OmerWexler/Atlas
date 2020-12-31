#pragma once

#include "JobRegistry.h"
#include "Argument.h"

#include "JobLog.h"

using namespace std;

IJob* JobRegistry::GetJob(int Type, int Success, string GetUniqueDescriptor)
{
    IJob* Job;

    switch (Type)
    {
    case 0:
        Job = (IJob*) new JobLog();
        Job->SetUniqueDescriptor("Test");

    case -1:
    default:
        Job = nullptr;
        break;
    }

    return Job;
}