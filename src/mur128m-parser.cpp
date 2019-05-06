/*
     File:    mur128m-parser.cpp
     Author:  Ilya Chikmarev
*/

#include <string>
#include <cstdio>
#include <memory>
#include "../include/usage.h"
#include "../include/get_processed_text.h"
#include "../include/location.h"
#include "../include/errors_and_tries.h"
#include "../include/error_count.h"
#include "../include/char_trie.h"
#include "../include/parser.h"
#include "../include/intermediate_repres.h"

enum Exit_codes{
    Success, No_args, File_processing_error
};

int main(int argc, char* argv[])
{
    if(1 == argc){
        usage(argv[0]);
        return No_args;
    }

    auto              text   = get_processed_text(argv[1]);
    if(!text.length()){
        return File_processing_error;
    }

    char32_t*         p          = const_cast<char32_t*>(text.c_str());
    auto              loc        = std::make_shared<ascaner::Location>(p);
    Errors_and_tries  et;
    et.ec_                       = std::make_shared<Error_count>();
    et.ids_trie_                 = std::make_shared<Char_trie>();
    et.strs_trie_                = std::make_shared<Char_trie>();

    auto              parser_ptr = std::make_shared<parser::Parser>(loc, et);

    mur128m_ir::Command  buffer;
    parser_ptr->compile(buffer);

    return Success;
}
