#include <vector>
#include <node.hpp>

namespace data_structure{

template <class ValueType>
class MinHeap{

public:
    MinHeap(){
        _heap.push_back(Node<ValueType>()); // Dummy value to fill index_0
    }

    void push(Node<ValueType> val){
        _heap.push_back(val);
        bubbleUp(_heap.size()-1);
    }


private:
    void bubbleUp(int index){
        int parent = index/2;
        while (index > 1 && heap[parent].data > heap[index].data){
            swap(heap[parent], heap[index]);
            index = parent;
            parent /= 2;
        }
    }
    std::vector<Node<ValueType>> _heap;
};
}