/*
    File:    lynx_scaner_delimiter_table.cpp
    Created: 25 March 2019 at 17:35 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include "../include/lynx_scaner_delimiter_table.h"

namespace lynx_scanner{
    const trans_table::Elem<Lexem_code> delimiters_jump_table[] = {
        {const_cast<char32_t*>(U":"),      Lexem_code::Sq_br_opened,                 1}, // 0:   [
        {const_cast<char32_t*>(U""),       Lexem_code::Sq_br_colon_opened,           0}, // 1:   [:

        {const_cast<char32_t*>(U":"),      Lexem_code::Round_br_opened,              3}, // 2:   (
        {const_cast<char32_t*>(U""),       Lexem_code::Tuple_begin,                  0}, // 3:   (:

        {const_cast<char32_t*>(U"]):="),   Lexem_code::Colon,                        5}, // 4:   :
        {const_cast<char32_t*>(U""),       Lexem_code::Sq_br_colon_closed,           0}, // 5:   :]
        {const_cast<char32_t*>(U""),       Lexem_code::Tuple_end,                    0}, // 6:   :)
        {const_cast<char32_t*>(U""),       Lexem_code::Resolution,                   0}, // 7:   ::
        {const_cast<char32_t*>(U""),       Lexem_code::Copy,                         0}, // 8:   :=

        {const_cast<char32_t*>(U""),       Lexem_code::Sq_br_closed,                 0}, // 9:   ]

        {const_cast<char32_t*>(U""),       Lexem_code::Round_br_closed,              0}, // 10:  )

        {const_cast<char32_t*>(U"-=<"),    Lexem_code::Less_than,                   12}, // 11:  <
        {const_cast<char32_t*>(U""),       Lexem_code::Set_field,                    0}, // 12:  <-
        {const_cast<char32_t*>(U""),       Lexem_code::Less_or_equals_than,          0}, // 13:  <=
        {const_cast<char32_t*>(U"="),      Lexem_code::Left_shift,                  15}, // 14:  <<
        {const_cast<char32_t*>(U""),       Lexem_code::Left_shift_assign,            0}, // 15:  <<=

        {const_cast<char32_t*>(U">-.="),   Lexem_code::Minus,                       17}, // 16:  -
        {const_cast<char32_t*>(U""),       Lexem_code::Component_is,                 0}, // 17:  ->
        {const_cast<char32_t*>(U"<"),      Lexem_code::Prev,                        21}, // 18:  --
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_sub,                   22}, // 19:  -.
        {const_cast<char32_t*>(U""),       Lexem_code::Minus_assign,                 0}, // 20:  -=
        {const_cast<char32_t*>(U""),       Lexem_code::Prev_with_wrapping,           0}, // 21:  --<
        {const_cast<char32_t*>(U""),       Lexem_code::Float_minus_assign,           0}, // 22:  -.=

        {const_cast<char32_t*>(U"=|&"),    Lexem_code::Logical_not,                 24}, // 23:  !
        {const_cast<char32_t*>(U""),       Lexem_code::Not_equals,                   0}, // 24:  !=
        {const_cast<char32_t*>(U"|"),      Lexem_code::Maybe_logical_or_not,        27}, // 25:  !|
        {const_cast<char32_t*>(U"&"),      Lexem_code::Maybe_logical_and_not,       28}, // 26:  !&
        {const_cast<char32_t*>(U".="),     Lexem_code::Logical_or_not,              29}, // 27:  !||
        {const_cast<char32_t*>(U".="),     Lexem_code::Logical_and_not,             31}, // 28:  !&&
        {const_cast<char32_t*>(U"="),      Lexem_code::Logical_or_not_full,         33}, // 29:  !||.
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_or_not_assign,        0}, // 30:  !||=
        {const_cast<char32_t*>(U"="),      Lexem_code::Logical_and_not_full,        34}, // 31:  !&&.
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_and_not_assign,       0}, // 32:  !&&=
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_or_not_full_assign,   0}, // 33:  !||.=
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_and_not_full_assign,  0}, // 34:  !&&.=

        {const_cast<char32_t*>(U"|&"),     Lexem_code::Bitwise_not,                 36}, // 35:  ~
        {const_cast<char32_t*>(U"="),      Lexem_code::Bitwise_or_not,              38}, // 36:  ~|
        {const_cast<char32_t*>(U"="),      Lexem_code::Bitwise_and_not,             39}, // 37:  ~&
        {const_cast<char32_t*>(U""),       Lexem_code::Bitwise_or_not_assign,        0}, // 38:  ~|=
        {const_cast<char32_t*>(U""),       Lexem_code::Bitwise_and_not_assign,       0}, // 39:  ~&=

        {const_cast<char32_t*>(U"^="),     Lexem_code::Bitwise_xor,                 41}, // 40:  ^
        {const_cast<char32_t*>(U"="),      Lexem_code::Logical_xor,                 43}, // 41:  ^^
        {const_cast<char32_t*>(U""),       Lexem_code::Bitwise_xor_assign,           0}, // 42:  ^=
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_xor_assign,           0}, // 43:  ^^=

        {const_cast<char32_t*>(U"@"),      Lexem_code::At,                          45}, // 44:  @
        {const_cast<char32_t*>(U""),       Lexem_code::Data_address,                 0}, // 45:  @@

        {const_cast<char32_t*>(U".|"),     Lexem_code::Point,                       47}, // 46:  .
        {const_cast<char32_t*>(U""),       Lexem_code::Range,                        0}, // 47:  ..
        {const_cast<char32_t*>(U"."),      Lexem_code::Maybe_component_or,          49}, // 48:  .|
        {const_cast<char32_t*>(U""),       Lexem_code::Component_or,                 0}, // 49:  .|.

        {const_cast<char32_t*>(U"="),      Lexem_code::Assignment,                  51}, // 50:  =
        {const_cast<char32_t*>(U""),       Lexem_code::Equals,                       0}, // 51:  ==

        {const_cast<char32_t*>(U""),       Lexem_code::Semicolon,                    0}, // 52:  ;

        {const_cast<char32_t*>(U"#"),      Lexem_code::Sharp,                       54}, // 53:
        {const_cast<char32_t*>(U"#"),      Lexem_code::Size_of,                     55}, // 54:
        {const_cast<char32_t*>(U""),       Lexem_code::Data_size,                    0}, // 55:

        {const_cast<char32_t*>(U"|+.="),   Lexem_code::Plus,                        57}, // 56:  +
        {const_cast<char32_t*>(U""),       Lexem_code::Cycle_name_prefix,            0}, // 57:  +|
        {const_cast<char32_t*>(U"<"),      Lexem_code::Next,                        61}, // 58:  ++
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_add,                   62}, // 59:  +.
        {const_cast<char32_t*>(U""),       Lexem_code::Plus_assign,                  0}, // 60:  +=
        {const_cast<char32_t*>(U""),       Lexem_code::Next_with_wrapping,           0}, // 61:  ++<
        {const_cast<char32_t*>(U""),       Lexem_code::Float_plus_assign,            0}, // 62:  +.=

        {const_cast<char32_t*>(U".*=/"),   Lexem_code::Mul,                          64}, // 63:  *
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_mul,                    68}, // 64:  *.
        {const_cast<char32_t*>(U".="),     Lexem_code::Power,                        69}, // 65:  **
        {const_cast<char32_t*>(U""),       Lexem_code::Mul_assign,                    0}, // 66:  *=
        {const_cast<char32_t*>(U""),       Lexem_code::Comment_end,                   0}, // 67:  */
        {const_cast<char32_t*>(U""),       Lexem_code::Float_mul_assign,              0}, // 68:  *.=
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_power,                  71}, // 69:  **.
        {const_cast<char32_t*>(U""),       Lexem_code::Power_assign,                  0}, // 70:  **=
        {const_cast<char32_t*>(U""),       Lexem_code::Float_power_assign,            0}, // 71:  **.=

        {const_cast<char32_t*>(U".=*"),    Lexem_code::Div,                          73}, // 72:  /
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_div,                    76}, // 73:  /.
        {const_cast<char32_t*>(U""),       Lexem_code::Div_assign,                    0}, // 74:  /=
        {const_cast<char32_t*>(U""),       Lexem_code::Comment_begin,                 0}, // 75:  /*
        {const_cast<char32_t*>(U""),       Lexem_code::Float_div_assign,              0}, // 76:  /.=

        {const_cast<char32_t*>(U".="),     Lexem_code::Remainder,                    78}, // 77:  %
        {const_cast<char32_t*>(U"="),      Lexem_code::Float_remainder,              80}, // 78:  %.
        {const_cast<char32_t*>(U""),       Lexem_code::Remainder_assign,              0}, // 79:  %=
        {const_cast<char32_t*>(U""),       Lexem_code::Float_remainder_assign,        0}, // 80:  %.=

        {const_cast<char32_t*>(U"|="),     Lexem_code::Bitwise_or,                   82}, // 81:  |
        {const_cast<char32_t*>(U".="),     Lexem_code::Logical_or,                   84}, // 82:  ||
        {const_cast<char32_t*>(U""),       Lexem_code::Bitwise_or_assign,             0}, // 83:  |=
        {const_cast<char32_t*>(U"="),      Lexem_code::Logical_or_full,              86}, // 84:  ||.
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_or_assign,             0}, // 85:  ||=
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_or_full_assign,        0}, // 86:  ||.=

        {const_cast<char32_t*>(U"&="),     Lexem_code::Bitwise_and,                  88}, // 87:  &
        {const_cast<char32_t*>(U".="),     Lexem_code::Logical_and,                  90}, // 88:  &&
        {const_cast<char32_t*>(U""),       Lexem_code::Bitwise_and_assign,            0}, // 89:  &=
        {const_cast<char32_t*>(U"="),      Lexem_code::Logical_and_full,             92}, // 90:  &&.
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_and_assign,            0}, // 91:  &&=
        {const_cast<char32_t*>(U""),       Lexem_code::Logical_and_full_assign,       0}, // 92:  &&.=

        {const_cast<char32_t*>(U">="),     Lexem_code::Greater_than,                 94}, // 93:  >
        {const_cast<char32_t*>(U"="),      Lexem_code::Right_shift,                  96}, // 94:  >>
        {const_cast<char32_t*>(U""),       Lexem_code::Greater_or_equals_than,        0}, // 95:  >=
        {const_cast<char32_t*>(U""),       Lexem_code::Right_shift_assign,            0}, // 96:  >>=

        {const_cast<char32_t*>(U"."),      Lexem_code::Cond_op,                       98}, // 97:  ?
        {const_cast<char32_t*>(U""),       Lexem_code::Cond_op_full,                   0}, // 98:  ?.

        {const_cast<char32_t*>(U"."),      Lexem_code::Curly_brace_opened,           100}, // 99:  {
        {const_cast<char32_t*>(U"."),      Lexem_code::Maybe_component,              101}, // 100: {.
        {const_cast<char32_t*>(U"}"),      Lexem_code::Maybe_component,              102}, // 101: {..
        {const_cast<char32_t*>(U""),       Lexem_code::Component,                      0}, // 102: {..}

        {const_cast<char32_t*>(U""),       Lexem_code::Curly_brace_closed,             0}, // 103: }

        {const_cast<char32_t*>(U""),       Lexem_code::Comma,                          0}  // 104: ,
    };
};