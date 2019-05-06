/*
    File:    get_processed_text.h
    Author:  Ilya Chikmarev
*/
#ifndef GET_PROCESSED_TEXT_H
#define GET_PROCESSED_TEXT_H
#include <string>
/* Function that opens a file with text. Returns a string with text if the file was
 * opened and the file size is not zero, and an empty string otherwise. */
std::u32string get_processed_text(const char* name);
#endif
