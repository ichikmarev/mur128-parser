/*
    File:    delimiter_init_table.h
  Author:  Chikmarev Ilya
*/

#ifndef DELIMITER_INIT_TABLE_H
#define DELIMITER_INIT_TABLE_H
#   include <cstddef>
#   include "../include/state_for_char.h"
namespace mur128m_scanner{
    extern const State_for_char delimiter_init_table[];
    extern const std::size_t    delimiter_init_table_size;
};
#endif
