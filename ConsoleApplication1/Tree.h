#pragma once

struct TreeNode
{
public:
    TreeNode(int pVal, TreeNode* pLeft = nullptr, TreeNode* pRigth = nullptr) :
        val(pVal),
        left(pLeft),
        right(pRigth)
    {}

    int val;
    TreeNode *left;
    TreeNode *right;
};

class Tree
{
public:
    Tree();
    ~Tree();

    static TreeNode *createTree();
    static void deleteAll(TreeNode* node);

    static void print_LevelOrderTraversal(TreeNode *head, int lev);
    static int getTreeHeight(TreeNode *head);

    static void main();

private:
    TreeNode *head;
};

