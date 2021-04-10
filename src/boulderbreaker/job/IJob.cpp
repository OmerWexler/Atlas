#pragma once

#include "IJob.h"

#include <random>
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

string IJob::GenerateRandomDescriptor(size_t Length)
{
    const std::string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    random_device random_device;
    mt19937 generator(random_device());
    uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    string random_string;

    for (size_t i = 0; i < Length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}

IJob::~IJob()
{
    if (ASyncThread.GetIsRunning())
    {
        ASyncThread.Stop();
    }
}