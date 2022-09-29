#include <bits/stdc++.h>
using namespace std;

#define MAX_NO_OF_CHILDREN = 10;

// --- Gneral Tree ---
// class Node{
//     int data;
//     // array
//     Node* children[MAX_NO_OF_CHILDREN]
//     // linkedlist
//     list<Node *> children;
// }
// class Tree{
//     Node* root;
//     // methods
// }

// --- Binary Tree ---

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int x)
    {
        this->data = x;
    }
};

class Tree
{
public:
    Node *root;

    int count_leaves_in_subtree(Node *node)
    {
        if (node->left == NULL && node->right == NULL)
        {
            return 1;
        }
        int leaves = 0;
        if (node->left != NULL)
        {
            leaves += count_leaves_in_subtree(node->left);
        }
        if (node->right != NULL)
        {
            leaves += count_leaves_in_subtree(node->right);
        }
        return leaves;
    }

    int count_leaves()
    {
        return count_leaves_in_subtree(root);
    }
};

// DFT
void inorderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    inorderTraversal(node->left);
    cout << node->data << "\n";
    inorderTraversal(node->right);
}

void PostOrderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    PostOrderTraversal(node->left);
    PostOrderTraversal(node->right);
    cout << node->data << "\n";
}

void PreOrderTraversal(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << "\n";
    PreOrderTraversal(node->left);
    PreOrderTraversal(node->right);
}

void BFT(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    queue<Node *> q;
    q.push(node);

    while (!q.empty())
    {
        node = q.front();
        q.pop();

        cout << node->data << " ";

        if (node->left != NULL)
        {
            q.push(node->left);
        }

        if (node->right != NULL)
        {
            q.push(node->right);
        }
    }
    cout << "\n";
}

int main(void)
{
    Tree t;
    t.root = new Node(3);
    t.root->right = new Node(10);
    t.root->right->left = new Node(10);
    t.root->right->right = new Node(10);
    t.root->left = new Node(5);
    t.root->left->left = new Node(7);
    t.root->left->right = new Node(8);
    t.root->left->right->right = new Node(9);
    t.root->left->right->right->left = new Node(9);
    t.root->left->right->right->right = new Node(9);

    inorderTraversal(t.root);
    BFT(t.root);
    cout << "\n"
         << t.count_leaves() << "\n";
}