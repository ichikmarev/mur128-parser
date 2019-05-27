/*
    File:    keyword_init_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/keyword_init_table.h"
#include "../include/mysize.h"

namespace mur128m_scanner{
    const State_for_char keyword_init_table[] = {
        {2,   U'a'}, {0,   U'b'}, {13,  U'c'},
        {53,  U'd'}, {66,  U'f'}, {106, U'i'},
        {86,  U'j'}, {138, U'l'}, {196, U'm'},
        {145, U'n'}, {131, U'o'}, {190, U'p'},
        {152, U'r'}, {184, U's'}, {148, U't'},
        {118, U'u'}, {134, U'x'}
    };

    const std::size_t    keyword_init_table_size = size(keyword_init_table);
};
