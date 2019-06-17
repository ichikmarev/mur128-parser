/*
    File:    parser.cpp
    Author:  Ilya Chikmarev
*/

#include <cstdio>
#include "../include/parser.h"
#include "../include/scope.h"
#include "../include/mur128m_scaner.h"
#include "../include/mur128m_lexeme.h"
#include "../include/abstract_scaner.h"

namespace parser{
    struct Parser::Impl{
    public:
        Impl()                             = default;
        Impl(const Impl& src)              = default;
        Impl& operator = (const Impl& rhs) = default;
        virtual ~Impl()                    = default;

        Impl(const ascaner::Location_ptr& location, const Errors_and_tries& et) :
            location_{location},
            et_{et},
            symbol_table_{std::make_shared<mur128m_scope::Symbol_table>()},
            scanner_{std::make_shared<mur128m_scanner::Scanner>(location, et)}
            {}

        void compile(mur128m_ir::Command& buffer);

    private:
        ascaner::Location_ptr                     location_;
        Errors_and_tries                          et_;
        std::shared_ptr<mur128m_scope::Symbol_table> symbol_table_;
        std::shared_ptr<mur128m_scanner::Scanner>    scanner_;

        mur128m_ir::Command                          buffer_;

        void program();
    };

    enum class Program_state{
        A, B, C, D, E, F
    };
#define PROGRAM_DEBUG_ON
    void Parser::Impl::program()
    {
#ifdef PROGRAM_DEBUG_ON
        puts("We are in a function for the non-terminal \'program\'.");
#endif
        Program_state state = Program_state::A;
        using namespace mur128m_scanner;
        Lynx_token  ltok;
        Lexeme_info li;
        Lexem_code  lc;
        while((lc = (li = (ltok = scanner_->current_lexeme()).lexeme_).code_) !=
              Lexem_code::Nothing)
        {
            switch(state){
                case Program_state::A:
                    break;
                case Program_state::B:
                    break;
                case Program_state::C:
                    break;
                case Program_state::D:
                    break;
                case Program_state::E:
                    break;
                case Program_state::F:
                    break;
            }
        }
#ifdef PROGRAM_DEBUG_ON
        puts("End of processing.");
#endif
    }

    void Parser::Impl::compile(mur128m_ir::Command& buffer)
    {
        buffer_.clear();
        program();
        buffer = buffer_;
    }

    void swap(Parser& first, Parser& second) noexcept
    {
    }

    void Parser::compile(mur128m_ir::Command& buffer)
    {
        pimpl_->compile(buffer);
    }

    Parser::Parser() : pimpl_{std::make_unique<Impl>()} {}

    Parser::Parser(const ascaner::Location_ptr& location, const Errors_and_tries& et) :
        pimpl_{std::make_unique<Impl>(location, et)} {}

    Parser::~Parser() = default;

    Parser::Parser(const Parser& src)
    {
        pimpl_ = std::make_unique<Impl>(*src.pimpl_);
    }

    Parser& Parser::operator = (const Parser& rhs)
    {
        pimpl_ = std::make_unique<Impl>(*rhs.pimpl_);
        return *this;
    }
};
