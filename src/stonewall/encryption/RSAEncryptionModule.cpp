#include "RSAEncryptionModule.h"
#include "rsa.h"

#include "Singleton.h"
#include "Logger.h"
#include "Utils.h"

#include <math.h>
#include <string>
#include <iostream>

const unsigned int RSAEncryptionModule::KeySize = 256 / 16; // BitNum / bit in short
const unsigned int RSAEncryptionModule::BlockSize = 78; // Number of digits of the number 2^(KeySize * 16)
const unsigned int RSAEncryptionModule::BufferSize = BlockSize * 2; 

RSAEncryptionModule::RSAEncryptionModule() : PublicKey(KeySize), PrivateKey(KeySize)
{}

void RSAEncryptionModule::GenerateKeys()
{
    mpuint& d = mpuint(KeySize);
    mpuint& e = mpuint(KeySize);
    mpuint& pq = mpuint(KeySize);
    
    // RSALib::GenerateKeys(d, e, pq);
    PublicKey = RSAKey(KeySize, e, pq);
    PrivateKey = RSAKey(KeySize, d, pq);

    // string TestString = Utils::GenerateRandomDescriptor(BlockSize * 2);
    // string Test = TestString.substr(0);
    
    // Encrypt(Test, PublicKey);
    // Decrypt(Test);
    
    // if (Test != TestString)
    //     GenerateKeys();
}

void RSAEncryptionModule::Encrypt(string& Target, RSAKey PublicKey)
{
    // string AsciiTarget = "";
    // string NextChar = "";

    // for (unsigned int i = 0; i < Target.size(); i++)
    // {
    //     NextChar = to_string((unsigned short)(Target[i]));
    //     AsciiTarget += to_string(NextChar.size()) + NextChar;
    // }

    // char* CResult;
    // const char* CTarget;
    // CResult = DBG_NEW char[BufferSize];

    // mpuint Source = mpuint(KeySize);
    // mpuint Result = mpuint(KeySize);

    // string TruncatedTarget = "";
    // string Addition = "";
    // Target = "";

    // while (AsciiTarget.size() > 0)
    // {
    //     Source = mpuint(KeySize);
    //     Result = mpuint(KeySize);
        
    //     if (AsciiTarget.size() > BlockSize / 2)
    //     {
    //         TruncatedTarget = AsciiTarget.substr(0, BlockSize / 2);
    //         CTarget = TruncatedTarget.c_str();
    //         Source.scan(CTarget);
    //         AsciiTarget = AsciiTarget.substr(BlockSize / 2);
    //     }
    //     else
    //     {
    //         while (AsciiTarget.length() < BlockSize / 2)
    //         {
    //             AsciiTarget += "9";
    //         }
            
    //         CTarget = AsciiTarget.c_str();
    //         Source.scan(CTarget);

    //         AsciiTarget = "";
    //     }

    //     if (Source > PublicKey.Modulus)
    //     {
    //         Singleton<Logger>::GetInstance().Debug("Fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk --------------------------------------");
    //         // Source.value[Source.length - 1] = 0;
    //     }

    //     RSALib::EncryptDecrypt(Result, Source, PublicKey.Exponent, PublicKey.Modulus);

    //     Result.edit(CResult);
    //     Addition = string(CResult).substr(0);

    //     while (Addition.length() < BlockSize - 1)
    //         Addition += "@";
        
    //     Target += Addition;
    // }
    // delete [] CResult;
}

void RSAEncryptionModule::Decrypt(string& Target)
{
    // mpuint& Source = mpuint(KeySize);
    // mpuint& Result = mpuint(KeySize);

    // char* CResult;
    // const char* CTarget;
    // CResult = DBG_NEW char[BufferSize];

    // size_t SepPos = 0;

    // bool Found = false;

    // string AsciiTarget = "";
    // string TruncatedTarget = "";
    // string Addition = "";

    // while (Target.size() > 0)
    // {
    //     Source = mpuint(KeySize);
    //     Result = mpuint(KeySize);

    //     if (Target.size() > BlockSize - 1)
    //     {
    //         TruncatedTarget = Target.substr(0, BlockSize - 1);

    //         while (TruncatedTarget.back() == '@')
    //             TruncatedTarget.pop_back();

    //         CTarget = TruncatedTarget.c_str();
    //         Source.scan(CTarget);

    //         Target = Target.substr(BlockSize - 1);
    //     }
    //     else
    //     {
    //         CTarget = Target.c_str();
    //         Source.scan(CTarget);

    //         Target = "";
    //     }
        
    //     RSALib::EncryptDecrypt(Result, Source, PrivateKey.Exponent, PrivateKey.Modulus);

    //     Result.edit(CResult);
    //     Addition = string(CResult);

    //     while (Addition.length() < BlockSize / 2)
    //         Addition = "0" + Addition;

    //     AsciiTarget += Addition;
    // }

    // int NextCharSize = 0;

    // while (AsciiTarget.size() > 0)
    // {
    //     NextCharSize = stoi(AsciiTarget.substr(0, 1));
    //     if (NextCharSize == 9 || NextCharSize == 0)
    //         break;
        
    //     Target += (char)(unsigned short)(stoi(AsciiTarget.substr(1, NextCharSize)));

    //     AsciiTarget = AsciiTarget.substr(1 + NextCharSize);
    // }   

    // delete [] CResult;
}