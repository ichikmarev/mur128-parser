/*
    File:    delimiter_init_table.cpp
    Created: 26 March 2019 at 11:28 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include "../include/delimiter_init_table.h"
#include "../include/mysize.h"

namespace lynx_scanner{
    const State_for_char delimiter_init_table[] = {
        {23,  U'!'}, {53,  U'#'}, {77,  U'%'},
        {87,  U'&'}, {2,   U'('}, {10,  U')'},
        {63,  U'*'}, {56,  U'+'}, {104, U','},
        {16,  U'-'}, {46,  U'.'}, {72,  U'/'},
        {4,   U':'}, {52,  U';'}, {11,  U'<'},
        {50,  U'='}, {93,  U'>'}, {97,  U'?'},
        {44,  U'@'}, {0,   U'['}, {9,   U']'},
        {40,  U'^'}, {99,  U'{'}, {81,  U'|'},
        {103, U'}'}, {35,  U'~'}
//         {23,  U'!'},    {53,  U'#'},    {77,  U'%'},
//         {87,  U'&'},    {2,   U'('},    {10,  U')'},
//         {63,  U'*'},    {56,  U'+'},    {104, U','},
//         {16,  U'-'},    {46,  U'.'},    {72,  U'/'},
//         {4,   U':'},    {52,  U';'},    {11,  U'<'},
//         {50,  U'='},    {93,  U'>'},    {97,  U'?'},
//         {44,  U'@'},    {0,   U'['},    {9,   U']'},
//         {40,  U'^'},    {99,  U'{'},    {81,  U'|'},
//         {103, U'}'},    {35,  U'~'}
    };

    const std::size_t    delimiter_init_table_size = size(delimiter_init_table);
};