#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR -1
#define OVERFLOW -2
typedef int Status;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef struct
{
    int value;
} ElemType;

typedef struct
{
    ElemType *elem;
    int length;
    int listSize;
} SqList;

/**
 * @description: initialize a list
 * @param {SqList *} - point to a list
 * @return {Status}
 */
Status initList(SqList *);

/**
 * @description: destroy a list
 * @param {SqList *} - point to a list
 * @return {Status}
 */
Status destroyList(SqList *);

/**
 * @description: reset a list to empty
 * @param {Sqlist *} - point to a list
 * @return {Status}
 */
Status clearList(SqList *);

/**
 * @description: whether a list is empty
 * @param {SqList} - a list 
 * @return {bool}
 */
bool listEmpty(SqList);

/**
 * @description: a list'length
 * @param {SqList} - a list 
 * @return {int}
 */
int listLength(SqList);

/**
 * @description: get an element by index
 * @param {SqList} - a list
 * @param {int} - index
 * @param {ElemType} - element
 * @return {Status}
 */
Status getElem(SqList, int, ElemType *);

/**
 * @description: find a elem by elem value
 * @param {SqList} - a list
 * @param {ElemType} - elem
 * @param {(ElemType,ElemType) => bool} - compare func
 * @return {int} - the index of elem
 */
int locateElem(SqList, ElemType, bool (*compare)(ElemType, ElemType));

/**
 * @description: comparing function
 * @param {ElemType} - elem
 * @param {ElemType} - elem
 * @return {bool}
 */
bool isEqual(ElemType, ElemType);

/**
 * @description: get element's previous element
 * @param {SqList} a list
 * @param {ElemType} - current element
 * @param {ElemType *} - pointer to previous element
 * @return {Status}
 */
Status priorElem(SqList, ElemType, ElemType *);

/**
 * @description: get element's next element
 * @param {SqList} - list
 * @param {ElemType} - current element
 * @param {ElemType *} - pointer to next element
 * @return {Status}
 */
Status nextElem(SqList, ElemType, ElemType *);

/**
 * @description: insert an element to a list
 * @param {SqList *} - pointer to list
 * @param {int} - index of element to be inserted
 * @param {ElemType} - the element to be inserted
 * @return {Status}
 */
Status listInsert(SqList *, int, ElemType);

/**
 * @description: delete an element from a list by index and return it by param third
 * @param {SqList *} - pointer to list
 * @param {int} - index of element to be deleted
 * @param {ElemType *} - the element to be deleted
 * @return {Status}
 */
Status listDelete(SqList *list, int i, ElemType *e);

/**
 * @description: traverse the list
 * @param {SqList} - list
 * @param {(ElemType) => Status} - print function
 * @return {Status}
 */
Status listTraverse(SqList, Status (*visit)(ElemType *));
