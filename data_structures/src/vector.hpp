#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <algorithm>

namespace data_structure {

template <typename T>
class Vector {
public:
    Vector();
    explicit Vector(std::size_t size);
    Vector(std::size_t size, const T& initial);
    ~Vector();

    // Rule of 5 — copying and moving are both supported
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    void push_back(const T& value);
    void push_back(T&& value);
    void reserve(std::size_t newCapacity);
    void resize(std::size_t newSize);
    void clear();

    std::size_t size() const;
    std::size_t capacity() const;

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;

private:
    std::size_t _capacity;
    std::size_t _size;
    T* _buffer;
};

template <typename T>
Vector<T>::Vector() : _capacity(0), _size(0), _buffer(nullptr) {}

template <typename T>
Vector<T>::Vector(std::size_t size)
    : _capacity(size), _size(size), _buffer(size ? new T[size]{} : nullptr) {}

template <typename T>
Vector<T>::Vector(std::size_t size, const T& initial)
    : _capacity(size), _size(size), _buffer(size ? new T[size] : nullptr) {
    for (std::size_t i = 0; i < size; ++i)
        _buffer[i] = initial;
}

template <typename T>
Vector<T>::~Vector() {
    delete[] _buffer;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : _capacity(other._capacity), _size(other._size),
      _buffer(other._capacity ? new T[other._capacity] : nullptr) {
    for (std::size_t i = 0; i < _size; ++i)
        _buffer[i] = other._buffer[i];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) return *this;
    Vector tmp(other);
    std::swap(_capacity, tmp._capacity);
    std::swap(_size, tmp._size);
    std::swap(_buffer, tmp._buffer);
    return *this;
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept
    : _capacity(other._capacity), _size(other._size), _buffer(other._buffer) {
    other._capacity = 0;
    other._size = 0;
    other._buffer = nullptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this == &other) return *this;
    delete[] _buffer;
    _capacity = other._capacity;
    _size = other._size;
    _buffer = other._buffer;
    other._capacity = 0;
    other._size = 0;
    other._buffer = nullptr;
    return *this;
}

template <typename T>
void Vector<T>::reserve(std::size_t newCapacity) {
    if (newCapacity <= _capacity) return;
    T* newBuffer = new T[newCapacity];
    for (std::size_t i = 0; i < _size; ++i)
        newBuffer[i] = std::move(_buffer[i]);
    delete[] _buffer;
    _buffer = newBuffer;
    _capacity = newCapacity;
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (_size >= _capacity)
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    _buffer[_size++] = value;
}

template <typename T>
void Vector<T>::push_back(T&& value) {
    if (_size >= _capacity)
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    _buffer[_size++] = std::move(value);
}

template <typename T>
void Vector<T>::resize(std::size_t newSize) {
    reserve(newSize);
    for (std::size_t i = _size; i < newSize; ++i)
        _buffer[i] = T{};
    _size = newSize;
}

template <typename T>
void Vector<T>::clear() {
    delete[] _buffer;
    _buffer = nullptr;
    _capacity = 0;
    _size = 0;
}

template <typename T>
std::size_t Vector<T>::size() const { return _size; }

template <typename T>
std::size_t Vector<T>::capacity() const { return _capacity; }

template <typename T>
T& Vector<T>::operator[](std::size_t index) { return _buffer[index]; }

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const { return _buffer[index]; }

template <typename T>
T& Vector<T>::at(std::size_t index) {
    if (index >= _size)
        throw std::out_of_range("Vector: index out of range");
    return _buffer[index];
}

template <typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index >= _size)
        throw std::out_of_range("Vector: index out of range");
    return _buffer[index];
}

} // namespace data_structure
