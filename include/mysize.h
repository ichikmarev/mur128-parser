/*
    File:    mysize.h
    Created: 09 February 2019 at 21:30 Moscow time
    Author:  Гаврилов Владимир Сергеевич
    E-mails: vladimir.s.gavrilov@gmail.com
             gavrilov.vladimir.s@mail.ru
             gavvs1977@yandex.ru
*/

#ifndef MYSIZE_H
#define MYSIZE_H
/*
 * I use g++ 6.3 (it is standard g++ version in Debian 9), and this compiler doesn't
 * support C++17. But since C++17 there is a template
 *
 * template <class T, std::size_t N>
 * constexpr std::size_t size(const T (&a)[N]) noexcept;
 *
 * This template returns N, i.e. a number of elements in an array a.
 * Hence, I use an implementation of the template from
 * https://en.cppreference.com/w/cpp/iterator/size
 */
template <class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept
{
    return N;
}
#endif