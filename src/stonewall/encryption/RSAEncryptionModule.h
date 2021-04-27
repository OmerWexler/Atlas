#pragma once

#include <string>
#include "RSAKey.h"

using namespace std;

class RSAEncryptionModule
{
private:
    static const unsigned int KeySize;
    static const unsigned int BlockSize;

    RSAKey PublicKey;
    RSAKey PrivateKey;
    
    bool m_IsInitiated;

public:
    RSAEncryptionModule();
    void GenerateKeys();

    void Encrypt(string& Target);
    void Decrypt(string& Target);

    RSAKey& GetPublicKey() { return PublicKey; }
    bool IsInitiated() { return m_IsInitiated; };
};