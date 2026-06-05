#pragma once

#include "stack.hpp"
#include "node.hpp"
#include <memory>
#include <stdexcept>

namespace data_structure {

// Concrete singly-linked implementation of Stack<T>.
// push/pop are O(1). Each element is heap-allocated as a Node.
// Trade-off vs array-backed: no reallocation, but pointer-chasing on every access.
template<typename T>
class LinkedStack : public Stack<T> {
    std::shared_ptr<Node<T>> head_;
    std::size_t size_;

public:
    LinkedStack() : head_(nullptr), size_(0) {}
    ~LinkedStack() override = default;

    std::size_t getSize() const override { return size_; }
    bool isEmpty() const override { return size_ == 0; }

    void push(const T& value) override {
        head_ = std::make_shared<Node<T>>(value, head_);
        ++size_;
    }

    void push(T&& value) override {
        head_ = std::make_shared<Node<T>>(std::move(value), head_);
        ++size_;
    }

    T pop() override {
        if (isEmpty())
            throw std::underflow_error("LinkedStack: pop on empty stack");
        T value = std::move(head_->data);
        head_ = head_->next;
        --size_;
        return value;
    }

    const T& top() const override {
        if (isEmpty())
            throw std::underflow_error("LinkedStack: top on empty stack");
        return head_->data;
    }

    void clear() override {
        head_ = nullptr;
        size_ = 0;
    }

    std::ostream& toStream(std::ostream& out) const override {
        traverse(head_.get(), [&out](const Node<T>& node) {
            out << node.data << " ";
        });
        return out;
    }
};

} // namespace data_structure
