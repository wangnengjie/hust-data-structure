#pragma once

#include "global.h"

typedef struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
} LinkNode;

typedef struct LinkList
{
    LinkNode *head;
    int length;
    bool initialized;
} LinkList;

/**
 * @description: initialize a list
 * @param {LinkList *} - point to a list
 * @return {Status}
 */
Status initList(LinkList *);

/**
 * @description: destroy a list
 * @param {LinkList *} - point to a list
 * @return {Status}
 */
Status destroyList(LinkList *);

/**
 * @description: reset a list to empty
 * @param {LinkList *} - point to a list
 * @return {Status}
 */
Status clearList(LinkList *);

/**
 * @description: whether a list is empty
 * @param {LinkList} - a list
 * @return {bool}
 */
bool listEmpty(LinkList);

/**
 * @description: a list'length
 * @param {LinkList} - a list
 * @return {int}
 */
int listLength(LinkList);

/**
 * @description: get an element by index
 * @param {LinkList} - a list
 * @param {int} - index
 * @param {ElemType} - element
 * @return {Status}
 */
Status getElem(LinkList, int, ElemType *);

/**
 * @description: find a elem by elem value
 * @param {LinkList} - a list
 * @param {ElemType} - elem
 * @param {(ElemType,ElemType) => bool} - compare func
 * @return {int} - the index of elem
 */
int locateElem(LinkList, ElemType, bool (*compare)(ElemType, ElemType));

/**
 * @description: get element's previous element
 * @param {LinkList} a list
 * @param {ElemType} - current element
 * @param {ElemType *} - pointer to previous element
 * @return {Status}
 */
Status priorElem(LinkList, ElemType, ElemType *);

/**
 * @description: get element's next element
 * @param {LinkList} - list
 * @param {ElemType} - current element
 * @param {ElemType *} - pointer to next element
 * @return {Status}
 */
Status nextElem(LinkList, ElemType, ElemType *);

/**
 * @description: insert an element to a list
 * @param {LinkList *} - pointer to list
 * @param {int} - index of element to be inserted
 * @param {ElemType} - the element to be inserted
 * @return {Status}
 */
Status listInsert(LinkList *, int, ElemType);

/**
 * @description: delete an element from a list by index and return it by param
 * third
 * @param {LinkList *} - pointer to list
 * @param {int} - index of element to be deleted
 * @param {ElemType *} - the element to be deleted
 * @return {Status}
 */
Status listDelete(LinkList *, int, ElemType *);

/**
 * @description: traverse the list
 * @param {LinkList} - list
 * @param {(LinkNode *) => void} - print function
 * @return {Status}
 */
Status listTraverse(LinkList, void (*visit)(LinkNode *));
