#pragma once

using namespace std;

struct Argument
{
    string Value;
    bool IsFile;

    Argument()
    {
        this->Value = "";
        this->IsFile = false;
    }

    Argument(string Value)
    {
        this->Value = Value;
        this->IsFile = false;
    }
    
    Argument(string Value, bool IsFile)
    {
        this->Value = Value;
        this->IsFile = IsFile;
    }
};