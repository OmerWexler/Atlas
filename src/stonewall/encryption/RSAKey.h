#pragma once

#include "mpuint.h"

struct RSAKey
{
    RSAKey() : 
        Exponent(512),
        Modulus(512)
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

    mpuint Exponent;
    mpuint Modulus;    
};