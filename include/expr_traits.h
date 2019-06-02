/*
    File:    expr_traits.h
    Author:  Ilya Chikmarev
*/
#ifndef EXPR_TRAITS_H
#define EXPR_TRAITS_H

#include "../include/lr_traits.h"
#include "../include/expr_lexem_info.h"
#include "../include/expr_scaner.h"

enum Rule : uint8_t{
    S_is_tQ, T_is_TbE,     T_is_E,
    E_is_EQ,
};

enum class Non_terminal : uint8_t{
    Nt_S, Nt_T, Nt_E
};

enum class Terminal{
    End_of_text, Term_a,  Term_b,
    Term_c, Term_d, Term_q, Term_l
};

using Expr_grammar_traits = Grammar_traits<Terminal, Non_terminal, Rule, 3>;

using Expr_scaner_traits  = Scaner_traits<Expr_scaner, Expr_lexem_info>;
#endif
