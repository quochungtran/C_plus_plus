#pragma once

#include <atomic>
#include <utility>
#include <stdexcept>

namespace data_structure {

struct ControlBlock {
    std::atomic<int> ref_count{1};

    ControlBlock() = default;
    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;
};

template <typename T>
class SharedPointer {
public:
    explicit SharedPointer(T* ptr = nullptr);
    ~SharedPointer();

    SharedPointer(const SharedPointer& other);
    SharedPointer& operator=(const SharedPointer& other);

    // Move: steal ownership — no ref-count change needed
    SharedPointer(SharedPointer&& other) noexcept;
    SharedPointer& operator=(SharedPointer&& other) noexcept;

    T& operator*();
    const T& operator*() const;
    T* operator->();
    const T* operator->() const;

    T* get() const;
    int use_count() const;
    explicit operator bool() const;

private:
    T* _ptr;
    ControlBlock* _controlBlock;

    void increment();
    void decrement_and_maybe_free();
};

template <typename T>
SharedPointer<T>::SharedPointer(T* ptr)
    : _ptr(ptr), _controlBlock(ptr ? new ControlBlock() : nullptr) {}

template <typename T>
SharedPointer<T>::~SharedPointer() {
    decrement_and_maybe_free();
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& other)
    : _ptr(other._ptr), _controlBlock(other._controlBlock) {
    increment();
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& other) {
    if (this != &other) {
        decrement_and_maybe_free();
        _ptr = other._ptr;
        _controlBlock = other._controlBlock;
        increment();
    }
    return *this;
}

template <typename T>
SharedPointer<T>::SharedPointer(SharedPointer&& other) noexcept
    : _ptr(other._ptr), _controlBlock(other._controlBlock) {
    other._ptr = nullptr;
    other._controlBlock = nullptr;
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& other) noexcept {
    if (this != &other) {
        decrement_and_maybe_free();
        _ptr = other._ptr;
        _controlBlock = other._controlBlock;
        other._ptr = nullptr;
        other._controlBlock = nullptr;
    }
    return *this;
}

template <typename T>
T& SharedPointer<T>::operator*() { return *_ptr; }

template <typename T>
const T& SharedPointer<T>::operator*() const { return *_ptr; }

template <typename T>
T* SharedPointer<T>::operator->() { return _ptr; }

template <typename T>
const T* SharedPointer<T>::operator->() const { return _ptr; }

template <typename T>
T* SharedPointer<T>::get() const { return _ptr; }

template <typename T>
int SharedPointer<T>::use_count() const {
    return _controlBlock ? _controlBlock->ref_count.load(std::memory_order_relaxed) : 0;
}

template <typename T>
SharedPointer<T>::operator bool() const { return _ptr != nullptr; }

template <typename T>
void SharedPointer<T>::increment() {
    if (_controlBlock)
        _controlBlock->ref_count.fetch_add(1, std::memory_order_relaxed);
}

template <typename T>
void SharedPointer<T>::decrement_and_maybe_free() {
    if (!_controlBlock) return;
    // acq_rel: acquire ensures we see all writes from other threads before freeing;
    // release ensures our writes are visible to the thread that drops the last ref
    if (_controlBlock->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
        delete _ptr;
        delete _controlBlock;
    }
    _ptr = nullptr;
    _controlBlock = nullptr;
}

template <typename T, typename... Args>
SharedPointer<T> make_shared(Args&&... args) {
    return SharedPointer<T>(new T(std::forward<Args>(args)...));
}

} // namespace data_structure
