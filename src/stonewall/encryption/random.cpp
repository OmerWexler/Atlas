#include <conio.h>
#include "mpuint.h"
#include "random.h"

#include <iostream> 
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 

#pragma warning( disable : 4244 ) 

void Random(mpuint &x)
{
    for (unsigned i = 0; i < x.length; i++)
    {
        srand(time(0));
        x.value[i] = (short)rand();
    }
}