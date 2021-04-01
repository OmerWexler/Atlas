#pragma once

#include <string>

using namespace std;

class IMessage
{
public:
    virtual string GetType() const = 0;
    virtual ~IMessage() {};
};

#define ATLS_CREATE_UNIQUE_MSG(type, ...) unique_ptr<IMessage>((IMessage*) DBG_NEW type(__VA_ARGS__))