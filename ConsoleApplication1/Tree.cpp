#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

#include "Tree.h"

static const char FILENAME[] = "Tree => ";

Tree::Tree() :
    head(nullptr)
{
}


Tree::~Tree()
{
    if (head != nullptr)
        Tree::deleteAll(head);
}


TreeNode *Tree::createTree()
{
    return 
    new TreeNode(1,
        new TreeNode(2,
            new TreeNode(4,
                nullptr,
                new TreeNode(8)
            ),
            new TreeNode(5)
        ),
        new TreeNode(3,
            new TreeNode(6),
            new TreeNode(7)
        )
    );
}


void Tree::deleteAll(TreeNode* node)
{
    if (node == nullptr)
        return;
    deleteAll(node->left);
    deleteAll(node->right);

    std::cout << "Delete val" << node->val << std::endl;

    delete node;
}


void Tree::print_LevelOrderTraversal(TreeNode *head, int level)
{
    if (head == nullptr)
        return;
    print_LevelOrderTraversal(head->left, level + 1);

    print_LevelOrderTraversal(head->right, level + 1);
}

int Tree::getTreeHeight(TreeNode *head)
{
    if (head == nullptr)
        return 0;
    int leftH = getTreeHeight(head->left) + 1;
    int rightH = getTreeHeight(head->right) + 1;

    return leftH < rightH ? rightH : leftH;
}

void Tree::main()
{
    /*** BEGIN OF FILE ***/
    std::cout << "\n------ BOF " << FILENAME << " ----\n";

    Tree *tree = new Tree();

    tree->head = Tree::createTree();


    std::cout << "Tree height:" << getTreeHeight(tree->head) << std::endl;

    delete tree;
    /*** END OF FILE ***/
    std::cout << std::endl << "------ EOF " << FILENAME << " ----" << std::endl << std::endl;
}