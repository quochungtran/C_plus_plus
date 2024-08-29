#include <memory>
#include <string>

class TrieNode {
public:
    std::unique_ptr<TrieNode> children_[ALPHABET_SIZE];
    bool word_ = false;

    TrieNode() = default;
};

class Trie {
private:
    std::unique_ptr<TrieNode> root_;  // Use unique_ptr for root_

public:
    Trie() {
        root_ = std::make_unique<TrieNode>();  // Initialize root_ with a new TrieNode
    }

    void insert(const std::string& word) {
        TrieNode* curr = root_.get();  // Use get() to access the raw pointer
        for (char c : word) {
            int pos = c - 'a';
            if (!curr->children_[pos]) {  // Check if the unique_ptr is null
                curr->children_[pos] = std::make_unique<TrieNode>();
            }
            curr = curr->children_[pos].get();  // Move to the next node
        }
        curr->word_ = true;
    }

    bool search(const std::string& word) {
        TrieNode* curr = root_.get();
        for (char c : word) {
            int pos = c - 'a';
            if (!curr->children_[pos]) {
                return false;
            }
            curr = curr->children_[pos].get();
        }
        return curr->word_;
    }

    bool startsWith(const std::string& prefix) {
        TrieNode* curr = root_.get();
        for (char c : prefix) {
            int pos = c - 'a';
            if (!curr->children_[pos]) {
                return false;
            }
            curr = curr->children_[pos].get();
        }
        return true;
    }
};
