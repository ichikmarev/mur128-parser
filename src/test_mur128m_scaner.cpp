/*
    File:    test_mur128m_scaner.cpp
    Author:  Chikmarev Ilya
*/

#include <cstdio>
#include "../include/test_mur128m_scaner.h"
#include "../include/mur128m_lexeme.h"

void test_mur128m_scaner(const std::shared_ptr<mur128m_scanner::Scanner>& mur128msc)
{
    mur128m_scanner::mur128m_token lti;
    mur128m_scanner::Lexem_code llc;
    do{
        lti    = mur128msc->current_lexeme();
        llc   = lti.lexeme_.code_;
        auto s = mur128msc->token_to_string(lti);
        puts(s.c_str());
    }while(llc != mur128m_scanner::Lexem_code::Nothing);
}
