#pragma once

#include "File.h"
#include "Utils.h"

File::File(string Path, ios::openmode Mode)
{
    Create(Path, Mode);
}

void File::Create(string Path, ios::openmode Mode)
{
    Stream = unique_ptr<fstream>(DBG_NEW fstream());

    Stream->open(Path, ios::out);
    Stream.reset(DBG_NEW fstream(Path));
}

void File::Write(string In)
{
    if (Stream)
        (*Stream.get()) << In;
}

void File::Read(string& Out, int size)
{
    Out = "";
    char ch;

    while (!Stream->eof() && Out.length() < size)
    {
        (*Stream.get()) >> ch;
        Out += ch;
    }
}

void File::Seeki(ios_base::seekdir Base, int Delta)
{
    Stream->seekg(Base, Delta);
}

void File::Seeko(ios_base::seekdir Base, int Delta)
{
    Stream->seekp(Base, Delta);
}

void File::Close()
{
    if (IsOpen())
        Stream->close();
}

bool File::IsOpen()
{
    return Stream && Stream->is_open();
}
