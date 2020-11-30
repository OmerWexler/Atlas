#pragma once

#include <string>

using namespace std;

class IMessage
{
public:
    virtual string GetType() const = 0;

};