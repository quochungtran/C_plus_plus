/**
Implement std::list container, that support constant time insertion and removal of elements from anywhere
in the container.

Fast random access is not supported it's usually implemented as a double linked list
*/

#ifndef DATA_STRUCTURES_LIST_HPP_
#define DATA_STRUCTURES_LIST_HPP_

#include <cstddef>
#include <iterator>

namespace data_structure{

template <typename T>
class DoubleLinkedList{
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value, Node* p = nullptr, Node* n=nullptr):
            data(value), prev(p), next(n) {}
    };

    Node* _head = nullptr;
    Node* _tail = nullptr;
    size_t _size = 0;

public:

class iterator{
friend class DoubleLinkedList;
    Node* _node;
    const DoubleLinkedList* _owner;
    iterator(Node* n, const DoubleLinkedList* owner): _node(n), _owner(owner){}
public:
    T& operator*() const {return _node->data;}
    T* operator->() const {return &_node->data;}
    iterator& operator++() {
        _node = _node->next;
        return *this;
    }
    iterator& operator--(){
        _node = _node ? _node->prev: _owner->_tail;
        return *this;
    }
    bool operator==(const iterator& other) const { return _node == other._node; }
    bool operator!=(const iterator& other) const { return !(*this == other); }
};

using const_iterator = iterator;

public:

    // -------------- rule of 5 --------------
    DoubleLinkedList() = default;
    // keep it simple by disabling copy
    DoubleLinkedList(const DoubleLinkedList& other) = delete;
    DoubleLinkedList& operator=(const DoubleLinkedList& other) = delete;

    DoubleLinkedList(DoubleLinkedList&& other): _head(other._head), _tail(other._tail), _size(other._size) {
        other._head = nullptr;
        other._tail = nullptr;
        other._size = 0;
    }

    DoubleLinkedList& operator=(DoubleLinkedList&& other){
        if (this != &other){
            clear();
            _head = other._head;
            _tail = other._tail;
            _size = other._size;
            other._head = nullptr;
            other._tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    void clear() {
        auto curr = _head;
        while (curr){
            auto next = curr->next;
            delete curr;
            curr = next;
        }
        _head = _tail = nullptr;
        _size = 0;
    }

    size_t size() const { return _size; }
    bool empty() const { return _size == 0; }
    
    // -------------- element access --------------
    T& front() {return _head->data; }
    const T& front() const {return _head->data;}
    T& back() {return _tail->data;}
    const T& back() const {return _tail->data;}
    
    // -------------- modifications --------------
    // insert value before pos, O(1): only pointer relinking, no shifting
    iterator insert(const_iterator pos, const T& value){
        Node* nodeAtPos = const_cast<Node*>(pos._node);
        Node* prev = nodeAtPos ? nodeAtPos->prev: _tail;
        auto newNodeToAdd = new Node(value, prev, nodeAtPos);

        if (prev)    prev->next = newNodeToAdd; else _head = newNodeToAdd;
        if (nodeAtPos)nodeAtPos->prev = newNodeToAdd; else _tail = newNodeToAdd;

        _size++;
        return iterator(newNodeToAdd, this);
    }

    iterator insert(const_iterator pos, T&& value){
        Node* nodeAtPos = const_cast<Node*>(pos._node);
        Node* prev = nodeAtPos ? nodeAtPos->prev: _tail;
        auto newNodeToAdd = new Node(std::move(value), prev, nodeAtPos);

        if (prev)      prev->next = newNodeToAdd; else _head = newNodeToAdd;
        if (nodeAtPos) nodeAtPos->prev = newNodeToAdd; else _tail = newNodeToAdd;
        
        _size++;
        return iterator(newNodeToAdd, this);
    }
   

    // -------------- iterators --------------
    iterator begin() const {
        return iterator(_head, this);
    }

    iterator end() const {
        return iterator(nullptr, this);
    }
};
}

#endif  // DATA_STRUCTURES_LIST_HPP_
