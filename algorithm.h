#pragma once

#include <algorithm>

template<template <typename...> class Container, typename Type, typename Functor>
constexpr auto forEach(const Container<Type>& container, Functor f) noexcept
{
    return std::for_each(container.begin(), container.end(), f);
}

template<template <typename...> class Container, typename Type, typename Functor>
constexpr auto allOf(const Container<Type>& container, Functor f)
{ //! TODO doesn't work atm fix iterator
    return std::all_of(container.begin(), container.end(), f);
}

template<template <typename...> class Container, typename Type, typename Functor>
constexpr auto max(const Container<Type>& container, Functor f)
{
    return std::max_element(container.begin(), container.end(), f);
}

template<template <typename...> class Container, typename Type>
constexpr auto max(const Container<Type>& container)
{
    return std::max_element(container.begin(), container.end());
}

