#pragma once

#include "LinkList.h"
#include "global.h"

typedef struct BiTNode
{
    ElemType data;
    BiTNode *leftChild;
    BiTNode *rightChild;
} BiTNode;

typedef struct BiTree
{
    BiTNode *root;
} BiTree;

enum TraverseType
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER
};

enum LR
{
    LEFT,
    RIGHT
};

/**
 * @description: create a binary tree by preorder
 * @param {BiTree *} - Tree
 * @param {LinkList *} - a list contains tree node by preorder
 * @return {Status}
 */
Status CreateBiTree(BiTree *, LinkList *);

/**
 * @description: destroy a binary tree
 * @param {BiTree *} - Tree
 * @return {Status}
 */
Status DestroyBiTree(BiTree *);

/**
 * @description: clear a binary tree
 * @param {BiTree *} - Tree
 * @return {Status}
 */
Status ClearBiTree(BiTree *);

/**
 * @description: whether tree is empty
 * @param {BiTree *} - Tree
 * @return {bool} - empty or not
 */
bool BiTreeEmpty(BiTree *);

/**
 * @description: the depth of input tree or subtree
 * @param {BiTree *} - Tree
 * @return {int} - depth
 */
int BiTreeDepth(BiTree *);

/**
 * @description: locate tree node
 * @param {BiTree *} - Tree
 * @param {char *} - key of node
 * @return {BiTNode *} - point to node that has the same key | NULL
 */
BiTNode *LocateNode(BiTree *, char *);

/**
 * @description: assign by key
 * @param {BiTree *} - Tree
 * @param {char *} - key
 * @param {int} - value
 * @return {Status}
 */
Status Assign(BiTree *, char *, int);

/**
 * @description: get brother node
 * @param {BiTree *} - Tree
 * @param {char *} - key
 * @return {BiTNode *} - NULL | point to brother node
 */
BiTNode *GetSibling(BiTree *, char *);

/**
 * @description: insert a node
 * @param {BiTree *} - Tree
 * @param {char *} - key
 * @param {LR} - enum type leftChild or rightChild
 * @param {BiTNode *} - node to insert
 * @return {Status}
 */
Status InsertNode(BiTree *, char *, LR, BiTNode *);

/**
 * @description: delete node by key
 * @param {BiTree *} - Tree
 * @param {char *} - key
 * @return {Status}
 */
Status DeleteNode(BiTree *, char *);

/**
 * @description: traverse entry
 * @param {BiTree *} - Tree
 * @param {TraverseType} - type to traverse
 * @param {(BiTNode *) => void} - visit func
 * @return {Status}
 */
Status TraverseTree(BiTree *, TraverseType, void (*visit)(BiTNode *));

/**
 * @description: preorder traverse tree
 * @param {BiTNode *} - root or subtree root
 * @param {(BiTNode *) => void} - visit func
 * @return {void}
 */
void PreOrderTraverse(BiTNode *, void (*visit)(BiTNode *));

/**
 * @description: inorder traverse tree
 * @param {BiTNode *} - root or subtree root
 * @param {(BiTNode *) => void} - visit func
 * @return {void}
 */
void InOrderTraverse(BiTNode *, void (*visit)(BiTNode *));

/**
 * @description: postorder traverse tree
 * @param {BiTNode *} - root or subtree root
 * @param {(BiTNode *) => void} - visit func
 * @return {void}
 */
void PostOrderTraverse(BiTNode *, void (*visit)(BiTNode *));

/**
 * @description: levelorder traverse tree
 * @param {BiTNode *} - root or subtree root
 * @param {(BiTNode *) => void} - visit func
 * @return {void}
 */
void LevelOrderTraverse(BiTNode *, void (*visit)(BiTNode *));
