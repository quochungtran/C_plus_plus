#pragma once

#include <iostream>

namespace data_structure {

// Abstract interface — lets you swap implementations (array vs linked) transparently
template<typename T>
class Stack {
public:
    virtual ~Stack() = default;
    virtual std::size_t getSize() const                        = 0;
    virtual bool isEmpty() const                               = 0;
    virtual void push(const T& value)                          = 0;
    virtual void push(T&& value)                               = 0;
    virtual T pop()                                            = 0;
    virtual const T& top() const                               = 0;
    virtual void clear()                                       = 0;
    virtual std::ostream& toStream(std::ostream& out) const    = 0;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Stack<T>& stack) {
    return stack.toStream(out);
}

} // namespace data_structure
