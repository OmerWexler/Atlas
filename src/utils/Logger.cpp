#pragma once

#include "Logger.h"

#include <string>
#include <iostream>

using namespace std;

void Logger::Log(string Msg)
{
    cout << Msg;
};