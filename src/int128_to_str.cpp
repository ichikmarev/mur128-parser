/*
    File:    int128_to_str.cpp
    Created: 27 March 2019 at 09:02 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
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