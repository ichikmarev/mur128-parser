/*
    File:    category.h
    Author:  Ilya Chikmarev
*/

#ifndef CATEGORY_H
#define CATEGORY_H
namespace mur128m_scanner{
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
