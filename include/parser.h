/*
    File:    parser.h
    Author:  Ilya Chikmarev
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

        void compile(mur128m_ir::Command& buffer);

    private:
        struct Impl;
        std::unique_ptr<Impl> pimpl_;
    };
};
#endif
