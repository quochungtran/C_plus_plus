
#include <cstddef>
#include <utility>
#include <stdexcept>


namespace data_structure{

template <typename T, std::size_t N>
class Array{

public:
    Array() = default;
    Array(T&& value);

    void insert(int index, T&& value);
    void remove(int index);
    T& operator[](unsigned int index);

private:
    T _buffer[N];
    size_t _currSize = 0;
};

template <typename T, size_t N>
Array<T, N>::Array(T&& value){
    for(int i = 0; i < N; i++){
        _buffer[i] = std::forward<T>(value);
    }
    _currSize = N;
}

template <typename T, size_t N>
T& Array<T, N>::operator[](unsigned int index){
    return _buffer[index];
}

template <typename T, size_t N>
void Array<T, N>::insert(int index, T&& value){
    if (_currSize >= N){
        throw std::out_of_range("index out of range");
    }

    for (int i = _currSize - 1; i >= index; i--){
        _buffer[i+1] = _buffer[i];
    }
    _buffer[index] = std::forward<T>(value);
    _currSize += 1;
}

template <typename T, size_t N>
void Array<T, N>::remove(int index){
    for (int i = index; i <= N-2; i++){
        _buffer[index] = _buffer[index+1];
    }
    _buffer[N-1] = 0;
    _currSize -= 1;
}

} // namespace data_structure