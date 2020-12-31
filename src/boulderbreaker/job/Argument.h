#pragma once

using namespace std;

struct Argument
{
    Argument(string Value, bool IsFile)
    {
        this->Value = Value;
        this->IsFile = IsFile;
    }
    string Value;
    bool IsFile;
};