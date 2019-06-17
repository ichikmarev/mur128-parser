/*
    File:    parser.cpp
    Author:  Ilya Chikmarev
*/

#include <cstdio>
#include "../include/parser.h"
#include "../include/scope.h"
#include "../include/mur128m_scaner.h"
#include "../include/mur128m_lexeme.h"
#include "../include/parser.h"


bool Parser::Impl::check2_var_name(ast::Id name)
{
    auto sr = st_->search(name);
    if(sr.status != symbol_table::Search_status::Found_in_the_current_scope)
    {
        return true;
    }else{
        auto id_str = idx_to_string(et_.ids_trie, name);
        printf(var_name_diagnosis_fmt[static_cast<unsigned>(sr.attr)],
               sc_->lexem_begin_line_number(),
               id_str.c_str());
        et_.ec->increment_number_of_errors();
        return false;
    }
}w

std::shared_ptr<ast::Binary_op> Parser::Impl::proc_expr_type()
{
	std::shared_ptr<ast::Binary_op> result;
	enum class State{
		Start, Twelve, Size, Finish
	};
	State state = State::Start;
	std::shared_ptr<ast::Alloc_array_expr> expr;
	for(;;){
		Main_lexem_info li = sc_->current_lexem();
		Lexem_category cat = get_lexem_category(li);
		switch(state){
			case State::Start:
				switch(cat){
					case Lexem_category::Kw_int:
					case Lexem_category::Kw_float:
					case Lexem_category::Kw_string:
					case Lexem_category::Kw_true:
					case Lexem_category::Kw_false:
					case Lexem_category::Open_round_bracket:
					case Lexem_category::Ident:
					case Lexem_category::Module_name_prefix:
					case Lexem_category::Kw_array:
                        sc_->back();
                        expr = proc_expr_twelve();
                        state = State::Twelve;
                        break;
					default:
						printf(expected_expr_twelve_fmt, 
								sc_->lexem_begin_line_number());
						et_.ec->increment_number_of_errors();
						return result;	
				}
				break;
			case State::Twelve:
				if(cat != Lexem_category::Dimension_size){
                    printf(expected_dim_size_fmt,  sc_->lexem_begin_line_number());
                    et_.ec->increment_number_of_errors();
                    return result;
                }
				sc_->back();
                state = State::Size;
                break;
			case State::Size:
				switch(cat){
					case Lexem_category::Kw_int:
					case Lexem_category::Kw_float:
					case Lexem_category::Kw_string:
					case Lexem_category::Kw_true:
					case Lexem_category::Kw_false:
					case Lexem_category::Open_round_bracket:
					case Lexem_category::Ident:
					case Lexem_category::Module_name_prefix:
					case Lexem_category::Kw_array:
                        sc_->back();
                        expr = proc_expr_twelve();
                        state = State::Finish;
                        break;
					default:
						printf(expected_expr_twelve_fmt, 
								sc_->lexem_begin_line_number());
						et_.ec->increment_number_of_errors();
						return result;	
				}
				break;
			case State::Finish:
				sc_->back();
                return result; 
		}
	}
	return result;
}


