#ifndef DATA_STRUCTURES_STACK_HPP_
#define DATA_STRUCTURES_STACK_HPP_


#include "node.hpp"
#include <stdexcept>  /// for std::invalid_argument

namespace data_structure {

template <class ValueType>
class stackK {
public:
    using value_type = ValueType;

    bool isEmptyStack() const {return (stackTop == nullptr);}

    void push(const value_type& item){
        auto newNode = std::make_shared<Node<value_type>>();
        newNode->data = item;
        newNode->next = stackTop;
        stackTop = newNode;
        _size++;
    }

    void pop() {
        ensureNotEmpty();
        stackTop = stackTop->next;
        _size--;
    }
    
    value_type top() const{
        ensureNotEmpty();
        return stackTop->data;
    }

    void clear() {
        stackTop = nullptr;
        _size = 0;
    }

    void display() const {
        std::cout << "Top --> ";
        display_all(this->stackTop.get());
        std::cout << "\n";
        std::cout << "Size of stack" << _size << std::endl; 
    }

private:
    void ensureNotEmpty() const {
        if (isEmptyStack()){
            throw std::invalid_argument("Stack is empty.");
        }
    }

private:
    std::shared_ptr<Node<value_type>> stackTop = {};
    std::size_t _size = 0;
};

}
#endif  // DATA_STRUCTURES_STACK_HPP_