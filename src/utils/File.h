#pragma once

#include <fstream>
#include <memory>

using namespace std;

class File
{
private:
    unique_ptr<fstream> Stream;

public:
    File() {};

    File(string Path, ios::openmode mode);
    void Create(string Path, ios::openmode mode);

    File& operator=(const File&& Other);

    void Write(string In);
    void Read(string& out, int size);

    void Seeki(ios_base::seekdir Base, int Delta);
    void Seeko(ios_base::seekdir Base, int Delta);

    void Close();

    bool IsOpen();
    
    ~File() { Close(); }
};