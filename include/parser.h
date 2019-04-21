/*
    File:    parser.h
    Created: 16 April 2019 at 08:41 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef PARSER_H
#define PARSER_H
#   include <memory>
#   include "../include/errors_and_tries.h"
#   include "../include/location.h"
#   include "../include/intermediate_repres.h"
namespace parser{
    class Parser{
    public:
        Parser();
        virtual ~Parser();
        Parser(const Parser& src);
        Parser& operator = (const Parser& rhs);

        Parser(const ascaner::Location_ptr& location, const Errors_and_tries& et);

        void compile(lynx_ir::Command& buffer);

    private:
        struct Impl;
        std::unique_ptr<Impl> pimpl_;
    };
};
#endif