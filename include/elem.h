/*
    File:    elem.h
    Author:  Ilya Chikmarev
*/

#ifndef ELEM_H
#define ELEM_H
#include <cstdint>
namespace trans_table{
/**
 * Element of transition table.
 */
    template<typename Lexem_code>
    struct Elem{
        /** A pointer to a string of characters that can be crossed. */
        char32_t*       symbols_;
        /** lexeme code */
        Lexem_code      code_;
        /** If the current character matches symbols[0], then
        *  the transition to the state first_state;
        *  if the current character matches symbols[1], then
        *  the transition to the state first_state + 1;
        *  if the current character matches symbols[2], then
        *  the transition to the state first_state + 2,
        *  and so on. */
        uint16_t        first_state_;
    };
};
#endif
