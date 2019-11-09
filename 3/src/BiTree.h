#pragma once

#include "global.h"

typedef struct BiTNode
{
    ElemType data;
    BiTNode *leftChild;
    BiTNode *rightChild;
} BiTNode, *BiTree;
