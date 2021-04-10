#pragma once

#include "IJob.h"
#include "Utils.h"
#include "CancelJobParser.h"
#include "CancelJobMessage.h"

using namespace std;

string CancelJobParser::GetType() const
{
    return CancelJobMessage::TYPE;
}

void CancelJobParser::Parse(const string& SMsg, unique_ptr<IMessage>& Message)
{
    string Descriptor = SMsg.substr(HEADER.length(), IJob::RANDOM_DESCRIPTOR_LENGTH);
    string OwnerPath =  SMsg.substr(HEADER.length() + IJob::RANDOM_DESCRIPTOR_LENGTH);
    
    Message.reset((IMessage*) DBG_NEW CancelJobMessage(Descriptor, OwnerPath));
}

bool CancelJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}