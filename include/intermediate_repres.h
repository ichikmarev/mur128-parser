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
        Module,     Type,      Type_definition, Simple_type,
        Tuple,      Pointer,   Reference,       Function_ptr,
        Array,      Enum,      Struct,          Algebraic_type,
        Int_val,    Float_val, Complex_val,     Bool_val,
        Char_val,   Str_val,   Argument_type,   Result_type,
        Array_index
    };

    enum class Simple_type_kind{
        Bool8,    Bool16,    Bool32,  Bool64,
        Int8,     Int16,     Int32,   Int64,
        Int128,   Float32,   Float64, Float80,
        Float128, Complex32, Char,    String,
        Void
    };

    struct Args{
        std::size_t first;
        std::size_t second;
        std::size_t third;
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