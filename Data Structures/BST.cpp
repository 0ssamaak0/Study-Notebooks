#include <bits/stdc++.h>
using namespace std;

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
bool is_BST(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    if (root->left != NULL)
    {
        if (root->data < root->left->data)
        {
            return false;
        }
    }
    if (root->right != NULL)
    {
        if (root->data > root->right->data)
        {
            return false;
        }
    }
    return (is_BST(root->right) & is_BST(root->left));
}

int tree_min(Node *root)
{
    if (root->left == NULL)
    {
        return root->data;
    }
    return tree_min(root->left);
}

int tree_max(Node *root)
{
    if (root->right == NULL)
    {
        return root->data;
    }
    return tree_max(root->right);
}

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

Node *search(Node *root, int data)
{
    if (root == NULL || root->data == data)
    {
        return root;
    }
    if (root->data < data)
    {
        return search(root->right, data);
    }
    else
    {
        return search(root->left, data);
    }
}

Node *insert(Node *root, int value)
{
    if (!root)
    {
        return new Node(value);
    }
    if (value > root->data)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        root->left = insert(root->left, value);
    }
    return root;
}

Node *deleteNode(Node *root, int data)
{
    // base case
    if (root == NULL)
    {
        return root;
    }
    // if smaller or greater than root
    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    // the root itself
    else
    {
        // 1) no children (delete or free)
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }

        // 2) single child: take child's value (delete or free)
        else if (root->left == NULL)
        {
            Node *temp = root->right;
            delete (root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            delete (root);
            return temp;
        }
        // 3) two children: min right or max left
        Node *temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}
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

int main(void)
{
    Node *root = new Node(5);

    root->right = new Node(6);
    root->right->right = new Node(7);
    root->right->left = new Node(4);
    root->left = new Node(2);
    root->left->right = new Node(3);
    root->left->left = new Node(1);

    inorderTraversal(root);
    cout << is_BST(root) << "\n";
}