/*
    File:    delimiter_init_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/delimiter_init_table.h"
#include "../include/mysize.h"

namespace mur128m_scanner{
    const State_for_char delimiter_init_table[] = {
        {7,   U'!'}, {53,  U'#'}, {14,  U'%'},
        {16,  U'&'}, {2,   U'('}, {3,   U')'},
        {12,  U'*'}, {11,  U'+'}, {21,  U','},
        {6,   U'-'}, {9,   U'.'}, {13,  U'/'},
        {10,  U';'}, {4,   U'<'}, {17,  U'>'},
        {97,  U'?'}, {44,  U'@'}, {0,   U'['},
        {1,   U']'}, {40,  U'^'}, {19,  U'{'},
        {15,  U'|'}, {20,  U'}'}, {8,   U'~'}
    };

    const std::size_t    delimiter_init_table_size = size(delimiter_init_table);
};
