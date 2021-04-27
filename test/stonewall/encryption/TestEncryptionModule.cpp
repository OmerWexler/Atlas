#include <string>
#include "RSAEncryptionModule.h"

using namespace std;

int TestEncryptionModule() 
{
    RSAEncryptionModule EModule = RSAEncryptionModule();
    EModule.GenerateKeys();

    for (int i = 0; i < 3; i++)
    {
        string InitialMessage = "\"|{}\":>>PL+NT)@#YGMSGejg15j21985jtpase9ng[\"NM{PL{\"|AauifhuiabefipabefSagfeagggggggggggggggadgergageeg4g43t2j58 yht823ghtpowngs  ";
        string Message = InitialMessage.substr(0);
        
        EModule.Encrypt(Message);
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
            return 1;
        
        InitialMessage = "\"|{}\":>>PL+NT)@#YGMSGejg15j21985jtpase9ng[\"NM{PL{\"|A+_!@(I%)$!@T{}JEWSANGFPNJMOnsungiuasdafewfasegfasegnsegF";
        Message = InitialMessage.substr(0);
        
        EModule.Encrypt(Message);
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
            return 1;
        
        InitialMessage = "NJMOnsungiuasdafewfasegfasegnsegF";
        Message = InitialMessage.substr(0);

        EModule.Encrypt(Message);
        EModule.Decrypt(Message);
        
        if (InitialMessage != Message)
            return 1;
    }

    return 0;
}
