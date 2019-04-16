/*
    File:    delimiter_init_table.h
    Created: 26 March 2019 at 11:22 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef DELIMITER_INIT_TABLE_H
#define DELIMITER_INIT_TABLE_H
#   include <cstddef>
#   include "../include/state_for_char.h"
namespace lynx_scanner{
    extern const State_for_char delimiter_init_table[];
    extern const std::size_t    delimiter_init_table_size;
};
#endif