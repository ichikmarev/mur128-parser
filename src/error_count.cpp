/*
    File:    error_count.cpp
    Author:  Chikmarev Ilya
*/

#include <cstdio>
#include "../include/error_count.h"

void Error_count::increment_number_of_errors()
{
    number_of_errors_++;
}

size_t Error_count::get_number_of_errors() const
{
    return number_of_errors_;
}

void Error_count::print() const
{
    printf("\nTotal errors %zu\n", number_of_errors_);
}
