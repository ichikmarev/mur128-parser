/*
    File:    mur128m_scaner.cpp
    Author:  Chikmarev Ilya
*/

#include <string>
#include <cstdio>
#include <quadmath.h>
#include "../include/mur128m_scaner.h"
#include "../include/mur128m_lexeme.h"
#include "../include/knuth_find.h"
#include "../include/belongs.h"
#include "../include/search_char.h"
#include "../include/mysize.h"
#include "../include/mur128m_scaner_keyword_table.h"
#include "../include/keyword_init_table.h"
#include "../include/get_init_state.h"
#include "../include/print_char32.h"
#include "../include/idx_to_string.h"
#include "../include/digit_to_int.h"
#include "../include/float128_to_string.h"
#include "../include/mur128m_scaner_delimiter_table.h"
#include "../include/delimiter_init_table.h"
#include "../include/int128_to_str.h"

namespace mur128m_scanner{
    static const Segment_with_value<char32_t, uint64_t> categories_table[] = {
    	{{U'b', U'b'},  4380      },    {{U'8', U'9'},  1085448   },  {{U'r', U'u'},  28        },    
    	{{U'+', U'+'},  262176    },    {{U'O', U'O'},  524       },  {{U'l', U'n'},  28        },    
    	{{U'{', U'~'},  32        },    {{U'$', U'$'},  2048      },  {{U'/', U'/'},  32        },    
    	{{U'C', U'D'},  4108      },    {{U'[', U'['},  32        },  {{U'f', U'f'},  528412    },    
    	{{U'p', U'p'},  28        },    {{U'x', U'x'},  524444    },  {{U'А', U'я'},  12        },  
    	{{U'!', U'!'},  32        },    {{U'\'', U'\''},  1024      },  {{U'-', U'-'},  262176    },    
    	{{U'1', U'1'},  1110024   },    {{U'A', U'A'},  4108      },  {{U'F', U'F'},  4108      },    
    	{{U'X', U'X'},  140       },    {{U'_', U'_'},  12        },  {{U'd', U'd'},  528412    },    
    	{{U'i', U'j'},  28        },    {{U'o', U'o'},  540       },  {{U'q', U'q'},  524300    },    
    	{{U'v', U'w'},  12        },    {{U'y', U'z'},  12        },  {{U'Ё', U'Ё'},  12        },  
    	{{U'ё', U'ё'},  12        },  	{{   1,   32},  1         },  {{U'"', U'"'},  64        },    
    	{{U'%', U'&'},  32        },    {{U'(', U'*'},  32        },  {{U',', U','},  32        },    
    	{{U'.', U'.'},  2097152   },    {{U'0', U'0'},  126984    },  {{U'2', U'7'},  1093640   },    
    	{{U':', U'>'},  32        },    {{U'B', U'B'},  4364      },  {{U'E', U'E'},  135180    },    
    	{{U'G', U'N'},  12        },    {{U'P', U'W'},  12        },  {{U'Y', U'Z'},  12        },    
    	{{U']', U'^'},  32        },    {{U'a', U'a'},  4124      },  {{U'c', U'c'},  4124      },    
    	{{U'e', U'e'},  135180    },    {{U'g', U'h'},  12        },  {{U'k', U'k'},  12        }
};
    static constexpr size_t   num_of_elems_in_categories_table = size(categories_table);
    static constexpr uint64_t other_as_int = static_cast<uint64_t>(Category::Other);

    static uint64_t get_categories_set(char32_t c)
    {
        auto t = knuth_find(categories_table,
                            categories_table + num_of_elems_in_categories_table,
                            c);
        return t.first ? categories_table[t.second].value :
                         (1ULL << static_cast<uint64_t>(Category::Other));
    }


    static inline uint64_t belongs(Category cat, uint64_t set_of_categories)
    {
        return ::belongs(static_cast<uint64_t>(cat), set_of_categories);
    }

    Scanner::Automaton_proc Scanner::procs_[] = {
        &Scanner::start_proc,     &Scanner::unknown_proc,
        &Scanner::keyword_proc,   &Scanner::id_proc,
        &Scanner::number_proc,    &Scanner::delimiter_proc,
        &Scanner::string_proc,    &Scanner::comment_proc,
        &Scanner::character_proc, &Scanner::encoded_character_proc
    };

    bool Scanner::start_proc()
    {
        state_  = -1;
        bool t  = true;
        /* For an automaton that processes a lexeme, the state with the number (-1)
        * is the state in which this machine is initialized. */
        if(belongs(Category::Spaces, char_categories_)){
            if(ch_ == U'\n'){
                loc_->pos_.line_pos_ = 1;
                (loc_->pos_.line_no_)++;
            }else{
                (loc_->pos_.line_pos_) += ch_ != U'\r';
            }
            return t;
        }
        lexeme_pos_.begin_pos_ = loc_->pos_;
        lexeme_pos_.end_pos_   = loc_->pos_;
        lexeme_begin_          = loc_->pcurrent_char_;
        comment_level_         = 0;
        if(belongs(Category::Keyword_begin, char_categories_)){
            automaton_           = Automaton_name::Keyword;
            token_.lexeme_.code_ = Lexem_code::Id;
            (loc_->pcurrent_char_)--;
            buffer_.clear() ;
            return true;
        }
        if(belongs(Category::Id_begin, char_categories_)){
            automaton_           = Automaton_name::Id;
            token_.lexeme_.code_ = Lexem_code::Id;
            (loc_->pcurrent_char_)--;
            buffer_.clear() ;
            return true;
        }
        if(belongs(Category::Delimiter_begin, char_categories_)){
            automaton_ = Automaton_name::Delimiter;
            (loc_->pcurrent_char_)--;
            return true;
        }
        if(belongs(Category::Dec_digit, char_categories_)){
            automaton_                  = Automaton_name::Number;
            int_part_                   = 0;
            frac_part_                  = 0.0q;
            exponent_                   = 0;
            exponent_sign_              = 1;
            base_                       = 10;
            num_of_digits_in_frac_part_ = 0;
            is_float_                   = false;
            token_.lexeme_.code_        = Lexem_code::Integer;
            (loc_->pcurrent_char_)--;
            return true;
        }
        if(ch_ == U'\''){
            automaton_                  = Automaton_name::Character;
            token_.lexeme_.code_        = Lexem_code::Char;
            (loc_->pcurrent_char_)--;
            return true;
        }
        if(ch_ == U'$'){
            automaton_                  = Automaton_name::Encoded_character;
            token_.lexeme_.code_        = Lexem_code::Char;
            char_code_                  = 0;
            base_                       = 10;
            (loc_->pcurrent_char_)--;
            buffer_.clear();
            return true;
        }
        if(ch_ == U'\"'){
            automaton_                  = Automaton_name::String;
            token_.lexeme_.code_        = Lexem_code::String;
            char_code_                  = 0;
            base_                       = 10;
            (loc_->pcurrent_char_)--;
            buffer_.clear();
        }
        return t;
    }

