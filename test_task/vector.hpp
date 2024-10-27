#pragma once

#ifdef __clang__
#include <sys/types.h>
#elif __GNUC__
#include <cstddef>
#endif

#include <algorithm>

namespace stdlike {

template<class T> 
class vector {
    T* data;
    std::size_t _size;
    std::size_t _capacity;

public:
    vector();
    explicit vector(std::size_t count, const T& value);
    explicit vector(std::size_t count);

    ~vector();
    vector(const vector& other);
    vector& operator=(const vector& other);
    vector(vector&& other) noexcept;
    vector& operator=(vector&& other) noexcept;

    // Element access
    T& operator[](std::size_t pos);
    const T& operator[](std::size_t pos) const;

    // Iterators
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;

    // Capacity
    bool empty() const;
    std::size_t size() const;
    std::size_t capacity() const;

    // Modifiers
    void clear();
    void push_back(T value);
    void pop_back();


    // friend bool operator==(const vector<T>& lhs, const vector<T>& rhs);
};

}