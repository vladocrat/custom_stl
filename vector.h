#pragma once

#include <memory>
#include <algorithm>

#include "iterator.h"

namespace Constants
{
constexpr static size_t DEFAULT_CAPACITY = 1;
constexpr static size_t DEFAULT_SIZE     = 0;
constexpr static float  FACTOR           = 1.5f;
} // Constants

template<class Type, class Allocator = std::allocator<Type>>
class Vector final
{
public:
    class VectorIterator final : public Iterator<Type>
    {
    public:
        VectorIterator(Type* val) noexcept : Iterator<Type>(val) { }
    };

    constexpr VectorIterator begin()       noexcept { return VectorIterator { &m_values[0] };      }
    constexpr VectorIterator end()         noexcept { return VectorIterator { &m_values[m_size] }; }
    constexpr VectorIterator begin() const noexcept { return VectorIterator { &m_values[0] };      }
    constexpr VectorIterator end()   const noexcept { return VectorIterator { &m_values[m_size] }; }

    Vector(const std::initializer_list<Type>& list) : m_size(list.size())
    {
        m_values = new Type[m_capacity];

        auto ix = 0;

        for (const Type& item : list)
        {
            m_values[ix++] = item;
        }
    }

    Vector() noexcept : m_values { nullptr }
    {
        m_values = new Type[m_capacity];
    }

    ~Vector()
    {
        delete[] m_values;
    }

    constexpr void pushBack(const Type& value)
    {
        if (m_size == m_capacity)
        {
            auto temp = new Type[m_size];

            std::copy(m_values, m_values + m_size, temp);

            delete[] m_values;
            m_capacity *= Constants::FACTOR;
            m_values = new Type[m_capacity];

            std::copy(temp, temp + m_size, m_values);
            delete[] temp;
        }

        m_values[m_size++] = value;
    }

    constexpr void pushBack(Type&& value)
    {
        if (m_size == m_capacity)
        {
            auto temp = new Type[m_size];
            std::move(m_values, m_values + m_size, temp);
            delete[] m_values;
            m_values = temp;
        }

        m_values[m_size++] = std::move(value);
    }

    constexpr void popBack()
    {
        auto newSize = m_size - 1;
        auto temp = new Type[newSize];
        std::copy(m_values, m_values + newSize, temp);

        delete[] m_values;
        m_values = nullptr;
        m_values = new Type[m_capacity];

        std::copy(temp, temp + newSize, m_values);
        m_size--;
        delete[] temp;
    }

    [[nodiscard]] constexpr auto   isEmpty()    const noexcept { return m_size == 0; }
    [[nodiscard]] constexpr auto   isNotEmpty() const noexcept { return m_size > 0;  }
    [[nodiscard]] constexpr size_t size()       const noexcept { return m_size;      }
    [[nodiscard]] constexpr size_t capacity()   const noexcept { return m_capacity;  }


    constexpr void reserve(const size_t count) noexcept
    { //!TODO works incorrecly ATM see https://en.cppreference.com/w/cpp/container/vector/reserve
        if (count < m_capacity)
        {
            return;
        }

        if (m_size != 0)
        {
            return;
        }

        m_capacity = count;
        m_values = new Type[m_capacity];
    }

    constexpr void clear() noexcept
    {
        if (m_values)
        {
            delete[] m_values;
            m_values = nullptr;
        }

        m_size = Constants::DEFAULT_SIZE;
    }

    [[nodiscard]] constexpr Type* data()        noexcept { return m_values;             }
    [[nodiscard]] constexpr const Type* data()  const    { return m_values;             }
    [[nodiscard]] constexpr Type& back()                 { return m_values[m_size - 1]; }
    [[nodiscard]] constexpr const Type& back()  const    { return m_values[m_size - 1]; }
    [[nodiscard]] constexpr Type& front()                { return m_values[0];          }
    [[nodiscard]] constexpr const Type& front() const    { return m_values[0];          }

    [[nodiscard]] constexpr Type& at(const size_t ix)
    {
        if (outOfBounds(ix))
            throw std::out_of_range("indexing element out of bounds");

        return m_values[ix];
    }

    [[nodiscard]] constexpr const Type& at(const size_t ix) const
    {
        if (outOfBounds(ix))
            throw std::out_of_range("indexing element out of bounds");

        return m_values[ix];
    }

    [[nodiscard]] constexpr Type operator[](const size_t ix) const
    {
        return m_values[ix];
    }

private:
    constexpr bool outOfBounds(const size_t ix) const { return ix >= m_size; }

    Type* m_values      { nullptr };
    size_t m_size       { Constants::DEFAULT_SIZE };
    size_t m_capacity   { Constants::DEFAULT_CAPACITY };
};

