#include "WinSocketTest.cpp"

int main(int argc, char **argv)
{
    int TestID = atoi(argv[1]);
    switch (TestID)
    {
    case 0:
        exit(TestWinSocketCommunicationSequence());
        break;
    
    default:
        break;
    }
}