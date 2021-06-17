#pragma once

#include <fstream>
#include <memory>

using namespace std;

class File
{
private:
    FILE* hFile;
    int MaxIndex;
    int ReadIndex;

    bool m_IsOpen = false;

public:
    File() {};

    File(string Path, string mode);
    File(string Path, string mode, bool mkdir);

    void Create(string Path, string mode);
    void Create(string Path, string mode, bool mkdir);

    File& operator=(File&& Other);

    void Write(string In, int Size);
    int Read(string& out, int Size);

    void Close();

    bool IsOpen();
    
    ~File() { Close(); }
};