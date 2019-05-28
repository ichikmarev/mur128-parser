/*
    File:    expr_lr_tables.h
    Author:  Ilya Chikmarev
*/

#ifndef EXPR_SLR_TABLES_H
#define EXPR_SLR_TABLES_H
#include "../include/types_for_lr_tables.h"
#include "../include/expr_traits.h"
extern const LR_parser_tables<Expr_grammar_traits> expr_slr_tables;
#endif
