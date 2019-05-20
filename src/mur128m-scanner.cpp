/*
     File:    mur128m-scanner.cpp
     Author:  Chikmarev Ilya
*/

#include <string>
#include <cstdio>
#include <memory>
#include "../include/get_processed_text.h"
#include "../include/location.h"
#include "../include/errors_and_tries.h"
#include "../include/error_count.h"
#include "../include/char_trie.h"
#include "../include/abstract_scaner.h"
#include "../include/mur128m_lexeme.h"
#include "../include/mur128m_scaner.h"
#include "../include/usage.h"
#include "../include/test_mur128m_scaner.h"

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

    char32_t*         p      = const_cast<char32_t*>(text.c_str());
    auto              loc    = std::make_shared<ascaner::Location>(p);
    Errors_and_tries  et;
    et.ec_                   = std::make_shared<Error_count>();
    et.ids_trie_             = std::make_shared<Char_trie>();
    et.strs_trie_            = std::make_shared<Char_trie>();
    auto              mur128msc = std::make_shared<mur128m_scanner::Scanner>(loc, et);

// #define DEBUG
#ifdef DEBUG
    printf("There is command line argument %s.\n", argv[1]);
#else
    test_mur128m_scaner(mur128msc);
    et.ec_->print();
#endif
    return Success;
}
