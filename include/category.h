/*
    File:    category.h
    Created: 19 March 2019 at 07:22 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef CATEGORY_H
#define CATEGORY_H
namespace lynx_scanner{
    enum class Category : uint32_t{
        Spaces,       Other,            Id_begin,
        Id_body,      Keyword_begin,    Delimiter_begin,
        Double_quote, Letters_Xx,       Letters_Bb,
        Letters_Oo,   Single_quote,     Dollar,
        Hex_digit,    Oct_digit,        Bin_digit,
        Dec_digit,    Zero,             Letters_Ee,
        Plus_minus,   Precision_letter, Digits_1_to_9,
        Point
    };
};
#endif