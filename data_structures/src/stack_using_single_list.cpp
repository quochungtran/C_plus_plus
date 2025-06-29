#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stack.hpp>

namespace datastructure
{


template <typename T>
class StackUsingArray: public Stack{

public:
    ~StackUsingArray(){
        clear();
    }

    std::size_t getSize() const override{
        return _size;
    }

    bool isEmpty() const override{
        return _size == 0;
    }

    void push(const T& iValue) override{
        _head = std::unique_ptr<Node> (new Node {iValue, std::move(_head)});
        _size++;
    }

    void push(const T&& iValue) override{
        _head = std::unique_ptr<Node> (new Node{std::move(iValue), std::move(_head)});
        _size++;
    }

    T pop() const override{
        if (isEmpty()){
            throw std::underflow_error("Stack Underflow - stack is empty");
        }

        auto value = std::move(_head->data);
        _head = std::move(_head->next);
        _size -= 1;
        
        return value;
    }

    const T& top() const override{
        if (!isEmpty())
        {
            throw std::underflow_error("Stack Underflow - stack is empty");
        }
        return _head->data;
    }

    void clear() override{
        while (_head){
            // head->next is now nullptr after move operation
            // the ownership of head->next move to next
            _head = std::move(_head->next);
            _size -= 1
        }
    }

    std::ostream& toStream(std::ostream& iOut) const override{
        os << "[";
        auto current = _head;
        while (current){
            os << current->data;
            current = current->next;
            if (!current){
                break;
            }
            os << ",";
        }
        os << "]";
    }
private:

    struct Node
    {
        T data;
        stf::unique_ptr<Node> next;

        explicit Node(T iValue, std::unique_ptr<Node> nextNode = nullptr)
            : data(iValue), next(nextNode){}
    };
    
    std::unique_ptr<Node> _head;
    std::size_t _size;
};
} // namespace datastructure