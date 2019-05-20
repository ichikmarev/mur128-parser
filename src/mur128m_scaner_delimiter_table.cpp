/*
    File:    mur128m_scaner_delimiter_table.cpp
    Author:  Chikmarev Ilya
*/

#include "../include/mur128m_scaner_delimiter_table.h"

namespace mur128m_scanner{
    const trans_table::Elem<Lexem_code> delimiters_jump_table[] = {
        {const_cast<char32_t*>(U""),      Lexem_code::Sq_br_opened,                 0}, // 0:   [
        {const_cast<char32_t*>(U""),      Lexem_code::Sq_br_closed,                 0}, // 1:   ]
        {const_cast<char32_t*>(U""),      Lexem_code::Round_br_opened,              0}, // 2:   (
        {const_cast<char32_t*>(U""),      Lexem_code::Round_br_closed,              0}, // 3:   )

        {const_cast<char32_t*>(U"<"),     Lexem_code::Less_than,                    5}, // 4:  <
        {const_cast<char32_t*>(U""),      Lexem_code::Left_shift,                   0}, // 5:  <<

        {const_cast<char32_t*>(U""),      Lexem_code::Minus,                        0}, // 6:  -

        {const_cast<char32_t*>(U""),      Lexem_code::Logical_not,                  0}, // 7:  !

        {const_cast<char32_t*>(U""),      Lexem_code::Bitwise_not,                  0}, // 8:  ~

        {const_cast<char32_t*>(U""),      Lexem_code::Point,                        0}, // 9:  .

        {const_cast<char32_t*>(U""),      Lexem_code::Semicolon,                    0}, // 10:  ;

        {const_cast<char32_t*>(U""),      Lexem_code::Plus,                         0}, // 11:  +

        {const_cast<char32_t*>(U""),      Lexem_code::Mul,                          0}, // 12:  *

        {const_cast<char32_t*>(U""),      Lexem_code::Div,                          0}, // 13:  /

        {const_cast<char32_t*>(U""),      Lexem_code::Remainder,                    0}, // 14:  %

        {const_cast<char32_t*>(U""),      Lexem_code::Bitwise_or,                   0}, // 15:  |

        {const_cast<char32_t*>(U""),      Lexem_code::Bitwise_and,                  0}, // 16:  &

        {const_cast<char32_t*>(U">"),     Lexem_code::Greater_than,                 18}, // 17:  >
        {const_cast<char32_t*>(U""),      Lexem_code::Right_shift,                  0}, // 18:  >>

        {const_cast<char32_t*>(U""),      Lexem_code::Curly_brace_opened,           0}, // 19:  {
        {const_cast<char32_t*>(U""),      Lexem_code::Curly_brace_closed,           0}, // 20: }

        {const_cast<char32_t*>(U""),      Lexem_code::Comma,                        0}  // 21: ,
    };
};
