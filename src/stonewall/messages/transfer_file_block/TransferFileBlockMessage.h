#pragma once

#include <memory>

#include "IMessage.h"
#include "Path.h"
#include <string>

using namespace std;

class TransferFileBlockMessage: public IMessage
{
private:
    string Filepath;
    Path PathToTarget;
    int WriteIndex;
    string DataBlock;
    bool m_IsEnd;

public:
    static const string TYPE;
    
    TransferFileBlockMessage(string Filepath, Path PathToTarget, int WriteIndex, bool IsEnd, string DataBlock);
    string GetType() const { return TYPE; }

    string GetFilepath() { return Filepath; };
    Path GetPathToTarget() { return PathToTarget; };
    int GetWriteIndex() { return WriteIndex; };
    bool IsEnd() { return m_IsEnd; };
    string GetDataBlock() { return DataBlock; };
};