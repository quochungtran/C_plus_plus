#include <iostream>
#include <iomanip>
#include <cmath>
#include <map>
#include <set>
#include <string>
#include <memory>

#define ALPHABET_SIZE 26
using namespace std;

// Complexity: O((n+q)∗string_length)

class TrieNode{
public:
    std::unique_ptr<TrieNode> children_[ALPHABET_SIZE];
    int maxWeight;

    TrieNode(){
        maxWeight = -1;        
    }
};

class Trie {
private:
    std::unique_ptr<TrieNode> root_;  // Use unique_ptr for root_
public:
    Trie(){
        root_ = std::make_unique<TrieNode>();  // Initialize root_ with a new TrieNode
    }

    void insert(const string& word, int weight)
    {
        TrieNode* curr = root_.get();  // Use get() to access the raw pointer
        for (const char& c: word)
        {
            int pos = c - 'a';
            if (curr->children_[pos] == nullptr)
            {
                curr->children_[pos] = std::make_unique<TrieNode>();
            }
            curr = curr->children_[pos].get();
            curr->maxWeight = max(curr->maxWeight, weight);
        }

    }

    int getHighestMatching(const string& word)
    {
        TrieNode* curr = root_.get();  // Use get() to access the raw pointer
        for (const char& c : word)
        {
            int pos = c - 'a';
            if (curr->children_[pos] == nullptr)
            {
                return -1;
            }
            curr = curr->children_[pos].get();
        }

        return curr->maxWeight;
    }


};

int main()
{   
    int n, q, value;
    string s;
    cin >> n >> q;

    Trie trie;

    for (int i = 0; i < n; i++)
    {
        cin >> s >> value;
        trie.insert(s, value);
    }

    for (int i = 0; i < q; i++)
    {
        cin >> s;
        cout << trie.getHighestMatching(s) << endl;
    }

    return 0;
}