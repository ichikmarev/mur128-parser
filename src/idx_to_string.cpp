/*
    File:    idx_to_string.cpp
    Author:  Ilya Chikmarev
*/

#include "../include/idx_to_string.h"
#include "../include/char_conv.h"
std::string idx_to_string(std::shared_ptr<Char_trie> t,
                          size_t                     idx,
                          std::string                default_value)
{
    auto u32str = t->get_string(idx);
    std::string s = u32string_to_utf8(u32str);
    return idx ? s : default_value;
}
