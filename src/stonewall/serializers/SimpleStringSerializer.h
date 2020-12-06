#pragma once

#include "IMessage.h"
#include "SimpleStringMessage.h"
#include "ISerializer.h"
#include "Logger.h"

#include <string>

using namespace std;

class SimpleStringSerializer: ISerializer
{
public:
    virtual string GetType() const
    {
        return "SimpleString";
    };

    virtual string Serialize(const IMessage* Message) const
    {
        if (Message->GetType() != GetType())
        {
            Logger::GetInstance().Error("Message of type - " + Message->GetType() + 
                                        " cannot be serialized by serializer of type - " + GetType());
        }
        return ((SimpleStringMessage*) Message)->GetValue();
    };

    virtual ISerializer* Clone() override
    {
        return (ISerializer*) new SimpleStringSerializer();
    };

    virtual ~SimpleStringSerializer() {};
};