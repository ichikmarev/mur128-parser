/*
    File:    keyword_init_table.h
    Created: 10 February 2019 at 10:45 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef KEYWORD_INIT_TABLE_H
#define KEYWORD_INIT_TABLE_H
#   include <cstddef>
#   include "../include/state_for_char.h"
namespace lynx_scanner{
    extern const State_for_char keyword_init_table[];
    extern const std::size_t    keyword_init_table_size;
};
#endif