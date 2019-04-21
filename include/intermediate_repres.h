/*
    File:    intermediate_repres.h
    Created: 21 April 2019 at 09:12 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef INTERMEDIATE_REPRES_H
#define INTERMEDIATE_REPRES_H
#   include <cstddef>
#   include <vector>
#   include <quadmath.h>
namespace lynx_ir{
    enum class Kind{
        Module,            Type,           Type_definition,     Simple_type,
        Tuple,             Pointer,        Reference,           Function_ptr,
        Array,             Enum,           Struct,              Algebraic_type,
        Value,             Argument_type,  Result_type,         Array_index,
        Elem_type,         Enum_elem,      Struct_field,        Variable,
        Constant,          Function,       Assignment,          Conditional_op,
        Logical_or_op,     Logical_and_op, Logical_not_op,      Comparison_op,
        Bitwise_or_op,     Bitwise_and_op, Bitwise_not,         Addition_op,
        Multiplication_op, Power_op,       Sharp_op
    };

    enum class Simple_type_kind{
        Bool8,    Bool16,    Bool32,  Bool64,
        Int8,     Int16,     Int32,   Int64,
        Int128,   Float32,   Float64, Float80,
        Float128, Complex32, Char,    String,
        Void
    };

    enum class Value_kind{
        Int_val,           Float_val,      Complex_val,
        Bool_val,          Char_val,       Str_val
    };

    enum class Function_attr_kind{
        Main, Pure, Ordinary
    };

    enum class Logical_or_op_kind{
        Logical_or,          Logical_or_not, Logical_or_full,
        Logical_or_not_full, Logical_xor
    };

    enum class Conditional_op_kind{
        Ordinary, Full
    };

    enum class Assignment_kind{
        Simple,                      Plus_assign,             Minus_assign,
        Mul_assign,                  Div_assign,              Remainder_assign,
        Copy,                        Bitwise_or_assign,       Bitwise_and_assign,
        Bitwise_xor_assign,          Logical_or_full,         Logical_and_full,
        Float_plus_assign,           Float_minus_assign,      Float_mul_assign,
        Float_div_assign,            Float_remainder_assign,  Logical_or_assign,
        Logical_and_assign,          Logical_xor_assign,      Power_assign,
        Left_shift_assign,           Right_shift_assign,      Bitwise_or_not_assign,
        Bitwise_and_not_assign,      Logical_or_not_full,     Logical_and_not_full,
        Logical_or_full_assign,      Logical_and_full_assign, Float_power_assign,
        Logical_or_not_assign,       Logical_and_not_assign,  Logical_or_not_full_assign,
        Logical_and_not_full_assign
    };

    enum class Logical_and_op_kind{
        Logical_and,      Logical_and_not,
        Logical_and_full, Logical_and_not_full
    };

    enum class Comparison_op_kind{
        Less,              Greater, Less_or_equals,
        Greater_or_equals, Equals,  Not_equals
    };

    enum class Bitwise_or_op_kind{
        Bitwise_or, Bitwise_or_not, Bitwise_xor
    };

    enum class Bitwise_and_op_kind{
        Bitwise_and, Bitwise_and_not,
        Left_shift,  Right_shift
    };

    enum class Addition_op_kind{
        Add, Float_add, Sub, Float_sub
    };

    enum class Attribute_kind{
        Value,          Simple_type,       Enum_elem_code, Field_size,
        Func_attr,      Logical_or_op,     Conditional_op, Assignment_op,
        Logical_and_op, Comparison_op,     Bitwise_or_op,  Bitwise_and_op,
        Addition_op,    Multiplication_op, Power_op
    };

    enum class Multiplication_op_kind{
        Mul, Float_mul,
        Div, Float_div,
        Mod, Float_mod
    };

    enum class Power_op_kind{
        Power, Float_power
    };

    struct Attribute{
        Attribute_kind kind_;
        union{
            Value_kind             vkind_;
            Simple_type_kind       stype_kind_;
            std::size_t            pointer_order_;
            std::size_t            enum_elem_code_;
            std::size_t            field_size_;
            Function_attr_kind     func_attr_;
            Assignment_kind        assignment_kind_;
            Conditional_op_kind    cond_op_kind_;
            Logical_or_op_kind     or_kind_;
            Logical_and_op_kind    and_kind_;
            Comparison_op_kind     cmp_op_kind_;
            Bitwise_or_op_kind     bitwise_or_op_kind_;
            Bitwise_and_op_kind    bitwise_and_op_kind_;
            Addition_op_kind       addition_op_kind_;
            Multiplication_op_kind multiplication_op_kind_;
            Power_op_kind          power_op_kind_;
        };
    };

    struct Args{
        Attribute   attr_;
        std::size_t first_;
        std::size_t second_;
        std::size_t third_;
        std::size_t next_;
    };

    struct IR{
        Kind kind_;
        union{
            Args              args_;
            unsigned __int128 int_val_;
            __float128        float_val_;
            __complex128      complex_val_;
            char32_t          char_val_;
            std::size_t       str_index_;
            bool              bool_val_;
        };
    };

    using Command = std::vector<IR>;
};
#endif