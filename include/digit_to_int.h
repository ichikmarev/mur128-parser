/*
    File:    digit_to_int.h
    Created: 17 March 2019 at 14:57 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef DIGIT_TO_INT_H
#define DIGIT_TO_INT_H
/**
 * \brief
 * \param [in] c  character of hexadecimal digit
 * \return        integer number corresponding to character c, i.e.
 *                '0' converted into 0,
 *                '1' converted into 1,
 *                '2' converted into 2,
 *                '3' converted into 3,
 *                '4' converted into 4,
 *                '5' converted into 5,
 *                '6' converted into 6,
 *                '7' converted into 7,
 *                '8' converted into 8,
 *                '9' converted into 9,
 *                'A' converted into 10,
 *                'B' converted into 11,
 *                'C' converted into 12,
 *                'D' converted into 13,
 *                'E' converted into 14,
 *                'F' converted into 15,
 *                'a' converted into 10,
 *                'b' converted into 11,
 *                'c' converted into 12,
 *                'd' converted into 13,
 *                'e' converted into 14,
 *                'f' converted into 15.
 */

unsigned digit_to_int(char32_t c);
#endif