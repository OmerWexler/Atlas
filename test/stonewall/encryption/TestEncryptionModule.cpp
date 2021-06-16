#include <string>
#include "RSAEncryptionModule.h"

#include "Singleton.h"
#include "Logger.h"

#include <iostream>

using namespace std;

int TestEncryptionModule() 
{
    RSAEncryptionModule EModule = RSAEncryptionModule();
    for (int i = 0; i < 5; i++)
    {
        EModule.GenerateKeys();
        string InitialMessage = "\"|{}\":>>PL+NT)@#YGMSGejg15j21985jtpa1-3856-293780ug34h-q8gj8mb---8v---- ----h---82---3-yt2-3y h8f-hidosahfnupiunffFUPIFFBNFFFffPUIBFIUPB@(*!{PG )#*_@ GB_) #@Y*_# Y% *()@#) se9n";
        string Message = InitialMessage.substr(0);
        
        EModule.Encrypt(Message, EModule.GetPublicKey());
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
        {
            Singleton<Logger>::GetInstance().Debug("Message Mismatch");
        }

        InitialMessage = "\"|{}\":>>PL+NT)@#YGMSGejg15j21985jtpase9ng[\"NM{PL{\"|A+_!@(I%)$!@T{}JEWSANGFPNJMOnsungiuasdafewfasegfasegnsegF";
        Message = InitialMessage.substr(0);
        
        EModule.Encrypt(Message, EModule.GetPublicKey());
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
        {
            Singleton<Logger>::GetInstance().Debug("Message Mismatch");
        }

        InitialMessage = "NJMOnsungiuasdafewfasegfasegnsegF";
        Message = InitialMessage.substr(0);

        EModule.Encrypt(Message, EModule.GetPublicKey());
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
        {
            Singleton<Logger>::GetInstance().Debug("Message Mismatch");
        }
    }

    Singleton<Logger>::GetInstance().Debug("Encryption Done");
    return 0;
}
