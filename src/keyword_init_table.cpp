/*
    File:    keyword_init_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/keyword_init_table.h"
#include "../include/mysize.h"

namespace mur128m_scanner{
    const State_for_char keyword_init_table[] = {
        {2,   U'a'}, {0,   U'b'}, {13,  U'c'},
        {59,  U'd'}, {72,  U'f'}, {148, U'i'},
        {129, U'j'}, {180, U'l'}, {196, U'm'},
        {187, U'n'}, {173, U'o'}, {281, U'p'},
        {194, U'r'}, {268, U's'}, {190, U't'},
        {160, U'u'}, {176, U'x'}, {287, U'e'},
        {297, U'w'}
    };

    const std::size_t    keyword_init_table_size = size(keyword_init_table);
};
