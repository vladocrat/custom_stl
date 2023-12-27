#pragma once

#include <iostream>

template<typename T>
struct Printable
{
    virtual ~Printable() = default;

    const auto print() const noexcept
    {
        return static_cast<const T*>(this)->print();
    }
};

template<typename T, typename = void>
struct is_printable : std::false_type {};

template <typename T>
struct is_printable<T, std::void_t<decltype(std::declval<const T>().print())>> : std::true_type {};
//struct is_printable<T, std::void_t<decltype(std::is_base_of_v<Printable<T>, T>)>> : std::true_type {}; //!TODO incorrect

template<typename T>
constexpr bool is_printable_v = is_printable<T>::value;

template<typename T>
constexpr auto& print(const T& t)
{
    if constexpr (is_printable_v<T>)
    {
        static_assert(std::is_base_of_v<Printable<T>, T>);
        return std::cout << t.print();
    }
    else
    {
        return std::cout << t;
    }
}

auto& print(const std::string_view& str)
{
    return std::cout << str;
}

auto& print(const std::string& str)
{
    return std::cout << str;
}

template<typename T, size_t N>
constexpr auto& print(const T (&arr)[N])
{    
    std::cout << "[ ";

    for (auto i = 0; i < N; i++)
    {
        std::cout << arr[i] << ' ';
    }

    return std::cout << ']';
}

template<template <typename...> class Container, typename Type>
constexpr auto& print(const Container<Type>& c)
{
    std::cout << "[ ";

    for (const auto& v : c)
    {
        if constexpr (is_printable_v<Type>)
        {
            std::cout << v.print() << ' ';
        }
        else
        {
            std::cout << v << ' ';
        }
    }

    return std::cout << ']';
}

template<typename T>
constexpr auto& println(const T& t)
{
    return print(t) << "\n";
}

template<typename T = void>
constexpr auto& println()
{
    return std::cout << "\n";
}