    bool Scanner::unknown_proc()
    {
        return belongs(Category::Other, char_categories_);
    }

    bool Scanner::keyword_proc()
    {
        bool t = false;
        if(state_ != -1){
            auto elem            = keywords_jump_table[state_];
            token_.lexeme_.code_ = elem.code_;
            int y                = search_char(ch_, elem.symbols_);
            if(y != THERE_IS_NO_CHAR){
                buffer_    += ch_;
                state_     =  elem.first_state_ + y;
                t          =  true;
                lexeme_pos_.end_pos_.line_pos_++;
                (loc_->pos_.line_pos_)++;
            }else if(belongs(Category::Id_body, char_categories_)){
                buffer_    += ch_;
                t          =  true;
                automaton_ =  Automaton_name::Id;
                lexeme_pos_.end_pos_.line_pos_++;
                (loc_->pos_.line_pos_)++;
            }else{
                (loc_->pcurrent_char_)--;
            }
            return t;
        }
        buffer_              += ch_;
        state_               =  get_init_state(ch_,
                                               keyword_init_table,
                                               keyword_init_table_size);
        token_.lexeme_.code_ =  keywords_jump_table[state_].code_;
        t                    =  true;
        lexeme_pos_.end_pos_.line_pos_++;
        (loc_->pos_.line_pos_)++;
        return t;
    }

