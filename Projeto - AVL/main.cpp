#include <iostream>
#include "avl.h"

int main()
{
    AVLTree<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    std::cout << "In-order traversal: ";
    tree.inOrderTraversal();
    std::cout << std::endl;

    std::cout << "Pre-order traversal: ";
    tree.preOrderTraversal();
    std::cout << std::endl;

    return 0;
}