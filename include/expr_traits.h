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
    P_is_B_E, B_is_S, E_is_i, S_is_At_SB,
    SB_is_R_C, R_is_ri_fi_sp_bp, C_is_srf,
    C_is_lrf, C_is_p, C_is_a3f, C_is_a3r
};

enum class Non_terminal : uint8_t{
    Nt_P, Nt_E, Nt_B, Nt_S, Nt_At,
    Nt_At,Nt_R, Nt_C, Nt_D, Nt_SB
};

enum class Terminal{
    End_of_text, Term_ri,  Term_fi,
    Term_sp, Term_bp, Term_mi, Term_lr,
    Term_srf, Term_lrf, Term_p, Term_a3f,
    Term_a2f, Term_m2f, Term_jr1, Term_jr2,
    Term_jc, Term_jcr, Term_crl, Term_clc,
    Term_r, Term_ra, Term_rc, Term_d,
    Term_p, Term_i
};

using Expr_grammar_traits = Grammar_traits<Terminal, Non_terminal, Rule, 3>;

using Expr_scaner_traits  = Scaner_traits<Expr_scaner, Expr_lexem_info>;
#endif
