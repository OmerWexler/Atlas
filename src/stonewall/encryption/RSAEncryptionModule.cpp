#include "RSAEncryptionModule.h"
#include "rsa.h"
#include <math.h>
#include <string>

#include "Singleton.h"
#include <iostream>
#include "Logger.h"

const unsigned int RSAEncryptionModule::KeySize = 256 / 16; // BitNum / bit in short
const unsigned int RSAEncryptionModule::BlockSize = 78; // Number of digits of the number 2^(KeySize * 16)

RSAEncryptionModule::RSAEncryptionModule() : PublicKey(KeySize), PrivateKey(KeySize)
{}

void RSAEncryptionModule::GenerateKeys()
{
    mpuint& d = mpuint(KeySize);
    mpuint& e = mpuint(KeySize);
    mpuint& pq = mpuint(KeySize);
    
    RSALib::GenerateKeys(d, e, pq);
    PublicKey = RSAKey(KeySize, e, pq);
    PrivateKey = RSAKey(KeySize, d, pq);
}

void RSAEncryptionModule::Encrypt(string& Target)
{
    string AsciiTarget = "";
    string NextChar = "";

    for (unsigned int i = 0; i < Target.size(); i++)
    {
        NextChar = to_string((unsigned short)(Target[i]));
        AsciiTarget += to_string(NextChar.size()) + NextChar;
    }

    char* CResult;
    const char* CTarget;
    CResult = new char[BlockSize];

    mpuint Source = mpuint(KeySize);
    mpuint Result = mpuint(KeySize);

    Singleton<Logger>::GetInstance().Debug("");
    Singleton<Logger>::GetInstance().Debug("");
    Singleton<Logger>::GetInstance().Debug("Encryption - " + Target);

    string TruncatedTarget = "";
    string Addition = "";
    Target = "";

    while (AsciiTarget.size() > 0)
    {
        Source = mpuint(KeySize);
        Result = mpuint(KeySize);
        
        if (AsciiTarget.size() > BlockSize / 2)
        {
            Singleton<Logger>::GetInstance().Debug("Ascii - " + AsciiTarget);

            TruncatedTarget = AsciiTarget.substr(0, BlockSize / 2);
            
            Singleton<Logger>::GetInstance().Debug("Trunc - " + TruncatedTarget);
            
            CTarget = TruncatedTarget.c_str();
            Source.scan(CTarget);

            AsciiTarget = AsciiTarget.substr(BlockSize / 2);
            
            Singleton<Logger>::GetInstance().Debug("Ascii - " + AsciiTarget);
        }
        else
        {
            Singleton<Logger>::GetInstance().Debug("Clear");

            while (AsciiTarget.length() < BlockSize / 2)
            {
                AsciiTarget += "9";
            }
            
            Singleton<Logger>::GetInstance().Debug("Ascii - " + AsciiTarget);
            
            CTarget = AsciiTarget.c_str();
            Source.scan(CTarget);

            AsciiTarget = "";
        }

        if (Source > PublicKey.Modulus)
        {
            Singleton<Logger>::GetInstance().Debug("Fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk --------------------------------------");
            system("pause");
            Source.value[Source.length - 1] = 0;
        }

        RSALib::EncryptDecrypt(Result, Source, PublicKey.Exponent, PublicKey.Modulus);

        Result.edit(CResult);
        Addition = string(CResult);

        while (Addition.length() < BlockSize - 1)
            Addition += "@";
        
        Target += Addition;
        Singleton<Logger>::GetInstance().Debug("Target Added - " + Addition);
        Singleton<Logger>::GetInstance().Debug("");
    }

    delete [] CResult;
}

void RSAEncryptionModule::Decrypt(string& Target)
{
    mpuint& Source = mpuint(KeySize);
    mpuint& Result = mpuint(KeySize);

    char* CResult;
    const char* CTarget;
    CResult = new char[BlockSize];

    size_t SepPos = 0;

    bool Found = false;

    string AsciiTarget = "";
    string TruncatedTarget = "";
    string Addition = "";

    Singleton<Logger>::GetInstance().Debug("");
    Singleton<Logger>::GetInstance().Debug("");
    Singleton<Logger>::GetInstance().Debug("Decryption");

    while (Target.size() > 0)
    {
        Source = mpuint(KeySize);
        Result = mpuint(KeySize);

        if (Target.size() > BlockSize - 1)
        {
            Singleton<Logger>::GetInstance().Debug("Target - " + Target);

            TruncatedTarget = Target.substr(0, BlockSize - 1);

            while (TruncatedTarget.back() == '@')
                TruncatedTarget.pop_back();

            Singleton<Logger>::GetInstance().Debug("Trunc - " + TruncatedTarget);

            CTarget = TruncatedTarget.c_str();
            Source.scan(CTarget);

            Target = Target.substr(BlockSize - 1);
            Singleton<Logger>::GetInstance().Debug("Target - " + Target);
        }
        else
        {
            Singleton<Logger>::GetInstance().Debug("Clear");
            Singleton<Logger>::GetInstance().Debug("Ascii - " + AsciiTarget);
            CTarget = Target.c_str();
            Source.scan(CTarget);

            Target = "";
        }
        
        RSALib::EncryptDecrypt(Result, Source, PrivateKey.Exponent, PrivateKey.Modulus);

        Result.edit(CResult);
        Addition = string(CResult);

        while (Addition.length() < BlockSize / 2)
            Addition = "0" + Addition;

        AsciiTarget += Addition;
        Singleton<Logger>::GetInstance().Debug("Ascii Added - " + Addition);
        Singleton<Logger>::GetInstance().Debug("");
    }

    int NextCharSize = 0;

    while (AsciiTarget.size() > 0)
    {
        NextCharSize = stoi(AsciiTarget.substr(0, 1));
        if (NextCharSize == 9 || NextCharSize == 0)
            break;
        
        Target += (char)(unsigned short)(stoi(AsciiTarget.substr(1, NextCharSize)));

        AsciiTarget = AsciiTarget.substr(1 + NextCharSize);
    }   

    Singleton<Logger>::GetInstance().Debug("Done - " + Target);

    delete [] CResult;
}