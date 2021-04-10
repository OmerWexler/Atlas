#pragma once

#include <memory>
#include <wx/string.h>

#include "IJob.h"

using namespace std;

class JobRegistry
{
public:
    static bool JobRegistry::GetJob(const string Type, shared_ptr<IJob>& OutJob);
    static void JobRegistry::GetJobList(vector<wxString>& OutList);
};