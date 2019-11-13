#define _CRT_SECURE_NO_WARNINGS

#include "BiTree.h"
#include "Queue.h"
#include "Stack.h"

Status CreateBiTree(BiTree *T, LinkList *list)
{
    if (T->initialized)
        return ERRORS;
    T->initialized = true;
    T->root = CreateFunc(list);
    return OK;
}

BiTNode *CreateFunc(LinkList *list)
{
    if (listEmpty(*list))
        return NULL;
    BiTNode *node = (BiTNode *)malloc(sizeof(BiTNode));
    if (!list->head->data) // empty node
    {
        listDelete(list, 1, &node);
        return NULL;
    }
    listDelete(list, 1, &node);
    node->leftChild = CreateFunc(list);
    node->rightChild = CreateFunc(list);
    return node;
}

Status DestroyBiTree(BiTree *T)
{
    Status t = ClearBiTree(T);
    if (t != OK)
        return t;
    T->initialized = false;
    return OK;
}

Status ClearBiTree(BiTree *T)
{
    if (!T->initialized)
        return ERRORS;
    PostOrderTraverse(T->root, (void (*)(BiTNode *))free);
    T->root = NULL;
    return OK;
}

bool BiTreeEmpty(BiTree *T)
{
    if (!T->initialized)
        return ERRORS;
    return T->root == NULL ? true : false;
}

int BiTreeDepth(BiTree *T)
{
    if (!T->initialized)
        return ERRORS;
    return GetDepthFunc(T->root);
}

int GetDepthFunc(BiTNode *root)
{
    if (!root)
        return 0;
    int m = GetDepthFunc(root->leftChild);
    int n = GetDepthFunc(root->rightChild);
    return (m > n ? m : n) + 1;
}

BiTNode *LocateNode(BiTree *T, char *key)
{
    if (!T->initialized)
        return NULL;
    return LocateNodeFunc(T->root, key);
}

BiTNode *LocateNodeFunc(BiTNode *root, char *key)
{
    if (!root)
        return NULL;
    BiTNode *node = NULL;
    if (isEqualByKey(root, key))
        node = root;
    else
    {
        node = LocateNodeFunc(root->leftChild, key);
        if (!node)
            node = LocateNodeFunc(root->rightChild, key);
    }
    return node;
}

Status Assign(BiTree *T, char *key, int value)
{
    if (!T->initialized)
        return ERRORS;
    BiTNode *t = LocateNodeFunc(T->root, key);
    if (!t)
        return ERRORS;
    t->data.value = value;
    return OK;
}

BiTNode *GetSibling(BiTree *T, char *key)
{
    if (!T->initialized)
        return NULL;
    BiTNode *parent = GetParentFunc(T->root, key);
    if (!parent)
        return NULL;
    if (isEqualByKey(parent->leftChild, key))
        return parent->rightChild;
    else
        return parent->leftChild;
}

BiTNode *GetParentFunc(BiTNode *root, char *key)
{
    if (root == NULL || isEqualByKey(root->leftChild, key) ||
        isEqualByKey(root->rightChild, key))
    {
        return root;
    }
    BiTNode *parent = GetParentFunc(root->leftChild, key);
    if (!parent)
        parent = GetParentFunc(root->rightChild, key);
    return parent;
}

Status InsertNode(BiTree *T, char *key, enum LR L_R, BiTNode *node)
{
    if (!T->initialized)
        return ERRORS;
    if (LocateNodeFunc(T->root, node->data.key) != NULL)
        return ERRORS;

    BiTNode *subroot = LocateNodeFunc(T->root, key);
    if (!subroot)
        return ERRORS;
    BiTNode *temp = NULL;
    if (L_R == LEFT)
    {
        temp = subroot->leftChild;
        subroot->leftChild = node;
        node->rightChild = temp;
    }
    else if (L_R == RIGHT)
    {
        temp = subroot->rightChild;
        subroot->rightChild = node;
        node->rightChild = temp;
    }
    else
        return ERRORS;
    return OK;
}

