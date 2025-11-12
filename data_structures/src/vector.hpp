#pragma once

#include <cstddef>

namespace data_structure {

template <typename T>
class Vector {
public:
    Vector();
    Vector(unsigned int size, const T& initial);
    Vector(unsigned int size);
    ~Vector();

    void push_back(const T& value);
    void reserve(unsigned int size);
    void resize(unsigned int size);
    auto size() const;
    auto capacity() const;

    T& operator[](unsigned int index);
    void clear();

private:
    size_t _capacity;
    size_t _size;
    T* _buffer;
};

template <typename T>
Vector<T>::Vector() : _capacity(0), _size(0), _buffer(nullptr) {}

template <typename T>
Vector<T>::Vector(unsigned int size)
    : _capacity(size), _size(size), _buffer(new T[size]) {}

template <typename T>
Vector<T>::Vector(unsigned int size, const T& initial)
    : _capacity(size), _size(size), _buffer(new T[size]) {
    for (unsigned int i = 0; i < size; ++i)
        _buffer[i] = initial;
}

template <typename T>
Vector<T>::~Vector() {
    clear();
}

template <typename T>
void Vector<T>::reserve(unsigned int newCapacity) {
    if (newCapacity <= _capacity) return;
    T* newBuffer = new T[newCapacity];
    for (unsigned int i = 0; i < _size; ++i)
        newBuffer[i] = _buffer[i];
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
auto Vector<T>::size() const {
    return _size;
}

template <typename T>
auto Vector<T>::capacity() const{
    return _capacity;
}

template <typename T>
void Vector<T>::clear() {
    delete[] _buffer;
    _buffer = nullptr;
    _capacity = 0;
    _size = 0;
}

template <typename T>
T& Vector<T>::operator[](unsigned int index) {
    return _buffer[index];
}

template <typename T>
void Vector<T>::resize(unsigned int size) {
    reserve(size);
    _size = size;
}

} // namespace data_structure
