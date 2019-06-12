/*
    File:    intermediate_repres.h
    Author:  Ilya Chikmarev
*/

#ifndef INTERMEDIATE_REPRES_H
#define INTERMEDIATE_REPRES_H
#   include <cstddef>
#   include <vector>
#   include <quadmath.h>
namespace mur128m_ir{
    enum class Kind{
        Program,           Section,             Value,               MachineCommand,
        Logical_or_op,     Logical_and_op,      Logical_not_op,      Comparison_op,
        Bitwise_or_op,     Bitwise_and_op,      Bitwise_not,         Addition_op,
        Multiplication_op, Power_op,            Sharp_op,            Inc_dec_op,
        Unary_pm_op,       Address,             Data_address,        Size_of,
    };

    enum class Section_type_kind{
        Section_start, section_attr
    };

    enum class Simple_type_kind{
        Int8,      Int16,      Int32,     Int64,
        Int128,    Float32,    Float64,   Float80,
        Float128,  UInt8,      UInt16,    UInt32,
        UInt64,    UInt128,    Complex32, Complex64,
        Complex80, Complex128, Char,      String,
        Void
    };

    enum class Value_kind{
        Int_val,           Float_val,      Complex_val, Char_val,
        Str_val
    };

    enum class Logical_or_op_kind{
        Logical_or,          Logical_or_not,        Logical_xor
    };

    enum class Conditional_op_kind{
        Ordinary, Full
    };

    enum class Assignment_kind{
        Simple,                      Plus_assign,             Minus_assign,
        Mul_assign,                  Div_assign,              Remainder_assign,
        Copy,                        Bitwise_or_assign,       Bitwise_and_assign,
        Bitwise_xor_assign,          Logical_or_full,         Logical_and_full,
        Logical_and_assign,          Logical_xor_assign,      Power_assign,
        Left_shift_assign,           Right_shift_assign,      Bitwise_or_not_assign,
        Bitwise_and_not_assign,      Logical_or_not_full,     Logical_and_not_full,
        Logical_or_full_assign,      Logical_and_full_assign, Float_power_assign,
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

    enum class Multiplication_op_kind{
        Mul,
        Div,
        Mod,
    };

    enum class Power_op_kind{
        Power
    };

    enum class Unary_pm_op_kind{
        Unary_plus, Unary_minus
    };

    enum class Attribute_kind{
        Value,          Simple_type,       Enum_elem_code, Field_size,
        Func_attr,      Logical_or_op,     Conditional_op, Assignment_op
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
            Inc_dec_op_kind        inc_dec_op_kind_;
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
        Attribute attr_;
    };

    using Command = std::vector<IR>;
};
#endif