Status DeleteNode(BiTree *T, char *key)
{
    if (!T->initialized)
        return ERRORS;
    BiTNode *toDelete = NULL;
    // root node to delete
    if (isEqualByKey(T->root, key))
    {
        toDelete = T->root;
        T->root = toDelete->leftChild;
        BiTNode *p = T->root;
        for (; p->rightChild; p = p->rightChild)
            ;
        p->rightChild = toDelete->rightChild;
        free(toDelete);
        return OK;
    }
    // other node
    BiTNode *parent = GetParentFunc(T->root, key);
    if (!parent)
        return ERRORS;

    if (isEqualByKey(parent->leftChild, key))
    {
        toDelete = parent->leftChild;
        if (!toDelete->leftChild) // left empty
            parent->leftChild = toDelete->rightChild;
        else if (!toDelete->rightChild) // right empty
            parent->leftChild = toDelete->leftChild;
        else // both has subtree
        {
            BiTNode *p = toDelete->leftChild;
            for (; p->rightChild; p = p->rightChild)
                ;
            p->rightChild = toDelete->rightChild;
            parent->leftChild = toDelete->leftChild;
        }
    }
    else
    {
        toDelete = parent->rightChild;
        if (!toDelete->leftChild)
            parent->rightChild = toDelete->rightChild;
        else if (!toDelete->rightChild)
            parent->rightChild = toDelete->leftChild;
        else
        {
            BiTNode *p = toDelete->leftChild;
            for (; p->rightChild; p = p->rightChild)
                ;
            p->rightChild = toDelete->rightChild;
            parent->rightChild = toDelete->leftChild;
        }
    }
    free(toDelete);
    return OK;
}

Status TraverseTree(BiTree *T, enum TraverseType type, void (*visit)(BiTNode *))
{
    if (!T->initialized)
        return ERRORS;
    switch (type)
    {
    case PRE_ORDER:
        PreOrderTraverse(T->root, visit);
        break;
    case IN_ORDER:
        InOrderTraverse(T->root, visit);
        break;
    case POST_ORDER:
        PostOrderTraverse(T->root, visit);
        break;
    case LEVEL_ORDER:
        LevelOrderTraverse(T->root, visit);
        break;
    default:
        return ERRORS;
        break;
    }
    return OK;
}

void PreOrderTraverse(BiTNode *root, void (*visit)(BiTNode *))
{
    BiTNode *p = root;
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->initialized = false;
    initStack(s);

    while (p || !stackEmpty(s))
    {
        while (p)
        {
            visit(p);
            stackPush(s, p);
            p = p->leftChild;
        }
        visit(p); // visit empty node
        if (!stackEmpty(s))
        {
            p = stackTop(s);
            stackPop(s);
            p = p->rightChild;
        }
    }
    destroyStack(s);
    free(s);
}

void InOrderTraverse(BiTNode *root, void (*visit)(BiTNode *))
{
    if (root)
    {
        InOrderTraverse(root->leftChild, visit);
        visit(root);
        InOrderTraverse(root->rightChild, visit);
    }
}

void PostOrderTraverse(BiTNode *root, void (*visit)(BiTNode *))
{
    if (root)
    {
        PostOrderTraverse(root->leftChild, visit);
        PostOrderTraverse(root->rightChild, visit);
        visit(root);
    }
}

void LevelOrderTraverse(BiTNode *root, void (*visit)(BiTNode *))
{
    if (!root)
        return;
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->initialized = false;
    initQueue(q);
    queuePush(q, root);
    while (!queueEmpty(q))
    {
        BiTNode *cur = queueFront(q);
        queuePop(q);
        visit(cur);
        if (cur->leftChild)
            queuePush(q, cur->leftChild);
        if (cur->rightChild)
            queuePush(q, cur->rightChild);
    }
}
