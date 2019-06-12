/*
    File:    keyword_init_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/keyword_init_table.h"
#include "../include/mysize.h"

namespace mur128m_scanner{
    const State_for_char keyword_init_table[] = {
        {2,   U'a'}, {0,   U'b'}, {13,  U'c'},
        {59,  U'd'}, {72,  U'f'}, {116, U'i'},
        {97,  U'j'}, {148, U'l'}, {196, U'm'},
        {155, U'n'}, {141, U'o'}, {216, U'p'},
        {162, U'r'}, {204, U's'}, {158, U't'},
        {128, U'u'}, {144, U'x'}, {222, U'e'},
	{232, U'w'}
    };

    const std::size_t    keyword_init_table_size = size(keyword_init_table);
};
