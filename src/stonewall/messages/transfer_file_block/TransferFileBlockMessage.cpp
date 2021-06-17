#pragma once

#include "TransferFileBlockMessage.h"

const string TransferFileBlockMessage::TYPE = "TFB";

TransferFileBlockMessage::TransferFileBlockMessage(string Filepath, Path PathToTarget, int WriteIndex, bool IsEnd, string DataBlock)
{
    this->Filepath = Filepath;
    this->PathToTarget = PathToTarget;
    this->WriteIndex = WriteIndex;
    this->m_IsEnd = IsEnd;
    this->DataBlock = DataBlock;
}