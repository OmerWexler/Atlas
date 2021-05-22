#pragma once

#include "IJob.h"

#include <random>

using namespace std;

size_t IJob::RANDOM_DESCRIPTOR_LENGTH = 16;

void IJob::StartASync(vector<Argument>& Input)
{
    ASyncThread = SmartThread(
        "IJob - " + UniqueDescriptor,
        ST_SINGLE_CALL,
        &IJob::Execute,
        this,
        Input
    );
}

IJob::~IJob()
{
    if (ASyncThread.GetIsRunning())
    {
        ASyncThread.Stop();
    }
}