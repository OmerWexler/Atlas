#pragma once

using namespace std;

struct Argument
{
    Argument()
    {
        this->Value = "";
        this->IsFile = false;
    }
    
    Argument(string Value, bool IsFile)
    {
        this->Value = Value;
        this->IsFile = IsFile;
    }
    
    string Value;
    bool IsFile;
};