#pragma once

#include "utils.h"
#include "TransferFileSerializer.h"
#include "TransferFileMessage.h"
#include "SeperatorBasedMessage.h"

using namespace std;

TransferFileSerializer::TransferFileSerializer()
{
    this->SPBSerializer = SeperatorBasedSerializer();
}

string TransferFileSerializer::GetType() const
{
    return TransferFileMessage::TYPE;
}

string TransferFileSerializer::Serialize(const unique_ptr<IMessage>& Message) const
{
    TransferFileMessage* TFMsg = (TransferFileMessage*) Message.get();

    SeperatorBasedMessage* SPBMsg = DBG_NEW SeperatorBasedMessage();
    SPBMsg->AddValue(TFMsg->GetFilepath());
    SPBMsg->AddValue(TFMsg->GetPathToTarget().GetStrPath());
    SPBMsg->AddValue(TFMsg->GetDataBlock());
    
    string SMsg = "" + HEADER;
    SMsg += SPBSerializer.Serialize(unique_ptr<IMessage>((IMessage*) SPBMsg));

    return SMsg;
}