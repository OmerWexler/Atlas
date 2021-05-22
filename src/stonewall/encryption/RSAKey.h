#pragma once

#include "mpuint.h"
#include "Utils.h"

struct RSAKey
{
    RSAKey() : 
        Exponent(0),
        Modulus(0)
    {}
    
    RSAKey(unsigned int KeyLength) : 
        Exponent(KeyLength), 
        Modulus(KeyLength)
    {}

    RSAKey(unsigned int KeyLength, const mpuint& Exponent, const mpuint& Modulus)  : 
        Exponent(KeyLength), 
        Modulus(KeyLength)
    {
        this->Exponent = Exponent;
        this->Modulus = Modulus;
    }

    RSAKey operator=(RSAKey& Other)
    {
        Exponent.length = Other.Exponent.length;
        delete[] Exponent.value;
        Exponent.value = DBG_NEW unsigned short[Exponent.length];
        Exponent = Other.Exponent;

        Modulus.length = Other.Modulus.length;
        delete[] Modulus.value;
        Modulus.value = DBG_NEW unsigned short[Modulus.length];
        Modulus = Other.Modulus;

        return *this;
    }

    mpuint Exponent;
    mpuint Modulus;    
};