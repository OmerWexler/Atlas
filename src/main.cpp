#pragma once

#include "Path.h"
#include "Utils.h"

using namespace std;

int main(int argc, char** argv) 
{
    Utils::SetupMemoryCheck();

    Path P("/mnt/share/SomeServer");
    P.RemoveFromEnd();
    P.AddToStart("Something");
    P.RemoveFromStart();
    P.AddToEnd("AAA");
    string S = P.GetStrPath();
}