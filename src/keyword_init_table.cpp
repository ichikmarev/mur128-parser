/*
    File:    keyword_init_table.cpp
    Created: 10 February 2019 at 10:49 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include "../include/keyword_init_table.h"
#include "../include/mysize.h"

namespace lynx_scanner{
    const State_for_char keyword_init_table[] = {
        {0,   U'б'}, {20,  U'в'}, {56,  U'г'},
        {64,  U'д'}, {67,  U'е'}, {71,  U'и'},
        {83,  U'к'}, {100, U'л'}, {112, U'м'},
        {130, U'н'}, {135, U'о'}, {147, U'п'},
        {172, U'р'}, {178, U'с'}, {198, U'т'},
        {202, U'ф'}, {209, U'ц'}, {221, U'ч'}
    };

    const std::size_t    keyword_init_table_size = size(keyword_init_table);
};