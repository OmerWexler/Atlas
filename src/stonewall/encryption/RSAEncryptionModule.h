#pragma once

#include <string>
#include "RSAKey.h"

using namespace std;

class RSAEncryptionModule
{
private:
    RSAKey PublicKey;
    RSAKey PrivateKey;
    
    bool m_IsInitiated = false;
    static const unsigned int BlockSize;

public:
    static const unsigned int KeySize;
    static const unsigned int BufferSize;

    RSAEncryptionModule();
    void GenerateKeys();

    void Encrypt(string& Target, RSAKey PublicKey);
    void Decrypt(string& Target);

    RSAKey& GetPublicKey() { return PublicKey; }
    bool IsInitiated() { return m_IsInitiated; };
};