#pragma once

#include <utility>

template<typename T>
class Iterator
{
public:
    Iterator(T* value) noexcept : m_value { value } {}
    Iterator(const Iterator& other) noexcept: m_value { other.m_value } {}
    Iterator(Iterator&& other) noexcept : m_value { std::move(other.m_value) } {}
    virtual ~Iterator() noexcept = default;

    constexpr auto& operator=(const Iterator& other) noexcept { m_value = other.m_value; return *this;            }
    constexpr auto& operator=(Iterator&& other)      noexcept { m_value = std::move(other.m_value); return *this; }

    [[nodiscard]] constexpr T& operator*()  noexcept { return *m_value; }
    [[nodiscard]] constexpr T* operator->() noexcept { return m_value;  }

    virtual Iterator<T>& operator++() noexcept { m_value++; return *this; }
    virtual Iterator<T>& operator--() noexcept { m_value--; return *this; }

    virtual Iterator<T>& operator++(int) noexcept { m_value++; return *this; }
    virtual Iterator<T>& operator--(int) noexcept { m_value--; return *this; }

    [[nodiscard]] constexpr bool operator!=(const Iterator& other) const noexcept { return  m_value != other.m_value; }
    [[nodiscard]] constexpr bool operator==(const Iterator& other) const noexcept { return  m_value == other.m_value; }

    [[nodiscard]] constexpr operator bool() const noexcept { return m_value; }

private:
    T* m_value { nullptr };
};

