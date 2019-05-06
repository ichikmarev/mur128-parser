/*
    File:    digit_to_int.cpp
    Author:  Ilya Chikmarev
*/

#include "../include/digit_to_int.h"
/**
 * It is well known, that characters of hexadecimal digits have the following codes in
 * the Unicode standart:
 *
 * |-----------|------|
 * | Character | Code |
 * |-----------|------|
 * | U'0'      | 0x30 |
 * |-----------|------|
 * | U'1'      | 0x31 |
 * |-----------|------|
 * | U'2'      | 0x32 |
 * |-----------|------|
 * | U'3'      | 0x33 |
 * |-----------|------|
 * | U'4'      | 0x34 |
 * |-----------|------|
 * | U'5'      | 0x35 |
 * |-----------|------|
 * | U'6'      | 0x36 |
 * |-----------|------|
 * | U'7'      | 0x37 |
 * |-----------|------|
 * | U'8'      | 0x38 |
 * |-----------|------|
 * | U'9'      | 0x39 |
 * |-----------|------|
 * | U'A'      | 0x41 |
 * |-----------|------|
 * | U'B'      | 0x42 |
 * |-----------|------|
 * | U'C'      | 0x43 |
 * |-----------|------|
 * | U'D'      | 0x44 |
 * |-----------|------|
 * | U'E'      | 0x45 |
 * |-----------|------|
 * | U'F'      | 0x46 |
 * |-----------|------|
 * | U'a'      | 0x61 |
 * |-----------|------|
 * | U'b'      | 0x62 |
 * |-----------|------|
 * | U'c'      | 0x63 |
 * |-----------|------|
 * | U'd'      | 0x64 |
 * |-----------|------|
 * | U'e'      | 0x65 |
 * |-----------|------|
 * | U'f'      | 0x66 |
 * |-----------|------|
 *
 * Hence, if a character of a digit belongs to the segment [U'0', U'9'], then
 * we can convert such character into digit using a formulae
 *     c - U'0'.
 * Otherwise, we need to convert a character into upper case and then to subtract
 * the value 0x37.
 *
 * Finally, to convert some standard Latin letter c, from U'a' to U'z', we need to
 * calculate
 *     c & 0b1101'1111
 */


unsigned digit_to_int(char32_t c)
{
    unsigned result = c - U'0';
    return (result < 10) ? result : ((c & 0b1101'1111) - 0x37);
}
