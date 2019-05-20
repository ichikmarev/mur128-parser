/*
    File:    position.h
    Author:  Chikmarev Ilya
*/

#ifndef POSITION_H
#define POSITION_H
#   include <cstddef>
namespace ascaner{
    struct Position{
        Position()                           = default;
        Position(const Position&)            = default;
        ~Position()                          = default;
        Position& operator=(const Position&) = default;

        Position(size_t line_no, size_t line_pos) :
            line_no_(line_no), line_pos_(line_pos) {}

        size_t line_no_  = 1;
        size_t line_pos_ = 1;
    };

    struct Position_range{
        Position begin_pos_;
        Position end_pos_;
    };
};
#endif
