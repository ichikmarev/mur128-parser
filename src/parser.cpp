/*
    File:    parser.cpp
    Created: 21 April 2019 at 09:50 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#include "../include/parser.h"

namespace parser{
    struct Parser::Impl{
    public:
        Impl()                             = default;
        Impl(const Impl& src)              = default;
        Impl& operator = (const Impl& rhs) = default;
        virtual ~Impl()                    = default;

        Impl(const ascaner::Location_ptr& location, const Errors_and_tries& et) :
            location_{location}, et_{et} {}

        void compile(lynx_ir::Command& buffer);

    private:
        ascaner::Location_ptr location_;
        Errors_and_tries      et_;
    };

    void Parser::Impl::compile(lynx_ir::Command& buffer)
    {
    }

    void swap(Parser& first, Parser& second) noexcept
    {
    }

    void Parser::compile(lynx_ir::Command& buffer)
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