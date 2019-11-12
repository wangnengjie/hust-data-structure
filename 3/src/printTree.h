#include "BiTree.h"
#include <Windows.h>

Status printTree(BiTree *T);

Status create(BiTree *T, int height, int width);

int calc(BiTNode *node, bool isLeft, int offset, int depth, char **buffer);
