#include <iostream>
using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
}

Node* createNode(int x)
{
    Node* newNode = new Node;
    newNode->key  = x;
    newNode->left = newNode->right = nullptr;
    return newNode; 
}
// Complexity : O(1)


// insert a new value into BST
// Average compexity: O(h), worst case : O(N)
Node* insertNode (Node* root, int x)
{
    // if current Node is nullptr
    if (root == nullptr)
    {
        return createNode(x);
    }

    if ( x < root->key)
    {
        root->left = insertNode(root->left, x);
    }
    else if (x > root->key)
    {
        root->right = insertNode(root->right, x);
    }

    return root;
}


// create a BST based on a list of values
// Complexity : O(N*h)
void createTree(Node* &root, int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        root = insertNode(root, a[i]);
    }
}

// Search Node in BST
// O(h)
Node* searchNode(Node* root, int x)
{
    if (root == nullptr || root->key == x)
    {
        return root;
    }

    if (root->key < x)
    {
        return searchNode(root->right, x);
    }

    return searchNode(root->left, x);
}


// Delete a Node in BST
// Case 1: delete the leaf node in BST
// Case 2: delete one node containing one/two nodes
// Case 3: another cases
// O(h)

Node* minValueNode(Node* node)
{
    Node* current = node;
    while(current->left != nullptr)
    {
        current = current->left;
    }

    return current;
}

Node deleteNode(Node* &root, int x)
{
    if (root == nullptr)
    {
        return root;
    }

    if (x < root->key)
    {
        root->left = deleteNode(root->left, x);
    }
    else if (x > root->key)
    {
        root->right = deleteNode(root->right, x);
    }
    else // x == root->key 
    {
        if (root->left == nullptr)
        {
            Node* temp = root->right;
            delete = root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp  = minValueNode(root->right);
        root->key   = temp->key;
        root->right = deleteNode(root->right, temp->key); 
    }

    return root;
}

Node* upper_bound(Node* root, x)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    
    if (root->key <= x)
    {
        return upper_bound(root->right, x);
    }
    else if (root->key > x)
    {
        auto up_left = upper_bound(root->left, x);
        return (up_left == nullptr ? root->key : up_left);
    }
}

// traversal the BST
// Inorder traversal (left->root->right)
// Preoder traversal (root->left->right)
// postorder traversal (left->right->root)
// O(N)

void traversalTree(Node* root)
{
    if (root != nullptr)
    {
        traversalTree(root->left);
        cout << root->key << " ";
        traversalTree(root->right);
    }
}

// size of the BST
// O9N
int size(Node* node)
{
    if (node == nullptr)
        return 0;
    else
        return (size(node->left) + 1 + size(node->right));
}

void deleteTree(Node* root)
{
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete(root);
}

// application when use set and hash map std::set, 