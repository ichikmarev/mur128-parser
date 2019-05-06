/*
    File:    int128_to_str.cpp
    Author:  Ilya Chikmarev
*/

#include "../include/int128_to_str.h"

std::string to_string(unsigned __int128 x)
{
    unsigned __int128 quotient    = x;
    unsigned __int128 remainder;
    unsigned          begin_index = 0;
    unsigned          end_index   = 0;

    char              buffer[40];

    do{
       remainder =  quotient % 10;
       quotient  /= 10;
       buffer[end_index++] = static_cast<unsigned>(remainder & 0xff) + '0';
    }while(quotient != 0);

    buffer[end_index--] = '\0';

    while(begin_index < end_index){
        char temp           = buffer[begin_index];
        buffer[begin_index] = buffer[end_index];
        buffer[end_index]   = temp;
        begin_index++;
        end_index--;
    }

    return std::string{buffer};
}
