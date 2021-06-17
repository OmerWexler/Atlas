#pragma once

#include "File.h"
#include "Utils.h"
#include <filesystem>
#include <windows.h>

namespace fs = std::experimental::filesystem;

File::File(string Path, string Mode)
{
    Create(Path, Mode);
}

File::File(string Path, string Mode, bool mkdir)
{
    Create(Path, Mode, mkdir);
}

void File::Create(string Path, string Mode)
{
    Create(Path, Mode, false);
}

void File::Create(string Path, string Mode, bool mkdir)
{
    m_IsOpen = false;

    if (IsOpen())
        Close();
    
    if (mkdir)
        CreateDirectoryA(fs::path(Path).parent_path().string().c_str(), NULL);
    
    hFile = fopen(Path.c_str(), Mode.c_str());
    if (!hFile)
        return;
    
    fseek(hFile, 0, SEEK_END);
    MaxIndex = ftell(hFile);
    rewind(hFile);

    ReadIndex = 0;
    if (hFile)
        m_IsOpen = true;
}

File& File::operator=(File&& Other)
{
    hFile = Other.hFile;
    Other.hFile = nullptr;
    
    m_IsOpen = Other.m_IsOpen;
    MaxIndex = Other.MaxIndex;
    ReadIndex = Other.ReadIndex;

    return *this;
}

void File::Write(string In, int Size)
{
    if (IsOpen())
        fwrite(In.c_str(), sizeof(char), Size, hFile);
}

int File::Read(string& Out, int Size)
{
    char* buffer = (char*) malloc (sizeof(char)*Size);
    
    int Read = fread(buffer, 1, Size, hFile);
    Out.assign(buffer, Read);

    return Read;
}

void File::Close()
{
    if (hFile && m_IsOpen)
        fclose(hFile);
}

bool File::IsOpen()
{
    return hFile && m_IsOpen;
}
