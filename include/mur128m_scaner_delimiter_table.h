/*
    File:    mur128m_scaner_delimiter_table.h
    Author:  Chikmarev Ilya
*/

#ifndef mur128m_SCANER_DELIMITER_TABLE_H
#define mur128m_SCANER_DELIMITER_TABLE_H
#   include "../include/elem.h"
#   include "../include/mur128m_lexeme.h"
namespace mur128m_scanner{
    extern const trans_table::Elem<Lexem_code> delimiters_jump_table[];
};
#endif
