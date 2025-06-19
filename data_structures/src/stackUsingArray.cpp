#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>

namespace datastructure
{
/**
 * @brief Class datastructure of a stack
 * @param T the type of elements in the stack
 */

template <typename T>
class StackUsingArray {
public:
    StackUsingArray(int size):
        _stackSize(size), 
        _stackIndex(-1), 
        _stack(std::make_unique<T[]>(_stackSize)){}
    
    StackUsingArray(StackUsingArray&& stk):
      _stackSize(stk._stackSize),      
      _stackIndex(stk._stackIndex),
      _stack(std::move(stk._stack)) {}

    bool full() const {
        return _stackSize - 1 == _stackIndex;
    }

    bool isEmpty() const{
        return _stackIndex == -1;
    }

    void push(T element) {
        if (this->full()){
            throw std::out_of_range("Stack overflow");
        }
        else{
            _stack[++_stackIndex] = element;
        }
    }

    T pop() {
        if (this->isEmpty()){
            throw std::out_of_range("Stack underflow");
        }

        return _stack[_stackIndex--];
    }


    friend std::ostream& operator<<(std::ostream& os, const StackUsingArray& iStack){
        os << "[";
        for (int i = 0; i <= iStack.getIndex(); i++){
            os << iStack.getArray()[i];
            if (i < iStack.getIndex()){
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

protected:

    auto getSize() const {
        return _stackSize;
    }

    const T* getStackContent() const{
        return _stack.get();
    }

    auto getIndex() const{
        return _stackIndex;
    }

private:
    std::size_t _stackSize;
    int _stackIndex;
    std::unique_ptr<T[]> _stack;
};
} // namespace datastructure