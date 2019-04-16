/*
    File:    usage.cpp
    Created: 11 March 2019 at 19:31 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include <cstdio>
#include "../include/usage.h"

static const char* usage_str =
    R"~(lynx-scanner
Copyright (c) Gavrilov V.S., 2019
lynx-parser is a compiler of the educational programming language Lynx.

This program is free software, and it is licensed under the GPLv3 license.
There is NO warranty, not even MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Usage: %s file
)~";

void usage(const char* program_name)
{
    printf(usage_str, program_name);
}