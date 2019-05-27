/*
    File:    mur128m_lexeme.h
    Author:  Chikmarev Ilya
*/
#ifndef mur128m_LEXEME_H
#define mur128m_LEXEME_H
#include <cstddef>
#include <quadmath.h>

namespace mur128m_scanner{
    enum class Lexem_code : uint16_t{
        Nothing,                     UnknownLexem,
        Section,                     Readable,
        Writable,                    Executable,
        Id,                          Integer,
        Float32,                     Float64,
        Float80,                     Float128,
        Complex32,                   Complex64,
        Complex80,                   Complex128,
        String,                      Char,
        Sq_br_opened,                Round_br_opened,
        Sq_br_closed,                Round_br_closed,
        Less_than,                   Left_shift,
        Minus,                       Logical_not,
        Bitwise_not,                 Point,
        Semicolon,                   Plus,
        Mul,                         Div,
        Remainder,                   Bitwise_or,
        Bitwise_and,                 Greater_than,
        Right_shift,                 Curly_brace_opened,
        Curly_brace_closed,          Comma
    };

    struct Lexeme_info{
        Lexem_code code_;
        union{
            unsigned __int128 int_val_;
            __float128        float_val_;
            __complex128      complex_val_;
            char32_t          char_val_;
            std::size_t       str_index_;
            std::size_t       id_index_;
        };
    };
};
#endif
