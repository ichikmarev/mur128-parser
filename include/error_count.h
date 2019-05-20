/*
    File:    error_count.h
    Author:  Chikmarev Ilya
*/

#ifndef ERROR_COUNT_H
#define ERROR_COUNT_H
#   include <cstddef>
/* A class for calculating the number of errors. */
class Error_count{
public:
    Error_count() : number_of_errors_(0) {};
    void   increment_number_of_errors();
    void   print() const;
    size_t get_number_of_errors() const;
private:
    size_t number_of_errors_;
};
#endif
