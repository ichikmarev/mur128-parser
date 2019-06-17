/*
    File:    mur128m_lexeme.h
    Author:  Chikmarev Ilya
*/
#ifndef mur128m_LEXEME_H
#define mur128m_LEXEME_H
#include <cstddef>
#include <quadmath.h>

namespace mur128m_scanner{
   enum class Lexem_code : uint16_t{
        Nothing,                     UnknownLexem,
        KwSection,                   KwReadable,
        KwWritable,                  KwExecutable,
        Id,                          Integer,
        KwFloat32,                   KwFloat64,
        KwFloat80,                   KwFloat128,
        KwInt32,                     KwInt64,
        KwInt128,		             KwInt8,
      	KwInt16,		             KwUInt32,
        KwUInt64,		             KwUInt128,
        KwUInt8,		             KwUInt16,
        Float32,                     Float64,
        Float80,                     Float128,
        KwComplex32,                 KwComplex64,
        KwComplex80,                 KwComplex128,
        Complex32,                   Complex64,
        Complex80,                   Complex128,
        String,                      Char,
        Sq_br_opened,                Round_br_opened,
        Sq_br_closed,                Round_br_closed,
        Less_than,                   Left_shift,
        Minus,                       Logical_not,
        Bitwise_not,                 Point,
        Semicolon,                   Plus,
        Mul,                         Div,
        Remainder,                   Bitwise_or,
        Bitwise_and,                 Greater_than,
        Right_shift,                 Curly_brace_opened,
        Curly_brace_closed,          Comma,
        Register,		     KwChar,
        KwFormat,		     KwString,
        RegisterBp, KwAnd,
        KwAbsf, KwAddi,
        KwAddf,
        KwAndn,KwCall,
        KwChfs,
        KwCmpf,KwCalls,
        KwCallr,KwCallz,
        KwCalln,KwCallp,
        KwCallsr,KwCallzr,
        KwCallge,  KwCallpr,
        KwCallger,KwCallnzr,
        KwCalller,KwDivf,
        KwDivis,KwDiviu,
        KwDivmodis,KwDivmodiu,
        KwFld1,KwFldz,
        KwFrac,KwJmp,
        KwJmpr,KwJmpge,
        KwJmple,KwJmpnz,
        KwJmppr,KwJmpsr,
        KwJmpzr,KwJmpger,
        KwJmpler, KwJmpnzr,
        KwOr,KwOrn,
        KwXor,KwXorn,
        KwLshift,KwLshifts,
        KwNot,KwTrap,
        KwRetz,KwReti,
        KwRetl,KwRetn,
        KwRetp,KwRetge,
        KwRetnz,KwRetag,
        KwRetai,KwRetap,
        KwRetal,KwRetaz,
        KwRetan,KwRets,
        KwRege,KwRetale,
        KwRetanz,KwRoundg,
        KwRoundn,KwRoundl,
        KwRoundt,KwRshift,
        KwRshifts,
        KwPop,KwPush,
        KwRegBp,KwRegF0,
        KwRegF1,KwRegF2,
        KwRegF3,KwRegF4,
        KwRegF5,KwRegF6,
        KwRegF7,KwRegF8,
        KwRegF9,KwRegF10,
        KwRegF11,KwRegF12,
        KwRegF13,KwRegF14,
        KwRegF15,KwRegF16,
        KwRegF17,KwRegF18,
        KwRegF19,KwRegF20,
        KwRegF21,KwRegF22,
        KwRegF23,KwRegF24,
        KwRegF25,KwRegF26,
        KwRegF27,KwRegF28,
        KwRegF29,KwRegF30,
        KwRegF31,KwRegR0,
    	KwRegR1,KwRegR2,
        KwRegR3,KwRegR4,
    	KwRegR5,KwRegR6,
    	KwRegR7,KwRegR8,
    	KwRegR9,KwRegR10,
    	KwRegR11,KwRegR12,
    	KwRegR13,KwRegR14,
    	KwRegR15,KwRegR16,
    	KwRegR17,KwRegR18,
    	KwRegR19,KwRegR20,
    	KwRegR21,KwRegR22,
    	KwRegR23,KwRegR24,
    	KwRegR25,KwRegR26,
    	KwRegR27,KwRegR28,
    	KwRegR29,KwRegR30,
    	KwRegR31,KwRegSp
    };

    struct Lexeme_info{
        Lexem_code code_;
        union{
            unsigned __int128 int_val_;
            __float128        float_val_;
            __complex128      complex_val_;
            char32_t          char_val_;
            std::size_t       str_index_;
            std::size_t       id_index_;
        };
    };
};
#endif
