#include "FileCore.h"

#include "GridNode.h"
#include "TransferFileMessage.h"
#include "TransferFileBlockMessage.h"
#include "Path.h"

#include "AtlasApp.h"
#include "MainFrame.h"

#undef SendMessage

unordered_map<string, FileBundle> FileCore::LocalFiles = unordered_map<string, FileBundle>();

string FileCore::GetType() const
{
    return "FileCore";
}

void FileCore::HandleMessage(unique_ptr<IMessage>& Message, GridConnection& Sender)
{
    if (!IsMessageRelated(Message))
        return;

    string Type = Message->GetType();
    if (Type == TransferFileMessage::TYPE)
    {
        TransferFileMessageFunc(Message, Sender, false);
    }
    else if (Type == TransferFileBlockMessage::TYPE)
    {   
        TransferFileMessageFunc(Message, Sender, true);
    }
}

void FileCore::TransferFileMessageFunc(unique_ptr<IMessage>& Message, GridConnection& Sender, bool IsExistingBlock)
{
    string CurrentNodeName = Singleton<GridNode>::GetInstance().GetName();
    GridConnection& Admin = Singleton<GridNode>::GetInstance().GetAdmin();

    TransferFileMessage* TFMsg;
    TransferFileBlockMessage* TFBMsg;
    Path PathToTarget = Path();

    if (IsExistingBlock)
    {
        TFBMsg = (TransferFileBlockMessage*) Message.get();
        PathToTarget = TFBMsg->GetPathToTarget();
    }
    else
    {
        TFMsg = (TransferFileMessage*) Message.get();
        PathToTarget = TFMsg->GetPathToTarget();
    }

    
    if (PathToTarget.size() > 1 && PathToTarget[0] == CurrentNodeName)
    {
        PathToTarget.RemoveFromStart();
        if (IsExistingBlock)
        {
            TFBMsg = (TransferFileBlockMessage*) Message.get();
            TFBMsg->GetPathToTarget().RemoveFromStart();
        }
        else
        {
            TFMsg = (TransferFileMessage*) Message.get();
            TFMsg->GetPathToTarget().RemoveFromStart();
        }
    }
    else
    {
        Singleton<Logger>::GetInstance().Warning(
            "Got a TransferFileMessage message with an unmatching path.\n Node name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());
    }

    if (!Singleton<GridNode>::GetInstance().IsWorker())
    {
        // Client should distribute to admin
        if (PathToTarget.size() > 0 && Admin.GetName() == PathToTarget[0])
        {
            Admin.SendMessage(Message);
            return;
        }
    }

    if (PathToTarget.size() == 1 && CurrentNodeName == PathToTarget[0]) // Target is this Node
    {
        if (IsExistingBlock)
        {
            string FilePath = TFBMsg->GetFilepath();
            if (LocalFiles.find(FilePath) == LocalFiles.end())
                LocalFiles[FilePath] = FileBundle();
                
            FileBundle& Bundle = LocalFiles[FilePath];
            Bundle.QueuedDataBlocks[TFBMsg->GetWriteIndex()] = TFBMsg->GetDataBlock();

            if (TFBMsg->IsEnd())
            {
                Bundle.EndFound = true;
                Bundle.EndIndex = TFBMsg->GetWriteIndex();
            }
        }
        else
        {
            string FilePath = TFMsg->GetFilepath();

            if (LocalFiles.find(FilePath) == LocalFiles.end())
                LocalFiles[FilePath] = FileBundle();
            
            LocalFiles[FilePath].NextWriteIndex = 1;
            LocalFiles[FilePath].File.Create(FilePath, "wb", true);

            LocalFiles[FilePath].File.Write(TFMsg->GetDataBlock(), TFMsg->GetDataBlock().length());
        }
    }
    else // Target is a member Node
    {   
        int TargetID = -1;
        auto& It = Singleton<GridNode>::GetInstance().GetMembersBegin();
        auto& End = Singleton<GridNode>::GetInstance().GetMembersEnd();

        while (It != End)
        {
            if (It->second.GetName() == PathToTarget[0])
            {
                TargetID = It->first;
                break;
            }

            It++;
        }

        if (TargetID != -1)
        {
            Singleton<GridNode>::GetInstance().GetMember(TargetID).SendMessage(Message);
        }
        else
        {
            Singleton<Logger>::GetInstance().Warning(
                "Got a SendJob message with an unmatching path.\nNode name - " + CurrentNodeName + "\nPath - " + PathToTarget.GetStrPath());
        }
    }
}

void FileCore::Periodic() 
{
    ASyncFunctionCore::Periodic();
    
    auto& It = LocalFiles.begin();
    auto& End = LocalFiles.end();
    
    while (It != End)
    {
        FileBundle& FBundle = It->second;

        if (FBundle.QueuedDataBlocks.size() > 0)
        {
            auto Index = FBundle.QueuedDataBlocks.find(FBundle.NextWriteIndex);
            if (Index != FBundle.QueuedDataBlocks.end())
            {
                FBundle.File.Write(
                    FBundle.QueuedDataBlocks[FBundle.NextWriteIndex],
                    FBundle.QueuedDataBlocks[FBundle.NextWriteIndex].length()
                );

                FBundle.QueuedDataBlocks.erase(Index);
                FBundle.NextWriteIndex++;

                if (FBundle.EndFound && FBundle.NextWriteIndex > FBundle.EndIndex)
                {
                    FBundle.File.Close();
                    FBundle.QueuedDataBlocks.clear();
                    It = LocalFiles.erase(It);
                    continue;
                }
            }
        }

        It++;
    }
}

void FileCore::StopCore()
{
    ASyncFunctionCore::StopCore();

    for (auto& Bundle: LocalFiles)
    {
        Bundle.second.File.Close();
    }
}

bool FileCore::IsMessageRelated(const unique_ptr<IMessage>& Message) const
{
    return Message->GetType() == TransferFileMessage::TYPE ||
           Message->GetType() == TransferFileBlockMessage::TYPE;
}