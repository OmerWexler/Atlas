#include "File.h"
#include <fstream>

using namespace std;

int FileTest() 
{
    File exe{"E:\\Desktop\\workspace\\2021 Cyber Project\\Atlas\\build\\src\\Debug\\20_23_40_Atlas.txt", "r"};
    File dest{"E:\\Desktop\\workspace\\2021 Cyber Project\\Atlas\\build\\src\\Debug\\FileTest\\20_23_40_Atlas.txt", "w", true};

    string Buff;
    int SizeRead = -1;
    while (SizeRead != 0)
    {
        SizeRead = exe.Read(Buff, 4096);
        dest.Write(Buff, SizeRead);
    }

    exe.Create("E:\\Desktop\\workspace\\2021 Cyber Project\\Atlas\\build\\src\\Debug\\Atlas.exe", "rb");
    dest.Create("E:\\Desktop\\workspace\\2021 Cyber Project\\Atlas\\build\\src\\Debug\\FileTest\\Atlas.exe", "wb", true);

    Buff;
    SizeRead = -1;
    while (SizeRead != 0)
    {
        SizeRead = exe.Read(Buff, 4096);
        dest.Write(Buff, SizeRead);
    }

    return 0;
}