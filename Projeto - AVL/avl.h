#ifndef AVL_H
#define AVL_H

#include <iostream>

template <typename T>
class AVLTree
{
private:
    struct Node
    {
        T data;
        Node *left;
        Node *right;
        int height;
        Node(T data) : data(data), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    Node *rotateRight(Node *node);
    Node *rotateLeft(Node *node);
    Node *rotateRightLeft(Node *node);
    Node *rotateLeftRight(Node *node);
    int getHeight(Node *node);
    int getBalanceFactor(Node *node);
    Node *balance(Node *node);
    Node *insert(Node *node, T data);
    void inOrderTraversal(Node *node);
    void preOrderTraversal(Node *node);
    void postOrderTraversal(Node *node);
    void destroy(Node *node);

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();
    void insert(T data);
    void inOrderTraversal();
    void preOrderTraversal();
    void postOrderTraversal();
};

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::rotateRight(Node *node)
{
    Node *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    leftChild->height = std::max(getHeight(leftChild->left), getHeight(leftChild->right)) + 1;
    return leftChild;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::rotateLeft(Node *node)
{
    Node *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    rightChild->height = std::max(getHeight(rightChild->left), getHeight(rightChild->right)) + 1;
    return rightChild;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::rotateRightLeft(Node *node)
{
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::rotateLeftRight(Node *node)
{
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

template <typename T>
int AVLTree<T>::getHeight(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

template <typename T>
int AVLTree<T>::getBalanceFactor(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::balance(Node *node)
{
    int balanceFactor = getBalanceFactor(node);
    if (balanceFactor > 1)
    {
        if (getBalanceFactor(node->left) > 0)
        {
            node = rotateRight(node);
        }
        else
        {
            node = rotateLeftRight(node);
        }
    }
    else if (balanceFactor < -1)
    {
        if (getBalanceFactor(node->right) < 0)
        {
            node = rotateLeft(node);
        }
        else
        {
            node = rotateRightLeft(node);
        }
    }
    return node;
}

template <typename T>
typename AVLTree<T>::Node *AVLTree<T>::insert(Node *node, T data)
{
    if (node == nullptr)
    {
        node = new Node(data);
        return node;
    }
    if (data < node->data)
    {
        node->left = insert(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insert(node->right, data);
    }
    else
    {
        return node;
    }
    node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    node = balance(node);
    return node;
}

template <typename T>
void AVLTree<T>::insert(T data)
{
    root = insert(root, data);
}

template <typename T>
void AVLTree<T>::inOrderTraversal(Node *node)
{
    if (node != nullptr)
    {
        inOrderTraversal(node->left);
        std::cout << node->data << " ";
        inOrderTraversal(node->right);
    }
}

template <typename T>
void AVLTree<T>::preOrderTraversal(Node *node)
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preOrderTraversal(node->left);
        preOrderTraversal(node->right);
    }
}

template <typename T>
void AVLTree<T>::postOrderTraversal(Node *node)
{
    if (node != nullptr)
    {
        postOrderTraversal(node->left);
        postOrderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
void AVLTree<T>::inOrderTraversal()
{
    inOrderTraversal(root);
}

template <typename T>
void AVLTree<T>::preOrderTraversal()
{
    preOrderTraversal(root);
}

template <typename T>
void AVLTree<T>::postOrderTraversal()
{
    postOrderTraversal(root);
}

template <typename T>
AVLTree<T>::~AVLTree()
{
    destroy(root);
}

template <typename T>
void AVLTree<T>::destroy(Node *node)
{
    if (node != nullptr)
    {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

#endif // AVL_H