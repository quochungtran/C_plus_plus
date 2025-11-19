#include "gtest/gtest.h"
#include <sstream>
#include "node.hpp"

using namespace data_structure;

// Helper function to collect output of display_all
template <typename T>
std::string get_display_output(const std::shared_ptr<Node<T>>& head) {
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    display_all(head.get());

    std::cout.rdbuf(oldCout);
    return oss.str();
}

TEST(NodeTest, EmptyNodeTest) {
    std::shared_ptr<Node<int>> nullNode;
    std::string output = get_display_output(nullNode);
    EXPECT_EQ(output, "");
}

TEST(NodeTest, TestMoveSemanticsWithString) {
    std::string str = "hello";

    auto node = std::make_shared<Node<std::string>>(std::move(str));

    auto output = get_display_output(node);
    EXPECT_EQ(output, "hello ");

    // This now verifies that str has been moved from
    EXPECT_TRUE(str.empty()) << "Expected 'str' to be empty after move, got: '" << str << "'";
}



TEST(NodeTest, SingleNodeTest){
    auto node = std::make_shared<Node<int>>(12);
    auto output = get_display_output(node);
    EXPECT_EQ(output, "12 ");
}

TEST(NodeTest, MutipleNodeTraversalTest){
    auto node1 = std::make_shared<Node<int>>(1);
    auto node2 = std::make_shared<Node<int>>(2, node1);
    auto node3 = std::make_shared<Node<int>>(3, node2);

    auto output = get_display_output(node3);
    EXPECT_EQ(output, "3 2 1 ");
}

TEST(NodeTest, TraverseWithCustomAction){
    auto node1 = std::make_shared<Node<int>>(1);
    auto node2 = std::make_shared<Node<int>>(2, node1);

    std::vector<int> collected_data;
    traverse(node2.get(), [&](const Node<int>& n){
        collected_data.push_back(n.data);
    });
    
    std::vector<int> expected = {2, 1};
    EXPECT_EQ(collected_data, expected);
}