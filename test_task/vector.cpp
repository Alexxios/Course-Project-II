#include "vector.hpp"
#include <algorithm>
#include <iostream>


namespace stdlike {

template<class T>
vector<T>::vector() : data(new T[0]()), _size(0), _capacity(0) {}

template<class T> 
vector<T>::vector(std::size_t count, const T& value) : data(new T[count]), _size(count), _capacity(count) {
    std::fill_n(data, count, value);
}

template<class T>
vector<T>::vector(std::size_t count) : data(new T[count]()), _size(count), _capacity(count) {
}

template<class T>
vector<T>::~vector() {
    if (data != nullptr) delete[] data;
}

template<class T>
vector<T>::vector(const vector& other) 
    : data(new T[other._capacity]), _size(other._size), _capacity(other._capacity) {
    std::copy(other.data, other.data + other._size, data);
}

template<class T>
vector<T>& vector<T>::operator=(const vector& other) {
    if (this != &other) {    
        delete[] data;
        data = new T[other._capacity];
        std::copy(other.data, other.data + other._size, data);
    }
    return *this;
}

template<class T>
vector<T>::vector(vector&& other) noexcept {
    data = other.data;
    _size = other._size;
    _capacity = other._capacity;

    other.data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<class T>
vector<T>& vector<T>::operator=(vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;

        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    
    return *this;
}

template<class T>
T& vector<T>::operator[](std::size_t pos) {
    return data[pos];
}

template<class T>
const T& vector<T>::operator[](std::size_t pos) const {
    return data[pos];
}

template<class T>
T* vector<T>::begin() {
    return data;
}

template<class T>
T* vector<T>::end() {
    return data + _size;
}

template<class T>
bool vector<T>::empty() const {
    return _size == 0;
}

template<class T>
std::size_t vector<T>::size() const {
    return _size;
}

template<class T>
std::size_t vector<T>::capacity() const {
    return _capacity;
}

template<class T>
void vector<T>::clear() {
    std::fill_n(data, _size, T());
    _size = 0;
}

template<class T>
void vector<T>::push_back(T value) {
    if (_size == _capacity) {
        _capacity = 2 * _capacity + 1;
        T* new_data = new T[_capacity];
        std::copy(data, data + _size, new_data);
        delete[] data;
        data = new_data;
    }
    data[_size] = value;
    ++_size;
}

template<class T>
void vector<T>::pop_back() {
    --_size;
    data[_size] = T();
}
}


int main(int argc, char *argv[]) {
    stdlike::vector<int> v(10);
    stdlike::vector<int> v2(v);
    stdlike::vector<int> v3 = v;
    
    v3[0] = 1;
    std::cout << v3[0] << std::endl;
    std::cout << v.end() << std::endl;
    std::cout << v2.end() << std::endl;
    std::cout << v3.end() << std::endl;
    
    stdlike::vector<int> v4(std::move(v));
    v4.push_back(1);
    std::cout << v4.end() << std::endl;
    std::cout << v4[v4.size() - 1] << std::endl;
    
    return 0;
}