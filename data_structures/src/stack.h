#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_

#include <iostream>

namespace data_structure {

template<typename T>
class Stack{
public:
    virtual ~Stack() {}; 
    virtual std::size_t getSize() const                       = 0;
    virtual bool isEmpty() const                              = 0;
    virtual void push(const T& iValue)                        = 0;
    virtual void push(const T&& iValue)                       = 0;
    virtual T pop()                                           = 0;
    virtual const T& top() const                              = 0;
    virtual void clear()                                      = 0;
    virtual std::ostream& toStream(std::ostream& ioOut) const = 0;
};

template<typename T>
std::ostream& operator<<(std::ostream& ioOut, const Stack<T>& iStack){
    return iStack.toStream();
}
}
#endif  // DATA_STRUCTURES_STACK_HPP_