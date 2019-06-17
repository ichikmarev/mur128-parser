/*
    File:    expr_lr_tables.cpp
    Author:  Ilya Chikmarev
*/

#include "../include/expr_lr_tables.h"
#include <utility>

static const Rule_info<Non_terminal> rules[] = {
    {Non_terminal::Nt_S, 3}, {Non_terminal::Nt_T, 3}, {Non_terminal::Nt_T, 1},
    {Non_terminal::Nt_E, 2}, {Non_terminal::Nt_E, 1}, {Non_terminal::Nt_F, 2},
    {Non_terminal::Nt_F, 1}, {Non_terminal::Nt_G, 2}, {Non_terminal::Nt_G, 1},
    {Non_terminal::Nt_H, 1}, {Non_terminal::Nt_H, 3}
};

static const GOTO_entry goto_P[] = {
    {ANY, 1}
};

static const GOTO_entry goto_B[] = {
    {ANY, 2}
};

static const GOTO_entry goto_R[] = {
    {ANY, 3}
};

static const GOTO_entry goto_C[] = {
    {3, 8}, {ANY, 5}
};

static const GOTO_entry goto_Ar[] = {
    {8, 30}, {ANY, 6}
};

static const GOTO_entry* goto_table[] = {
    goto_P, goto_B, goto_R, goto_C, goto_Ar
};

