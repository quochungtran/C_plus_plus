#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stack.h>

namespace data_structure
{
template <typename T>
class StackUsingSingleList: public Stack<T>{

public:
    ~StackUsingSingleList(){
        clear();
    }

    std::size_t getSize() const override{
        return _size;
    }

    bool isEmpty() const override{
        return _size == 0;
    }

    void push(const T& iValue) override{
        _head = std::make_shared<listNode> (iValue, _head);
        _size++;
    }

    void push(const T&& iValue) override{
        _head = std::make_shared<listNode> (std::move(iValue),_head);
        _size++;
    }

    T pop() override{
        assert(!isEmpty());
        auto value = std::move(_head->data);
        _head = std::move(_head->next);
        _size -= 1;
        
        return value;
    }

    const T& top() const override{
        assert(!isEmpty());
        return _head->data;
    }

    void clear() override{
        while (_head){
            // head->next is now nullptr after move operation
            // the ownership of head->next move to next
            _head = std::move(_head->next);
            _size -= 1;
        }
    }

    std::ostream& toStream(std::ostream& iOut) const override{
        iOut << "[";
        auto current = _head;
        while (current){
            iOut << current->data;
            current = current->next;
            if (current){
                iOut << ",";
            }
        }
        iOut << "]";
        return iOut;
    }
private:

    struct listNode
    {
        T data;
        std::shared_ptr<listNode> next;

        explicit listNode(T iValue, std::shared_ptr<listNode> nextlistNode = nullptr)
            : data(std::move(iValue)), next(std::move(nextlistNode)){}
    };
    
    std::shared_ptr<listNode> _head = nullptr;
    std::size_t _size = 0;
};
} // namespace datastructure