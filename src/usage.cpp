/*
    File:    usage.cpp
    Author:  Ilya Chikmarev
*/

#include <cstdio>
#include "../include/usage.h"

static const char* usage_str =
    R"~(mur128m-scanner
Copyright (c) Gavrilov V.S., 2019
mur128m-parser is a compiler of the educational programming language Lynx.

This program is free software, and it is licensed under the GPLv3 license.
There is NO warranty, not even MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

Usage: %s file
)~";

void usage(const char* program_name)
{
    printf(usage_str, program_name);
}
