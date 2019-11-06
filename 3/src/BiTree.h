#pragma once

#include "CommonType.h"

typedef struct TreeNode
{
    ElemType data;
    TreeNode *leftChild;
    TreeNode *rightChild;
} TreeNode;

typedef struct BiTree
{
    TreeNode *root;
} BiTree;