    bool Scanner::id_proc()
    {
        bool t = true;
        /* The variable t is true if the current identifier has not yet
         * been fully read, and false otherwise. */
        if(-1 == state_){
            buffer_ += ch_; state_ = 0;
            lexeme_pos_.end_pos_.line_pos_++;
            (loc_->pos_.line_pos_)++;
            return t;
        }
        t = belongs(Category::Id_body, char_categories_);
        if(t){
            buffer_ += ch_;
            lexeme_pos_.end_pos_.line_pos_++;
            (loc_->pos_.line_pos_)++;
        }else{
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    /**
     * A regular expression for numbers of the programming language МУР128 can be written
     * in the form
     *    abc(d?c)* | (a|e)(d?(a|e))*(f(a|e)(d?(a|e))*)?(gh?(a|e)(d?(a|e))*)?j?i?   (1)
     * where
     *    a    U'0'
     *    b    base_marker (one of letters B, b, O, o, X, x)
     *    c    digit (binary digit for letters B and b,
     *                octal digit for letters O and o,
     *                and hexadecimal digit for letters X and x)
     *    d    ' (single quote)
     *    e    U'1' ... U'9'
     *    f    .  (point)
     *    g    E or e
     *    h    + or -
     *    i    i
     *    j    one of letters f, d, x, q (default suffix is d)
     *
     * If we construct the minimal DFA for (1), we obtain the following transition
     * table:
     *
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * | State | a | b | c | d | e | f | g | h | i | j |            Remark            |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   A   | B |   |   |   | C |   |   |   |   |   | Initial state.               |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   B   | C | E |   | F | C | H | I |   | J | K | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   C   | C |   |   | F | C | H | I |   | J | K | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   E   |   |   | L |   |   |   |   |   |   |   |                              |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   F   | C |   |   |   | C |   |   |   |   |   |                              |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   H   | M |   |   |   | M |   |   |   |   |   |                              |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   I   | O |   |   |   | O |   |   | Q |   |   |                              |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   J   |   |   |   |   |   |   |   |   |   |   | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   K   |   |   |   |   |   |   |   |   | J |   | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   L   |   |   | L | E |   |   |   |   |   |   | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   M   | M |   |   | H | M |   | I |   | J | K | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   O   | O |   |   | Q | O |   |   |   | J | K | Final state.                 |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     * |   Q   | O |   |   |   | O |   |   |   |   |   |                              |
     * |-------|---|---|---|---|---|---|---|---|---|---|------------------------------|
     *
     * More meanigful names for states:
     *
     * |-------|--------------------------------------|
     * | State |          Meaningful name             |
     * |-------|--------------------------------------|
     * |   A   | Initial_state                        |
     * |-------|--------------------------------------|
     * |   B   | Maybe_nondecimal                     |
     * |-------|--------------------------------------|
     * |   C   | Decimal_int                          |
     * |-------|--------------------------------------|
     * |   E   | Base_marker                          |
     * |-------|--------------------------------------|
     * |   F   | Digits_separator                     |
     * |-------|--------------------------------------|
     * |   H   | Fractional_part_begin                |
     * |-------|--------------------------------------|
     * |   I   | Power_of_ten                         |
     * |-------|--------------------------------------|
     * |   J   | Complex_suffix                       |
     * |-------|--------------------------------------|
     * |   K   | Precision_suffix                     |
     * |-------|--------------------------------------|
     * |   L   | Non_decimal_digit                    |
     * |-------|--------------------------------------|
     * |   M   | Fractional_part_digit                |
     * |-------|--------------------------------------|
     * |   O   | Digit_of_power_of_ten                |
     * |-------|--------------------------------------|
     * |   Q   | Power_signum                         |
     * |-------|--------------------------------------|
     *
     */

    enum Number_state{
        Initial_state = -1, Maybe_nondecimal,      Decimal_int,
        Base_marker,        Digits_separator,      Fractional_part_begin,
        Power_of_ten,       Complex_suffix,        Precision_suffix,
        Non_decimal_digit,  Fractional_part_digit, Digit_of_power_of_ten,
        Power_signum
    };

    void Scanner::set_float_precision()
    {
        switch(ch_){
            case U'f':
                token_.lexeme_.code_ = Lexem_code::Float32;
                break;
            case U'd':
                token_.lexeme_.code_ = Lexem_code::Float64;
                break;
            case U'x':
                token_.lexeme_.code_ = Lexem_code::Float80;
                break;
            case U'q':
                token_.lexeme_.code_ = Lexem_code::Float128;
                break;
        }
    }

    void Scanner::make_integer()
    {
        token_.lexeme_.code_    = Lexem_code::Integer;
        token_.lexeme_.int_val_ = int_part_;
    }

    static const char* unexpected_not_digit             =
        "Error at %zu:%zu: expected digit.\n";
    static const char* expected_digit_or_pm             =
        "Error at %zu:%zu: expected decimal digit, plus, or minus.\n";
    static const char* expected_logical_or_not          =
        "Error at %zu:%zu: expected !||\n";
    static const char* expected_logical_and_not         =
        "Error at %zu:%zu: expected !&&\n";
    static const char* expected_component_or            =
        "Error at %zu:%zu: expected .|.\n";
    static const char* expected_digit_of_char_code      =
        "Error at %zu:%zu: expected a digit of a character code.\n";
    static const char* expected_quote                   =
        "Error at %zu:%zu: expected a single quote.\n";
    static const char* unexpected_end_of_char_literal   =
        "Error at %zu:%zu: unexpected end of a character literal.\n";
    static const char* unexpected_end_of_string_literal =
        "Error at %zu:%zu: unexpected end of a string literal.\n";
    static const char* unexpected_char_in_char_code   =
        "Error at %zu:%zu: unexpected character in character code at "
        "processing of string literal.\n";

    template<typename... T>
    static void print_diagnostic(const char* msg, T... args)
    {
        printf(msg, args...);
    }

    __float128 Scanner::make_float()
    {
        __float128 result     =  int_part_ +
                                 frac_part_ * powq(10.0q, -num_of_digits_in_frac_part_);
        __float128 result_exp =  exponent_;
        result_exp            *= exponent_sign_;
        result                *= powq(10.0q, result_exp);
        return result;
    }

    void Scanner::set_complex_precision()
    {
        switch(token_.lexeme_.code_){
            case Lexem_code::Float32:
                token_.lexeme_.code_ = Lexem_code::Complex32;
                break;
            case Lexem_code::Float64:
                token_.lexeme_.code_ = Lexem_code::Complex64;
                break;
            case Lexem_code::Float80:
                token_.lexeme_.code_ = Lexem_code::Complex80;
                break;
            case Lexem_code::Float128:
                token_.lexeme_.code_ = Lexem_code::Complex128;
                break;
            default:
                ;
        }
    }

    __complex128 Scanner::make_complex()
    {
        __complex128 result;
        __float128   float_result = make_float();
        result                    = {0.0q, float_result};
        return result;
    }

    bool Scanner::maybe_nondecimal_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            int_part_        = int_part_ * base_ + digit_to_int(ch_);
            state_           = Decimal_int;
        }else if(belongs(Category::Letters_Bb, char_categories_)){
            base_            = 2;
            digits_category_ = Category::Bin_digit;
            state_           = Base_marker;
        }else if(belongs(Category::Letters_Oo, char_categories_)){
            base_            = 8;
            digits_category_ = Category::Oct_digit;
            state_           = Base_marker;
        }else if(belongs(Category::Letters_Xx, char_categories_)){
            base_            = 16;
            digits_category_ = Category::Hex_digit;
            state_           = Base_marker;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_           = Digits_separator;
        }else if(belongs(Category::Point, char_categories_)){
            state_           = Fractional_part_begin;
        }else if(belongs(Category::Letters_Ee, char_categories_)){
            state_           = Power_of_ten;
        }else if(belongs(Category::Precision_letter, char_categories_)){
            state_           = Precision_suffix;
            set_float_precision();
        }else if(ch_ == U'i'){
            state_               = Complex_suffix;
            token_.lexeme_.code_ = Lexem_code::Complex64;
        }else{
            make_integer();
            result               = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::decimal_int_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            int_part_ = int_part_ * base_ + digit_to_int(ch_);
            state_    = Decimal_int;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_    = Digits_separator;
        }else if(belongs(Category::Point, char_categories_)){
            state_    = Fractional_part_begin;
        }else if(belongs(Category::Letters_Ee, char_categories_)){
            state_    = Power_of_ten;
        }else if(belongs(Category::Precision_letter, char_categories_)){
            state_    = Precision_suffix;
            set_float_precision();
        }else if(ch_ == U'i'){
            state_               = Complex_suffix;
            token_.lexeme_.code_ = Lexem_code::Complex64;
        }else{
            make_integer();
            result    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::base_marker_proc()
    {
        bool result = true;
        if(belongs(digits_category_, char_categories_)){
            int_part_ = int_part_ * base_ + digit_to_int(ch_);
            state_    = Non_decimal_digit;
        }else{
            make_integer();
            result    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::digits_separator_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            int_part_        = int_part_ * base_ + digit_to_int(ch_);
            state_           = Decimal_int;
        }else{
            print_diagnostic(unexpected_not_digit,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            make_integer();
            result           = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::non_decimal_digit_proc()
    {
        bool result = true;
        if(belongs(digits_category_, char_categories_)){
            int_part_ = int_part_ * base_ + digit_to_int(ch_);
            state_    = Non_decimal_digit;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_    = Base_marker;
        }else{
            make_integer();
            result    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::fractional_part_begin_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            num_of_digits_in_frac_part_++;
            frac_part_       = frac_part_ * 10.0q + digit_to_int(ch_);
            state_           = Fractional_part_digit;
        }else{
            print_diagnostic(unexpected_not_digit,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.code_      = Lexem_code::Float64;
            token_.lexeme_.float_val_ = make_float();
            result            = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::power_of_ten_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            exponent_      = exponent_ * 10 + digit_to_int(ch_);
            state_         = Digit_of_power_of_ten;
        }else if(belongs(Category::Plus_minus, char_categories_)){
            exponent_sign_ = (ch_ == U'+') ? 1 : (-1);
            state_         = Power_signum;
        }else{
            print_diagnostic(expected_digit_or_pm,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.code_      = Lexem_code::Float64;
            token_.lexeme_.float_val_ = make_float();
            result         = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::fractional_part_digit_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            num_of_digits_in_frac_part_++;
            frac_part_                = frac_part_ * 10.0q + digit_to_int(ch_);
            state_                    = Fractional_part_digit;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_                    = Fractional_part_begin;
        }else if(belongs(Category::Letters_Ee, char_categories_)){
            state_                    = Power_of_ten;
        }else if(belongs(Category::Precision_letter, char_categories_)){
            state_                    = Precision_suffix;
            set_float_precision();
        }else if(ch_ == U'i'){
            state_                    = Complex_suffix;
            token_.lexeme_.code_      = Lexem_code::Complex64;
        }else{
            token_.lexeme_.code_      = Lexem_code::Float64;
            token_.lexeme_.float_val_ = make_float();
            result                    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return result;
    }

    bool Scanner::digit_of_power_of_ten_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            exponent_                 = exponent_ * 10 + digit_to_int(ch_);
            state_                    = Digit_of_power_of_ten;
        }else if(belongs(Category::Single_quote, char_categories_)){
            exponent_sign_            = (ch_ == U'+') ? 1 : (-1);
            state_                    = Power_signum;
        }else if(belongs(Category::Precision_letter, char_categories_)){
            state_                    = Precision_suffix;
            set_float_precision();
        }else if(ch_ == U'i'){
            state_                    = Complex_suffix;
            token_.lexeme_.code_      = Lexem_code::Complex64;
        }else{
            token_.lexeme_.code_      = Lexem_code::Float64;
            token_.lexeme_.float_val_ = make_float();
            result                    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }

        return result;
    }

    bool Scanner::power_signum_proc()
    {
        bool result = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            exponent_                 = exponent_ * 10 + digit_to_int(ch_);
            state_                    = Digit_of_power_of_ten;
        }else{
            print_diagnostic(unexpected_not_digit,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.code_      = Lexem_code::Float64;
            token_.lexeme_.float_val_ = make_float();
            result                    = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }

        return result;
    }

    bool Scanner::precision_suffix_proc()
    {
        bool result = true;
        if(ch_ == U'i'){
            state_                    = Complex_suffix;
        }else{
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
            token_.lexeme_.float_val_ = make_float();
            result                    = false;
        }
        return result;
    }

    bool Scanner::number_proc()
    {
        bool t = true;
        lexeme_pos_.end_pos_.line_pos_++;
        (loc_->pos_.line_pos_)++;
        switch(state_){
            case Initial_state:
                state_    = (ch_ == U'0') ? Maybe_nondecimal : Decimal_int;
                int_part_ = digit_to_int(ch_);
                break;
            case Maybe_nondecimal:
                t = maybe_nondecimal_proc();
                break;
            case Decimal_int:
                t = decimal_int_proc();
                break;
            case Base_marker:
                t = base_marker_proc();
                break;
            case Digits_separator:
                t = digits_separator_proc();
                break;
            case Fractional_part_begin:
                t = fractional_part_begin_proc();
               break;
            case Power_of_ten:
                t = power_of_ten_proc();
                break;
            case Complex_suffix:
                (loc_->pos_.line_pos_)--;
                (loc_->pcurrent_char_)--;
                set_complex_precision();
                token_.lexeme_.complex_val_ = make_complex();
                t                           = false;
                break;
            case Precision_suffix:
                t = precision_suffix_proc();
                break;
            case Non_decimal_digit:
                t = non_decimal_digit_proc();
                break;
            case Fractional_part_digit:
                t = fractional_part_digit_proc();
                break;
            case Digit_of_power_of_ten:
                t = digit_of_power_of_ten_proc();
                break;
            case Power_signum:
                t = power_signum_proc();
                break;
            default:
                ;
        }
        return t;
    }

    bool Scanner::delimiter_proc()
    {
        bool t = false;
        if(state_ != -1){
            auto elem            = delimiters_jump_table[state_];
            auto code            = elem.code_;
            token_.lexeme_.code_ = code;
            int y                = search_char(ch_, elem.symbols_);
            if(y != THERE_IS_NO_CHAR){
                state_ =  elem.first_state_ + y;
                t      =  true;
                lexeme_pos_.end_pos_.line_pos_++;
                (loc_->pos_.line_pos_)++;
            }
            return t;
        }

        state_               =  get_init_state(ch_,
                                               delimiter_init_table,
                                               delimiter_init_table_size);
        token_.lexeme_.code_ =  delimiters_jump_table[state_].code_;
        t                    =  true;
        lexeme_pos_.end_pos_.line_pos_++;
        (loc_->pos_.line_pos_)++;

        return t;
    }

    /**
     * A regular expression for quoted string literals of the programming language МУР128
     * can be written in the form
     *     g(h|gg)*g, (0)
     * where
     *    g    " (double quote)
     *    h    character which is not single quote
     *
     * If we construct the minimal DFA for (0), we obtain the following transition table:
     *
     * |-------|---|---|------------------------------|
     * | State | g | h |            Remark            |
     * |-------|---|---|------------------------------|
     * |   A   | B |   | Initial state.               |
     * |-------|---|---|------------------------------|
     * |   B   | C | B |                              |
     * |-------|---|---|------------------------------|
     * |   C   | B |   | Final state.                 |
     * |-------|---|---|------------------------------|
     *
     * More meanigful names for states:
     *
     * |-------|--------------------------------------|
     * | State |          Meaningful name             |
     * |-------|--------------------------------------|
     * |   A   | Begin_string                         |
     * |-------|--------------------------------------|
     * |   B   | String_body                          |
     * |-------|--------------------------------------|
     * |   C   | End_string                           |
     * |-------|--------------------------------------|
     *
     */

    enum String_literal_state{
        Begin_string = -1, String_body, End_string
    };

    void Scanner::increment_position_of_char_in_string_literal(char32_t c)
    {
        if(c == U'\n'){
            loc_->pos_.line_pos_           = 1;
            (loc_->pos_.line_no_)++;
            lexeme_pos_.end_pos_.line_pos_ = 1;
            lexeme_pos_.end_pos_.line_no_++;
        }else{
            bool is_not_cr                 =  c != U'\r';
            loc_->pos_.line_pos_           += is_not_cr;
            lexeme_pos_.end_pos_.line_pos_ += is_not_cr;
        }
    }

    bool Scanner::string_proc()
    {
        bool t    = true;
        last_pos_ = loc_->pos_;
        increment_position_of_char_in_string_literal(ch_);
        switch(state_){
            case Begin_string:
                state_ = String_body;
                break;
            case String_body:
                if(ch_ == U'\"'){
                    state_  =  End_string;
                }else{
                    state_  =  String_body;
                    buffer_ += ch_;
                }
                break;
            case End_string:
                switch(ch_){
                    case U'\"':
                        buffer_              += ch_;
                        state_               =  String_body;
                        break;
                    case U'$':
                        state_               =  -1;
                        automaton_           =  Automaton_name::Encoded_character;
                        base_                =  10;
                        char_code_           =  0;
                        loc_->pos_           =  last_pos_;
                        lexeme_pos_.end_pos_ =  last_pos_;
                        (loc_->pcurrent_char_)--;
                        break;
                    default:
                        loc_->pos_           =  last_pos_;
                        lexeme_pos_.end_pos_ =  last_pos_;
                        (loc_->pcurrent_char_)--;
                        t                    =  false;
                }
                break;
            default:
                ;
        }
        return t;

    }

    enum Comment_state{
        Comment_body = -1, Maybe_incrementing_level, Maybe_decrementing_level
    };

    bool Scanner::comment_proc()
    {
        bool t = true;
        switch(state_){
            case Comment_body:
                if(comment_level_ <= 0){
                    token_.lexeme_.code_ = Lexem_code::Nothing;
                    automaton_           = Automaton_name::Start;
                    (loc_->pcurrent_char_)--;
                    return t;
                }
                switch(ch_){
                    case U'*':
                        state_           = Maybe_decrementing_level;
                        break;
                    case U'/':
                        state_           = Maybe_incrementing_level;
                        break;
                    default:
                        ;
                }
                break;
            case Maybe_incrementing_level:
                comment_level_ += ch_ == U'*';
                state_         =  Comment_body;
                break;
            case Maybe_decrementing_level:
                comment_level_ -= ch_ == U'/';
                state_         =  Comment_body;
                break;
        }
        return t;
    }

    /**
     *
     * A regular expression for quoted character literals of the programming language МУР128
     * can be written in the form
     *     d(i|dd)d, (1)
     * where
     *    d    ' (single quote)
     *    i    character which is not single quote
     *
     * If we construct the minimal DFA for (1), we obtain the following transition
     * table:
     *
     * |-------|---|---|------------------------------|
     * | State | d | i |            Remark            |
     * |-------|---|---|------------------------------|
     * |   A   | B |   | Begin state.                 |
     * |-------|---|---|------------------------------|
     * |   B   | C | D |                              |
     * |-------|---|---|------------------------------|
     * |   C   | D |   |                              |
     * |-------|---|---|------------------------------|
     * |   D   | F |   |                              |
     * |-------|---|---|------------------------------|
     * |   F   |   |   | Final state.                 |
     * |-------|---|---|------------------------------|
     *
     * More meanigful names for states:
     *
     * |-------|--------------------------------------|
     * | State |          Meaningful name             |
     * |-------|--------------------------------------|
     * |   A   | Initial_quote                        |
     * |-------|--------------------------------------|
     * |   B   | Quoted_char                          |
     * |-------|--------------------------------------|
     * |   C   | Maybe_quote                          |
     * |-------|--------------------------------------|
     * |   D   | End_of_quoted_char                   |
     * |-------|--------------------------------------|
     * |   F   | Final_quote                          |
     * |-------|--------------------------------------|
     *
     */

    enum Character_state{
        Initial_quote = -1, Quoted_char, Maybe_quote,
        End_of_quoted_char, Final_quote
    };


    bool Scanner::character_proc()
    {
        lexeme_pos_.end_pos_.line_pos_++;
        (loc_->pos_.line_pos_)++;
// #ifdef CHAR_AUTOMATON_DEBUG_ON
//         print_state(state_);
// #endif
//         bool t = (this->*char_procs_[state_ + 1])();
        bool t = true;
        switch(state_){
            case Initial_quote:
                state_ = Quoted_char;
                break;
            case Quoted_char:
                if(ch_ == U'\''){
                    state_                   = Maybe_quote;
                }else{
                    state_                   = End_of_quoted_char;
                    token_.lexeme_.char_val_ = ch_;
                }
                break;
            case Maybe_quote:
                if(ch_ == U'\''){
                    state_                   = End_of_quoted_char;
                    token_.lexeme_.char_val_ = ch_;
                }else{
                    print_diagnostic(expected_quote,
                                     loc_->pos_.line_no_,
                                     loc_->pos_.line_pos_);
                    en_->increment_number_of_errors();
                    token_.lexeme_.code_     = Lexem_code::Char;
                    token_.lexeme_.char_val_ = U'\'';
                    t                        = false;
                    lexeme_pos_.end_pos_.line_pos_--;
                    (loc_->pos_.line_pos_)--;
                    (loc_->pcurrent_char_)--;
                }
                break;
            case End_of_quoted_char:
                if(ch_ == U'\''){
                    state_                   = Final_quote;
                }else{
                    print_diagnostic(expected_quote,
                                     loc_->pos_.line_no_,
                                     loc_->pos_.line_pos_);
                    en_->increment_number_of_errors();
                    t                        = false;
                    lexeme_pos_.end_pos_.line_pos_--;
                    (loc_->pos_.line_pos_)--;
                    (loc_->pcurrent_char_)--;
                }
                break;
            case Final_quote:
                t                            = false;
                lexeme_pos_.end_pos_.line_pos_--;
                (loc_->pos_.line_pos_)--;
                (loc_->pcurrent_char_)--;
                break;
            default:
                ;
        }
        return t;
    }

    /**
     * A regular expression for character literals in the form of a character code is
     *    f(abc(d?c)*|(a|e)(d?(a|e))*), (2)
     * where
     *    a    U'0'
     *    b    base_marker (one of letters B, b, O, o, X, x)
     *    c    digit (binary digit for letters B and b,
     *                octal digit for letters O and o,
     *                and hexadecimal digit for letters X and x)
     *    d    ' (single quote)
     *    e    U'1' ... U'9'
     *    f    U'$'
     *
     * If we construct the minimal DFA for (2), we obtain the following transition
     * table:
     *
     * |-------|---|---|---|---|---|---|------------------------------|
     * | State | a | b | c | d | e | f |            Remark            |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   A   |   |   |   |   |   | B | Begin state.                 |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   B   | C |   |   |   | D |   |                              |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   C   | D | F |   | G | D |   | Final state.                 |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   D   | D |   |   | G | D |   | Final state.                 |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   F   |   |   | I |   |   |   |                              |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   G   | D |   |   |   | D |   |                              |
     * |-------|---|---|---|---|---|---|------------------------------|
     * |   I   |   |   | I | F |   |   | Final state.                 |
     * |-------|---|---|---|---|---|---|------------------------------|
     *
     * More meanigful names for states:
     *
     * |-------|--------------------------------------|
     * | State |          Meaningful name             |
     * |-------|--------------------------------------|
     * |   A   | Char_code_init_state                 |
     * |-------|--------------------------------------|
     * |   B   | Char_as_code                         |
     * |-------|--------------------------------------|
     * |   C   | Maybe_nondecimal_code                |
     * |-------|--------------------------------------|
     * |   D   | Decimal_code                         |
     * |-------|--------------------------------------|
     * |   F   | Code_base_marker                     |
     * |-------|--------------------------------------|
     * |   G   | Code_digits_separator                |
     * |-------|--------------------------------------|
     * |   I   | Non_decimal_digit_of_code            |
     * |-------|--------------------------------------|
     *
     */

    enum Encoded_character_state{
        Char_code_init_state = -1, Char_as_code,     Maybe_nondecimal_code,
        Decimal_code,              Code_base_marker, Code_digits_separator,
        Non_decimal_digit_of_code
    };

    Scanner::Encoded_character_state_proc Scanner::encoded_char_procs_[] = {
        &Scanner::char_code_init_state_proc,     &Scanner::char_as_code_proc,
        &Scanner::maybe_nondecimal_code_proc,    &Scanner::decimal_code_proc,
        &Scanner::code_base_marker_proc,         &Scanner::code_digits_separator_proc,
        &Scanner::non_decimal_digit_of_code_proc
    };

    bool Scanner::char_code_init_state_proc()
    {
        bool t = true;
        state_ = Char_as_code;
        return t;
    }

    bool Scanner::char_as_code_proc()
    {
        bool t = true;
        if(belongs(Category::Zero, char_categories_)){
            state_                   = Maybe_nondecimal_code;
        }else if(belongs(Category::Digits_1_to_9, char_categories_)){
            state_                   = Decimal_code;
            char_code_               = char_code_ * base_ + digit_to_int(ch_);
        }else{
            print_diagnostic(expected_digit_of_char_code,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.char_val_ = char_code_;
            switch(ch_){
                case U'\"':
                    automaton_           =  Automaton_name::String;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               = -1;
                    break;
                case U'$':
                    automaton_           =  Automaton_name::Encoded_character;
                    char_code_           =  0;
                    base_                =  10;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               =  -1;
                    break;
                default:
                    t                    =  false;
            }
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    bool Scanner::maybe_nondecimal_code_proc()
    {
        bool t = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            char_code_               =  char_code_ * base_ + digit_to_int(ch_);
            state_                   =  Decimal_code;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_                   =  Code_digits_separator;
        }else if(belongs(Category::Letters_Bb, char_categories_)){
            base_                    =  2;
            digits_category_         =  Category::Bin_digit;
            state_                   =  Code_base_marker;
        }else if(belongs(Category::Letters_Oo, char_categories_)){
            base_                    =  8;
            digits_category_         =  Category::Oct_digit;
            state_                   =  Code_base_marker;
        }else if(belongs(Category::Letters_Xx, char_categories_)){
            base_                    =  16;
            digits_category_         =  Category::Hex_digit;
            state_                   =  Code_base_marker;
        }else if(belongs(Category::Double_quote, char_categories_)){
            automaton_               =  Automaton_name::String;
            token_.lexeme_.code_     =  Lexem_code::String;
            state_                   =  -1;
            buffer_                  += char_code_;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else if(belongs(Category::Dollar, char_categories_)){
            automaton_               =  Automaton_name::Encoded_character;
            token_.lexeme_.code_     =  Lexem_code::String;
            buffer_                  += char_code_;
            char_code_               =  0;
            base_                    =  10;
            state_                   =  -1;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else{
            if(token_.lexeme_.code_ == Lexem_code::Char){
                token_.lexeme_.char_val_ =   char_code_;
            }else{
                buffer_                  +=  char_code_;
            }
            t                        =  false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    bool Scanner::decimal_code_proc()
    {
        bool t = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            char_code_               =  char_code_ * base_ + digit_to_int(ch_);
            state_                   =  Decimal_code;
        }else if(belongs(Category::Single_quote, char_categories_)){
            state_                   =  Code_digits_separator;
        }else if(belongs(Category::Double_quote, char_categories_)){
            automaton_               =  Automaton_name::String;
            token_.lexeme_.code_     =  Lexem_code::String;
            state_                   =  -1;
            buffer_                  += char_code_;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else if(belongs(Category::Dollar, char_categories_)){
            automaton_               =  Automaton_name::Encoded_character;
            token_.lexeme_.code_     =  Lexem_code::String;
            buffer_                  += char_code_;
            char_code_               =  0;
            base_                    =  10;
            state_                   =  -1;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else{
            if(token_.lexeme_.code_ == Lexem_code::Char){
                token_.lexeme_.char_val_ =   char_code_;
            }else{
                buffer_                  +=  char_code_;
            }
//             token_.lexeme_.code_     =  Lexem_code::Char;
//             token_.lexeme_.char_val_ =  char_code_;
            t                        =  false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    bool Scanner::code_base_marker_proc()
    {
        bool t = true;
        if(belongs(digits_category_, char_categories_)){
            char_code_               = char_code_ * base_ + digit_to_int(ch_);
            state_                   = Non_decimal_digit_of_code;
        }else{
            print_diagnostic(expected_digit_of_char_code,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.char_val_ = char_code_;
            switch(ch_){
                case U'\"':
                    automaton_           =  Automaton_name::String;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               = -1;
                    break;
                case U'$':
                    automaton_           =  Automaton_name::Encoded_character;
                    char_code_           =  0;
                    base_                =  10;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               =  -1;
                    break;
                default:
                    t                    =  false;
            }
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    bool Scanner::code_digits_separator_proc()
    {
        bool t = true;
        if(belongs(Category::Dec_digit, char_categories_)){
            char_code_ = char_code_ * base_ + digit_to_int(ch_);
            state_     = Decimal_code;
        }else{
            print_diagnostic(expected_digit_of_char_code,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
            token_.lexeme_.char_val_ = char_code_;
            switch(ch_){
                case U'\"':
                    automaton_           =  Automaton_name::String;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               = -1;
                    break;
                case U'$':
                    automaton_           =  Automaton_name::Encoded_character;
                    char_code_           =  0;
                    base_                =  10;
                    token_.lexeme_.code_ =  Lexem_code::String;
                    buffer_              += char_code_;
                    state_               =  -1;
                    break;
                default:
                    t                    =  false;
            }
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;

    }

    bool Scanner::non_decimal_digit_of_code_proc()
    {
        bool t = true;
        if(belongs(digits_category_, char_categories_)){
            char_code_               = char_code_ * base_ + digit_to_int(ch_);
            state_                   = Non_decimal_digit_of_code;
        }else if(ch_ == U'\''){
            state_                   = Code_base_marker;
        }else if(belongs(Category::Double_quote, char_categories_)){
            automaton_               =  Automaton_name::String;
            token_.lexeme_.code_     =  Lexem_code::String;
            buffer_                  += char_code_;
            state_                   =  -1;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else if(belongs(Category::Dollar, char_categories_)){
            automaton_               =  Automaton_name::Encoded_character;
            token_.lexeme_.code_     =  Lexem_code::String;
            buffer_                  += char_code_;
            char_code_               =  0;
            base_                    =  10;
            state_                   =  -1;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }else{
            if(token_.lexeme_.code_ == Lexem_code::Char){
                token_.lexeme_.char_val_ =   char_code_;
            }else{
                buffer_                  +=  char_code_;
            }
//             token_.lexeme_.code_     = Lexem_code::Char;
//             token_.lexeme_.char_val_ = char_code_;
            t                        = false;
            lexeme_pos_.end_pos_.line_pos_--;
            (loc_->pos_.line_pos_)--;
            (loc_->pcurrent_char_)--;
        }
        return t;
    }

    bool Scanner::encoded_character_proc()
    {
        lexeme_pos_.end_pos_.line_pos_++;
        (loc_->pos_.line_pos_)++;
        bool t = (this->*encoded_char_procs_[state_ + 1])();
        return t;
    }

    Scanner::Final_proc Scanner::finals_[] = {
        &Scanner::start_final_proc,     &Scanner::unknown_final_proc,
        &Scanner::keyword_final_proc,   &Scanner::id_final_proc,
        &Scanner::number_final_proc,    &Scanner::delimiter_final_proc,
        &Scanner::string_final_proc,    &Scanner::comment_final_proc,
        &Scanner::character_final_proc, &Scanner::encoded_character_final_proc
    };

    void Scanner::start_final_proc()
    {
        token_.range_.begin_pos_ = token_.range_.end_pos_ = loc_->pos_;
        return;
    }

    void Scanner::unknown_final_proc()
    {
        return;
    }

    void Scanner::keyword_final_proc()
    {
        /* If we are here, then the current lexeme is either an identifier,
         * or a keyword. And if the current lexeme is an identifier, then
         * this identifier must be written to the identifier table. */
        auto elem                = keywords_jump_table[state_];
        token_.lexeme_.code_     = elem.code_;
        if(elem.code_ == Lexem_code::Id){
            token_.lexeme_.id_index_ = ids_ -> insert(buffer_);
        }
        return;
    }

    void Scanner::id_final_proc()
    {
        /* If the current lexeme is an identifier, then this identifier
            * must be written to the identifier table. */
        token_.lexeme_.code_     = Lexem_code::Id;
        token_.lexeme_.id_index_ = ids_ -> insert(buffer_);
        return;
    }

    void Scanner::number_final_proc()
    {
        switch(state_){
            case Initial_state:     case Maybe_nondecimal: case Decimal_int:
            case Non_decimal_digit:
                make_integer();
                break;
            case Base_marker: case Digits_separator:
                print_diagnostic(unexpected_not_digit,
                                 loc_->pos_.line_no_,
                                 loc_->pos_.line_pos_);
                en_->increment_number_of_errors();
                make_integer();
                break;
            case Fractional_part_begin: case Power_signum:
                print_diagnostic(unexpected_not_digit,
                                 loc_->pos_.line_no_,
                                 loc_->pos_.line_pos_);
                en_->increment_number_of_errors();
                token_.lexeme_.code_      = Lexem_code::Float64;
                token_.lexeme_.float_val_ = make_float();
                break;
            case Power_of_ten:
                print_diagnostic(expected_digit_or_pm,
                                 loc_->pos_.line_no_,
                                 loc_->pos_.line_pos_);
                en_->increment_number_of_errors();
                token_.lexeme_.code_      = Lexem_code::Float64;
                token_.lexeme_.float_val_ = make_float();
                break;
            case Complex_suffix:
                set_complex_precision();
                token_.lexeme_.complex_val_ = make_complex();
                break;
            case Precision_suffix:
                token_.lexeme_.float_val_ = make_float();
                break;
            case Fractional_part_digit: case Digit_of_power_of_ten:
                token_.lexeme_.code_      = Lexem_code::Float64;
                token_.lexeme_.float_val_ = make_float();
                break;
        }

        return;
    }

    void Scanner::delimiter_final_proc()
    {
        auto elem            = delimiters_jump_table[state_];
        token_.lexeme_.code_ = elem.code_;
        correct_delimiter(elem.code_);
        return;
    }

    void Scanner::correct_delimiter(Lexem_code code)
    {
        // switch(code){
        //     case Lexem_code::Maybe_logical_or_not:
        //         print_diagnostic(expected_logical_or_not,
        //                          loc_->pos_.line_no_,
        //                          loc_->pos_.line_pos_);
        //         en_->increment_number_of_errors();
        //         token_.lexeme_.code_      = Lexem_code::Logical_or_not;
        //         break;
        //     case Lexem_code::Maybe_logical_and_not:
        //         print_diagnostic(expected_logical_and_not,
        //                          loc_->pos_.line_no_,
        //                          loc_->pos_.line_pos_);
        //         en_->increment_number_of_errors();
        //         token_.lexeme_.code_      = Lexem_code::Logical_and_not;
        //         break;
        //     case Lexem_code::Maybe_component:
        //         print_diagnostic(expected_component,
        //                          loc_->pos_.line_no_,
        //                          loc_->pos_.line_pos_);
        //         en_->increment_number_of_errors();
        //         token_.lexeme_.code_      = Lexem_code::Component;
        //         break;
        //     case Lexem_code::Maybe_component_or:
        //         print_diagnostic(expected_component_or,
        //                          loc_->pos_.line_no_,
        //                          loc_->pos_.line_pos_);
        //         en_->increment_number_of_errors();
        //         token_.lexeme_.code_      = Lexem_code::Component_or;
        //         break;
        //     case Lexem_code::Comment_begin:
        //         comment_level_ = 1;
        //         automaton_     = Automaton_name::Comment;
        //         state_         = -1;
        //         break;
        //     case Lexem_code::Comment_end:
        //         print_diagnostic(unexpected_mark_of_comment_end,
        //                          loc_->pos_.line_no_,
        //                          loc_->pos_.line_pos_);
        //         en_->increment_number_of_errors();
        //         token_.lexeme_.code_      = Lexem_code::Nothing;
        //         automaton_                = Automaton_name::Start;
        //         break;
        //     default:
        //         ;
        // }
    }

    void Scanner::string_final_proc()
    {
        token_.lexeme_.str_index_ = strs_ -> insert(buffer_);
        token_.lexeme_.code_      = Lexem_code::String;
        if(state_ != End_string){
            print_diagnostic(unexpected_end_of_string_literal,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
        }
        return;
    }

    void Scanner::comment_final_proc()
    {
        if(comment_level_ > 0){
            en_->increment_number_of_errors();
            token_.lexeme_.code_      = Lexem_code::Nothing;
        }
        return;
    }

    void Scanner::character_final_proc()
    {
        switch(state_){
            case Quoted_char: case Maybe_quote:
                token_.lexeme_.char_val_ = U'\'';
                print_diagnostic(unexpected_end_of_char_literal,
                                 loc_->pos_.line_no_,
                                 loc_->pos_.line_pos_);
                en_->increment_number_of_errors();
                break;
            case End_of_quoted_char:
                print_diagnostic(unexpected_end_of_char_literal,
                                 loc_->pos_.line_no_,
                                 loc_->pos_.line_pos_);
                en_->increment_number_of_errors();
                break;
            case Final_quote:
                break;
            default:
                ;
        }
    }

    void Scanner::encoded_character_final_proc()
    {
        if(token_.lexeme_.code_ == Lexem_code::String){
            token_.lexeme_.str_index_ = strs_ -> insert(buffer_);
        }
        if((state_ != Maybe_nondecimal_code)     &&
           (state_ != Decimal_code)              &&
           (state_ != Non_decimal_digit_of_code))
        {
            print_diagnostic(unexpected_end_of_char_literal,
                             loc_->pos_.line_no_,
                             loc_->pos_.line_pos_);
            en_->increment_number_of_errors();
        }
    }

    ascaner::Token<mur128m_scanner::Lexeme_info> Scanner::current_lexeme()
    {
        automaton_           = Automaton_name::Start;
        token_.lexeme_.code_ = Lexem_code::Nothing;
        lexeme_begin_        = loc_->pcurrent_char_;
        bool t               = true;
        while((ch_ = *(loc_->pcurrent_char_)++)){
            char_categories_ = get_categories_set(ch_);
            t                = (this->*procs_[static_cast<unsigned>(automaton_)])();
            if(!t){
                token_.range_          = lexeme_pos_;
                token_.range_.end_pos_.line_pos_--;
                if(Automaton_name::Id == automaton_){
                    /* If the current lexeme is an identifier, then this identifier
                     * must be written to the identifier table. */
                    token_.lexeme_.code_     = Lexem_code::Id;
                    token_.lexeme_.id_index_ = ids_ -> insert(buffer_);
                }else if(Automaton_name::Keyword == automaton_){
                    /* If we are here, then the current lexeme is either an identifier,
                     * or a keyword. And if the current lexeme is an identifier, then
                     * this identifier must be written to the identifier table. */
                    auto elem                = keywords_jump_table[state_];
                    token_.lexeme_.code_     = elem.code_;
                    if(elem.code_ == Lexem_code::Id){
                        token_.lexeme_.id_index_ = ids_ -> insert(buffer_);
                    }
                }else if(token_.lexeme_.code_ == Lexem_code::String){
                    token_.lexeme_.str_index_ = strs_ -> insert(buffer_);
                }
                return token_;
            }
        }

        token_.range_          = lexeme_pos_;
        token_.range_.end_pos_.line_pos_--;
        /* Here we can be, only if we have already read all the processed text. In
         * this case, the pointer to the current symbol points to a character that
         * is immediately after the null character, which is a sign of the end of
         * the text. To avoid entering subsequent calls outside the text, we need
         * to go back to the null character. */
        (loc_->pcurrent_char_)--;
        /* Further, since we are here, the end of the current token (perhaps
         * unexpected) has not yet been processed. It is necessary to perform this
         * processing, and, probably, to display some kind of diagnostics. */
        (this->*finals_[static_cast<unsigned>(automaton_)])();
        return token_;
    }

    static const std::string code_names[] = {
        "Nothing",                     "UnknownLexem",
        "KwSection",                   "KwReadable",
        "KwWritable",                  "KwExecutable",
        "Id",                          "Integer",
        "KwFloat32",                   "KwFloat64",
        "KwFloat80",                   "KwFloat128",
	"KwInt32",                     "KwInt64",
        "KwInt128",		       "KwInt8",
	"KwInt16",		       "KwUInt32",
        "KwUInt64",		       "KwUInt128",
	"KwUInt8",		       "KwUInt16",
        "Float32",                     "Float64",
        "Float80",                     "Float128",
        "Complex32",                   "Complex64",
        "Complex80",                   "Complex128",
	"KwComplex32",                 "KwComplex64",
        "KwComplex80",                 "KwComplex128",
        "String",                      "Char",
        "Sq_br_opened",                "Round_br_opened",
        "Sq_br_closed",                "Round_br_closed",
        "Less_than",                   "Left_shift",
        "Minus",                       "Logical_not",
        "Bitwise_not",                 "Point",
        "Semicolon",                   "Plus",
        "Mul",                         "Div",
        "Remainder",                   "Bitwise_or",
        "Bitwise_and",                 "Greater_than",
        "Right_shift",                 "Curly_brace_opened",
        "Curly_brace_closed",          "Comma",
	"Register",		       "KwChar",
	"KwFormat",		       "KwString"
    };

    std::string Scanner::lexeme_to_string(const mur128m_scanner::Lexeme_info& li)
    {
        std::string result;
        auto        lc     = li.code_;
        result             = code_names[static_cast<unsigned>(lc)];
        switch(lc){
            case Lexem_code::Char:
                result += " " + show_char32(li.char_val_);
                break;
            case Lexem_code::Id:
                result += " " + idx_to_string(ids_, li.id_index_);
                break;
            case Lexem_code::String:
                result += " " + idx_to_string(strs_, li.str_index_);
                break;
            case Lexem_code::Float32: case Lexem_code::Float64:
            case Lexem_code::Float80: case Lexem_code::Float128:
                result += " " + to_string(li.float_val_);
                break;
            case Lexem_code::Complex32: case Lexem_code::Complex64:
            case Lexem_code::Complex80: case Lexem_code::Complex128:
                result += " " + to_string(cimagq(li.complex_val_)) + "i";
                break;
            case Lexem_code::Integer:
                result += " " + to_string(li.int_val_);
                break;
            default:
                ;
        }
        return result;
    }
};
