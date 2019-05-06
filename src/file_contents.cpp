/*
    File:    file_contents.cpp
    Author:  Ilya Chikmarev
*/

#include <cstdio>
#include <memory>
#include <boost/filesystem/operations.hpp>
#include "../include/file_contents.h"
#include "../include/fsize.h"

class Binary_file{
public:
    Binary_file() = default;
    Binary_file(const char* name) : fptr(fopen(name, "rb")) {};
    ~Binary_file() {fclose(fptr);};

    FILE* get() const {return fptr;};
private:
    FILE* fptr = 0;
};

namespace fs = boost::filesystem;

Contents get_contents(const char* name)
{
    Contents result = std::make_pair(Get_contents_return_code::Normal, "");
    fs::path p{name};
    if(!fs::exists(p)){
        result.first = Get_contents_return_code::Impossible_open;
        return result;
    }
    Binary_file f {name};
    FILE* fptr = f.get();
    if(!fptr){
        result.first = Get_contents_return_code::Impossible_open;
        return result;
    }
    long file_size = fsize(fptr);
    if(!file_size){
        return result;
    }
    auto   test_text = std::make_unique<char[]>(file_size + 1);
    char*  q         = test_text.get();
    size_t fr        = fread(q, 1, file_size, fptr);
    if(fr < (unsigned long)file_size){
        result.first = Get_contents_return_code::Read_error;
        return result;
    }
    test_text[file_size] = 0;
    result.second = std::string(test_text.get());
    return result;
}
