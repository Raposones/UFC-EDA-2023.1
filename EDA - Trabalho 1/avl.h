#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <string>
#include <sstream>
#include "person.h"

template <typename var>
class AVL
{
private:
    struct Node
    {
        var key;
        Person *person;
        Node *left;
        Node *right;
        int height;

        Node(var k, Person *p)
        {
            this->key = k;
            this->person = p;
            this->left = nullptr;
            this->right = nullptr;
            this->height = 1;
        }
    };

    Node *root;
    bool allow_duplicates;

    Node *insert(Node *node, var key, Person *person);
    Node *rotate_left(Node *node);
    Node *rotate_right(Node *node);
    Node *rotate_rl(Node *node);
    Node *rotate_lr(Node *node);
    int height(Node *node);
    int balance_factor(Node *node);
    Node *perform_rotation(Node *node);
    void pre_order(Node *node);
    void in_order(Node *node);
    void clear(Node *node);
    Node *natID_search(Node *node, var key);
    void prefix_search(Node *node, var prefix);
    void print_person(Person *p);
    void substring_search(Node *node, var substring);
    void date_range_search(Node *node, Date min, Date max);

public:
    AVL(bool allow_dup = false) : root(nullptr), allow_duplicates(allow_dup){};
    void clear();
    void insert(var key, Person *person);
    void pre_order();
    void in_order();
    void natID_search(var key);
    void prefix_search(var prefix);
    void substring_search(var substring);
    void date_range_search(string date_min, string date_max);
};

template <typename var>
void AVL<var>::clear(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename var>
void AVL<var>::clear()
{
    clear(root);
    root = nullptr;
}

template <typename var>
typename AVL<var>::Node *AVL<var>::rotate_left(Node *node)
{
    Node *right_child = node->right;
    node->right = right_child->left;
    right_child->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    right_child->height = max(height(right_child->left), height(right_child->right)) + 1;
    return right_child;
}

template <typename var>
typename AVL<var>::Node *AVL<var>::rotate_right(Node *node)
{
    Node *left_child = node->left;
    node->left = left_child->right;
    left_child->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    left_child->height = max(height(left_child->left), height(left_child->right)) + 1;
    return left_child;
}

template <typename var>
typename AVL<var>::Node *AVL<var>::rotate_rl(Node *node)
{
    node->right = rotate_right(node->right);
    return rotate_left(node);
}

template <typename var>
typename AVL<var>::Node *AVL<var>::rotate_lr(Node *node)
{
    node->left = rotate_left(node->left);
    return rotate_right(node);
}

template <typename var>
int AVL<var>::height(Node *node)
{
    if (node == nullptr)
        return 0;

    return node->height;
}

template <typename var>
int AVL<var>::balance_factor(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

template <typename var>
typename AVL<var>::Node *AVL<var>::perform_rotation(Node *node)
{
    int bal = balance_factor(node);
    if (bal > 1)
    {
        if (balance_factor(node->left) > 0)
        {
            node = rotate_right(node);
        }
        else
        {
            node = rotate_lr(node);
        }
    }
    else if (bal < -1)
    {
        if (balance_factor(node->right) < 0)
        {
            node = rotate_left(node);
        }
        else
        {
            node = rotate_rl(node);
        }
    }
    return node;
}

template <typename var>
typename AVL<var>::Node *AVL<var>::insert(Node *node, var key, Person *person)
{
    if (node == nullptr)
    {
        node = new Node(key, person);
        return node;
    }
    if (key < node->key)
    {
        node->left = insert(node->left, key, person);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, person);
    }
    else if (allow_duplicates)
    {
        node->left = insert(node->left, key, person);
    }
    else
    {
        return node;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    node = perform_rotation(node);
    return node;
}

template <typename var>
void AVL<var>::insert(var key, Person *person)
{
    root = insert(root, key, person);
}

template <typename var>
void AVL<var>::pre_order(Node *node)
{
    if (node != nullptr)
    {
        cout << node->key << endl;
        pre_order(node->left);
        pre_order(node->right);
    }
}

template <typename var>
void AVL<var>::pre_order()
{
    pre_order(root);
}

template <typename var>
void AVL<var>::in_order(Node *node)
{
    if (node != nullptr)
    {

        in_order(node->left);
        cout << node->key << endl;
        in_order(node->right);
    }
}

template <typename var>
void AVL<var>::in_order()
{
    in_order(root);
}

template <typename var>
typename AVL<var>::Node *AVL<var>::natID_search(Node *node, var key)
{
    if (node == nullptr || node->key == key)
    {
        return node;
    }
    if (node->key < key)
    {
        return natID_search(node->right, key);
    }
    else
    {
        return natID_search(node->left, key);
    }
}

template <typename var>
void AVL<var>::natID_search(var key)
{
    Node *res = natID_search(root, key);
    if (res == nullptr)
    {
        cout << "No National ID results for " << key << endl;
    }
    else
    {
        Person *p = res->person;
        cout << p->name << endl;
        cout << p->natID << endl;
        cout << date_to_str(p->birthday) << endl;
        cout << p->city << endl;
    }
}

template <typename var>
void AVL<var>::prefix_search(var prefix)
{
    prefix_search(root, prefix);
}

template <typename var>
void AVL<var>::prefix_search(Node *node, var prefix)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->key.compare(0, prefix.size(), prefix) == 0)
    {
        print_person(node->person);
    }
    prefix_search(node->left, prefix);
    prefix_search(node->right, prefix);
}

template <typename var>
void AVL<var>::substring_search(var substring)
{
    substring_search(root, substring);
}

template <typename var>
void AVL<var>::substring_search(Node *node, var substring)
{
    if (node == nullptr)
    {
        return;
    }
    if (node->key.find(substring) != string::npos)
    {
        print_person(node->person);
    }
    substring_search(node->left, substring);
    substring_search(node->right, substring);
}

template <typename var>
void AVL<var>::date_range_search(string date_min, string date_max)
{
    date_range_search(root, str_to_date(date_min), str_to_date(date_max));
}

template <typename var>
void AVL<var>::date_range_search(Node *node, Date min, Date max)
{
    bool is_between = 1;
    if (node == nullptr)
    {
        return;
    }
    Person *p = node->person;
    Date target = p->birthday;
    if ((target.year < min.year) ||
        (target.year == min.year && target.month < min.month) ||
        (target.year == min.year && target.month == min.month && target.day < min.day))
    {
        is_between = 0;
    }
    if (is_between && ((target.year > max.year) ||
                       (target.year == max.year && target.month > max.month) ||
                       (target.year == max.year && target.month == max.month && target.day > max.day)))
    {
        is_between = 0;
    }
    if (is_between)
    {
        print_person(p);
    }
    date_range_search(node->left, min, max);
    date_range_search(node->right, min, max);
}

template <typename var>
void AVL<var>::print_person(Person *p)
{
    cout << "----------------------" << endl;
    cout << "NAME: " << p->name << endl;
    cout << "NAT. ID: " << p->natID << endl;
    cout << "BIRTHDAY: " << date_to_str(p->birthday) << endl;
    cout << "CITY OF BIRTH: " << p->city << endl;
    cout << "----------------------" << endl;
}

#endif