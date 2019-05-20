/*
    File:    float128_to_string.cpp
    Author:  Chikmarev Ilya
*/

#include <quadmath.h>
#include "../include/float128_to_string.h"

std::string to_string(const __float128 x)
{
    int         sz     = quadmath_snprintf(NULL, 0, "%+.20Qe", x);
    char        buffer[sz + 1];
    quadmath_snprintf(buffer, sz + 1, "%+.20Qe", x);
    std::string result{buffer};
    return result;
}
