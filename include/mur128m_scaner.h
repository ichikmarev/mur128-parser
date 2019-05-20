/*
    File:    mur128m_scaner.h
    Author:  Chikmarev Ilya
*/
#ifndef mur128m_SCANER_H
#define mur128m_SCANER_H
#   include "../include/mur128m_lexeme.h"
#   include "../include/abstract_scaner.h"
#   include "../include/category.h"
namespace mur128m_scanner{
    using mur128m_token = ascaner::Token<mur128m_scanner::Lexeme_info>;

    class Scanner : public ascaner::Abstract_scaner<mur128m_scanner::Lexeme_info>{
    public:
        Scanner()               = default;
        Scanner(const ascaner::Location_ptr& location, const Errors_and_tries& et) :
            ascaner::Abstract_scaner<mur128m_scanner::Lexeme_info>(location, et) {};
        Scanner(const Scanner&) = default;
        virtual ~Scanner()      = default;

        ascaner::Token<mur128m_scanner::Lexeme_info> current_lexeme() override;

        std::string lexeme_to_string(const mur128m_scanner::Lexeme_info& li) override;
    private:
        enum class Automaton_name{
            Start,     Unknown,          Keyword, Id,
            Number,    Delimiter,        String,  Comment,
            Character, Encoded_character
        };

        Automaton_name        automaton_;

        typedef bool (Scanner::*Automaton_proc)();
        /* It is the type of the pointer on function-member that implements
         * the state machine that handles the lexem. The function should
         * return true if the token has not been read to the end,
         * and false otherwise. */

        typedef void (Scanner::*Final_proc)();
        /* It is the type of the pointer on function-member that performs
        * the necessary actions in case of unexpected end of lexem. */

        static Automaton_proc procs_[];
        static Final_proc     finals_[];

        int                   comment_level_;

        bool start_proc();     bool unknown_proc();
        bool keyword_proc();   bool id_proc();
        bool number_proc();    bool delimiter_proc();
        bool string_proc();    bool comment_proc();
        bool character_proc(); bool encoded_character_proc();

        void start_final_proc();     void unknown_final_proc();
        void keyword_final_proc();   void id_final_proc();
        void number_final_proc();    void delimiter_final_proc();
        void string_final_proc();    void comment_final_proc();
        void character_final_proc(); void encoded_character_final_proc();

        unsigned __int128 int_part_;
         __float128       frac_part_;
        unsigned          exponent_;
        int               exponent_sign_;
        int               num_of_digits_in_frac_part_;

        unsigned __int128 base_;

        bool              is_float_;

        void make_integer();
        void set_float_precision();

        Category           digits_category_;

        __float128 make_float();

        void set_complex_precision();
        __complex128 make_complex();

        void correct_delimiter(Lexem_code code);

        bool maybe_nondecimal_proc();         bool decimal_int_proc();
        bool base_marker_proc();              bool digits_separator_proc();
        bool non_decimal_digit_proc();        bool fractional_part_begin_proc();
        bool power_of_ten_proc();             bool fractional_part_digit_proc();
        bool digit_of_power_of_ten_proc();    bool power_signum_proc();
        bool precision_suffix_proc();

        typedef bool (Scanner::*Encoded_character_state_proc)();

        static Encoded_character_state_proc   encoded_char_procs_[];

        bool char_code_init_state_proc();      bool char_as_code_proc();
        bool maybe_nondecimal_code_proc();     bool decimal_code_proc();
        bool code_base_marker_proc();          bool code_digits_separator_proc();
        bool non_decimal_digit_of_code_proc();

        char32_t          char_code_;
        ascaner::Position last_pos_;

//         typedef bool (Scanner::*String_state_proc)();
//
//         static String_state_proc string_procs_[];
//
//         bool string_state_a_proc(); bool string_state_b_proc();
//         bool string_state_c_proc(); bool string_state_d_proc();
//         bool string_state_e_proc(); bool string_state_f_proc();
//         bool string_state_h_proc(); bool string_state_j_proc();
//         bool string_state_l_proc(); bool string_state_n_proc();
//         bool string_state_o_proc(); bool string_state_p_proc();
//         bool string_state_t_proc(); bool string_state_u_proc();
//         bool string_state_y_proc();

        void increment_position_of_char_in_string_literal(char32_t c);
//         void decrement_position_of_char_in_string_literal();
    };
};
#endif