static const Parser_action_table<Terminal> action_table = {
    {{0,Terminal::Term_ri},SHIFT(4)},              {{1,Terminal::End_of_text},ACCESS},
    {{0,Terminal::Term_fi},SHIFT(5)},              {{2,Terminal::Term_sp},SHIFT(6)},
    {{0,Terminal::Term_sp},SHIFT(7)},              {{3,Terminal::Term_q},REDUCE(T_is_S)},
    {{3,Terminal::Term_mi},SHIFT(9)},              {{3,Terminal::Term_lr},SHIFT(10)},
    {{3,Terminal::Term_sr},SHIFT(11)},             {{3,Terminal::Term_p},SHIFT(12)},
    {{3,Terminal::Term_a3f},SHIFT(13},             {{3,Terminal::Term_mrf},SHIFT(15)},
    {{3,Terminal::Term_lrf},SHIFT(16},             {{3,Terminal::Term_pup},SHIFT(16)},
    {{3,Terminal::Term_p},SHIFT(17},             {{3,Terminal::Term_m2f},SHIFT(18)},
    {{3,Terminal::Term_clc},SHIFT(16},             {{3,Terminal::Term_jcr},SHIFT(19)},
    {{3,Terminal::Term_dc},SHIFT(20},             {{3,Terminal::Term_rc},SHIFT(20)},
    {{3,Terminal::Term_b},REDUCE(C_is_p)},        {{3,Terminal::Term_q},REDUCE(C_is_p)},
    {{4,Terminal::Term_RP},REDUCE(C_is_p)},       {{5,Terminal::Term_b},REDUCE(C_is_p)},
    {{5,Terminal::Term_d},REDUCE(E_is_F)},        {{5,Terminal::Term_q},REDUCE(E_is_F)},
    {{5,Terminal::Term_LP},REDUCE(C_is_srf)},     {{5,Terminal::Term_RP},REDUCE(E_is_F)},
    {{6,Terminal::Term_b},REDUCE(F_is_G)},        {{6,Terminal::Term_d},REDUCE(F_is_G)},
    {{6,Terminal::Term_q},REDUCE(F_is_G)},        {{6,Terminal::Term_LP},REDUCE(F_is_G)},
    {{6,Terminal::Term_RP},REDUCE(F_is_G)},       {{6,Terminal::Term_c},SHIFT(13)},
    {{7,Terminal::Term_a},SHIFT(14)},             {{7,Terminal::Term_b},REDUCE(G_is_H)},
    {{7,Terminal::Term_c},REDUCE(G_is_H)},        {{7,Terminal::Term_d},REDUCE(G_is_H)},
    {{7,Terminal::Term_q},REDUCE(G_is_H)},        {{7,Terminal::Term_LP},REDUCE(G_is_H)},
    {{7,Terminal::Term_RP},REDUCE(G_is_H)},       {{8,Terminal::Term_a},REDUCE(H_is_d)},
    {{8,Terminal::Term_b},REDUCE(H_is_d)},        {{8,Terminal::Term_c},REDUCE(H_is_d)},
    {{8,Terminal::Term_sp},REDUCE(R_is_ri_fi_sp_bp)},{{8,Terminal::Term_q},REDUCE(H_is_d)},
    {{8,Terminal::Term_LP},REDUCE(B_is_S)},       {{8,Terminal::Term_RP},REDUCE(H_is_d)},
    {{9,Terminal::Term_d},SHIFT(18)},              {{9,Terminal::Term_LP},SHIFT(23)},
    {{10,Terminal::Term_d},SHIFT(24)},             {{10,Terminal::Term_LP},SHIFT(26)},
    {{11,Terminal::End_of_text},REDUCE(P_is_B_E)},{{12,Terminal::Term_b},REDUCE(S_is_At_SB)},
    {{12,Terminal::Term_rc},REDUCE(C_is_srf)},      {{12,Terminal::Term_q},REDUCE(S_is_At_SB)},
    {{12,Terminal::Term_LP},REDUCE(C_is_srf)},     {{12,Terminal::Term_RP},REDUCE(S_is_At_SB)},
    {{13,Terminal::Term_ra},REDUCE(F_is_Gc)},      {{13,Terminal::Term_d},REDUCE(S_is_At_SB)},
    {{13,Terminal::Term_q},REDUCE(F_is_Gc)},      {{13,Terminal::Term_LP},REDUCE(S_is_At_SB)},
    {{13,Terminal::Term_clc},REDUCE(F_is_Gc)},     {{14,Terminal::Term_b},REDUCE(E_is_i)},
    {{14,Terminal::Term_d},REDUCE(G_is_Ha)},      {{14,Terminal::Term_q},REDUCE(E_is_i)},
    {{14,Terminal::Term_LP},REDUCE(G_is_Ha)},     {{14,Terminal::Term_RP},REDUCE(E_is_i)},
    {{14,Terminal::Term_c},REDUCE(G_is_Ha)},      {{15,Terminal::Term_b},SHIFT(12)},
    {{15,Terminal::Term_RP},SHIFT(23)},           {{16,Terminal::Term_d},SHIFT(8)},
    {{16,Terminal::Term_LP},SHIFT(24)},            {{16,Terminal::Term_b},REDUCE(T_is_TbE)},
    {{16,Terminal::Term_q},REDUCE(T_is_TbE)},     {{16,Terminal::Term_RP},REDUCE(T_is_TbE)},
    {{17,Terminal::Term_a},REDUCE(P_is_B_E)}, {{17,Terminal::Term_b},REDUCE(P_is_B_E)},
    {{17,Terminal::Term_c},REDUCE(P_is_B_E)}, {{17,Terminal::Term_d},REDUCE(P_is_B_E)},
    {{17,Terminal::Term_q},REDUCE(P_is_B_E)}, {{17,Terminal::Term_LP},REDUCE(P_is_B_E)},
    {{17,Terminal::Term_RP},REDUCE(P_is_B_E)} {{18,Terminal::Term_sp},SHIFT(24)},
    {{19,Terminal::Term_LP},REDUCE(B_is_S)},       {{18,Terminal::Term_RP},REDUCE(H_is_d)},
    {{19,Terminal::Term_d},SHIFT(27)},              {{19,Terminal::Term_LP},SHIFT(23)},
    {{20,Terminal::Term_d},SHIFT(29)},             {{19,Terminal::Term_LP},SHIFT(26)},
    {{21,Terminal::End_of_text},REDUCE(P_is_B_E)},{{20,Terminal::Term_fi},REDUCE(S_is_At_SB)},
    {{22,Terminal::Term_rc},REDUCE(C_is_srf)},      {{22,Terminal::Term_q},REDUCE(S_is_At_SB)},
    {{22,Terminal::Term_LP},REDUCE(C_is_srf)},     {{22,Terminal::Term_p},REDUCE(S_is_At_SB)},
    {{22,Terminal::Term_ra},REDUCE(F_is_Gc)},      {{23,Terminal::Term_d},REDUCE(S_is_At_SB)},
    {{22,Terminal::Term_q},REDUCE(F_is_Gc)},      {{23,Terminal::Term_p},REDUCE(S_is_At_SB)},
    {{23,Terminal::Term_clc},REDUCE(F_is_Gc)},     {{24,Terminal::Term_b},REDUCE(E_is_i)},
    {{24,Terminal::Term_d},REDUCE(G_is_Ha)},      {{24,Terminal::Term_q},REDUCE(SB_is_R_C)},
    {{25,Terminal::Term_LP},REDUCE(G_is_Ha)},     {{26,Terminal::Term_RP},REDUCE(SB_is_R_C)},
    {{27,Terminal::Term_LP},SHIFT(24)},            {{28,Terminal::Term_b},REDUCE(T_is_TbE)},
    {{28,Terminal::Term_m2f},REDUCE(C_is_lrf)},     {{28,Terminal::Term_RP},REDUCE(C_is_lrf)},
    {{29,Terminal::Term_m2f},REDUCE(C_is_lrf)}, {{30,Terminal::Term_b},REDUCE(C_is_lrf)},
    {{30,Terminal::Term_ra},REDUCE(C_is_a3r)}, {{30,Terminal::Term_d},REDUCE(C_is_a3r)},
    {{31,Terminal::Term_q},REDUCE(C_is_a3r)}, {{32,Terminal::Term_p},REDUCE(C_is_a3r)},
    {{32,Terminal::Term_d},REDUCE(C_is_a3r)}
};

const LR_parser_tables<Expr_grammar_traits> expr_slr_tables = {
    const_cast<Rule_info<Non_terminal>*>(rules),
    const_cast<GOTO_entry**>(goto_table),
    const_cast<Parser_action_table<Terminal>*>(&action_table)
};
