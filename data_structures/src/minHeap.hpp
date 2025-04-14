#include <vector>
#include <node.hpp>

namespace data_structure{

template <class ValueType>
class MinHeap{

public:
    void push(Node<ValueType> val){
        _heap.push_back(val);
        bubbleUp(_heap.size()-1);
    }

    Node<ValueType> getMin() const {return _heap[0].data;}

    std::size_t getSize() const {return _heap.size();}

private: 
    int parent(int i) { return (i-1) / 2 ;}
    int left (int i) { return 2*i + 1;}
    int right (int i) {return 2*i + 2;}

private:
    void bubbleUp(int index){
        while (index > 1 && _heap[parent].data > _heap[index].data){
            std::swap(_heap[parent], _heap[index]);
            index = parent(index);
        }
    }

    std::vector<Node<ValueType>> _heap;
};
}