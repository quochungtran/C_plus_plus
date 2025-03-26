#ifndef DATA_STRUCTURES_NODE_HPP_
#define DATA_STRUCTURES_NODE_HPP_

#include <iostream>
#include <memory>
#include <vector> 

template  <class ValueType>
struct Node
{
    using node_type = ValueType;
    ValueType data = {};
    std::shared_ptr<Node<ValueType>> next = {};
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

#endif  // DATA_STRUCTURES_NODE_HPP_