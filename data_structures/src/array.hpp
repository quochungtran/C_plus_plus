#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace data_structure {

template <typename T, std::size_t N>
class Array {
public:
    Array() = default;
    explicit Array(const T& value);

    void insert(std::size_t index, T value);
    void remove(std::size_t index);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    std::size_t size() const { return _currSize; }
    static constexpr std::size_t capacity() { return N; }

private:
    T _buffer[N]{};
    std::size_t _currSize = 0;
};

template <typename T, std::size_t N>
Array<T, N>::Array(const T& value) {
    for (std::size_t i = 0; i < N; ++i)
        _buffer[i] = value;
    _currSize = N;
}

template <typename T, std::size_t N>
T& Array<T, N>::operator[](std::size_t index) {
    if (index >= _currSize)
        throw std::out_of_range("Array: index out of range");
    return _buffer[index];
}

template <typename T, std::size_t N>
const T& Array<T, N>::operator[](std::size_t index) const {
    if (index >= _currSize)
        throw std::out_of_range("Array: index out of range");
    return _buffer[index];
}

template <typename T, std::size_t N>
void Array<T, N>::insert(std::size_t index, T value) {
    if (_currSize >= N)
        throw std::out_of_range("Array: full");
    if (index > _currSize)
        throw std::out_of_range("Array: index out of range");
    for (std::size_t i = _currSize; i > index; --i)
        _buffer[i] = std::move(_buffer[i - 1]);
    _buffer[index] = std::move(value);
    ++_currSize;
}

template <typename T, std::size_t N>
void Array<T, N>::remove(std::size_t index) {
    if (index >= _currSize)
        throw std::out_of_range("Array: index out of range");
    for (std::size_t i = index; i < _currSize - 1; ++i)
        _buffer[i] = std::move(_buffer[i + 1]);   // was: _buffer[index] = _buffer[index+1] (bug)
    _buffer[--_currSize] = T{};
}

} // namespace data_structure
