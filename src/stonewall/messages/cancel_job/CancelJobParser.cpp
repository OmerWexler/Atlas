#pragma once

#include "CancelJobParser.h"
#include "CancelJobMessage.h"

using namespace std;

const string CancelJobParser::HEADER = "CJ";

string CancelJobParser::GetType() const
{
    return "CancelJob";
}

IMessage* CancelJobParser::Parse(const string& SMsg)
{
    string Descriptor = SMsg.substr(HEADER.length(), SMsg.length());
    return (IMessage*) new CancelJobMessage(Descriptor);
}

bool CancelJobParser::CanParse(const string& SMsg) const
{
    return SMsg.substr(0, HEADER.length()) == HEADER;
}

IParser* CancelJobParser::Clone()
{
    return (IParser*) new CancelJobParser();
}