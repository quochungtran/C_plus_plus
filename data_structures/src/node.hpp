#ifndef DATA_STRUCTURES_NODE_HPP_
#define DATA_STRUCTURES_NODE_HPP_

#include <iostream>
#include <memory>
#include <vector> 

namespace data_structure{
template  <class ValueType>
struct Node
{
    ValueType data = {};
    std::shared_ptr<Node<ValueType>> next = {};

    Node(const ValueType& value, std::shared_ptr<Node<ValueType>> nextNode = nullptr)
    : data((value)), next(std::move(nextNode)){}

    template<typename U>
    explicit Node(U&& value, std::shared_ptr<Node<ValueType>> nextNode = nullptr)
        : data(std::forward<U>(value)), next(std::move(nextNode)) {}
};

template <typename Node, typename Action>
void traverse(const Node* const inNode, const Action& action){
    if (inNode){
        action(*inNode),
        traverse(inNode->next.get(), action);
    }
}

template <typename Node>
void display_all(const Node* const inNode){
    traverse(inNode,
            [](const Node& curNode){std::cout << curNode.data << " ";});
}
}
#endif  // DATA_STRUCTURES_NODE_HPP_