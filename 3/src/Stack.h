#pragma once

#include "CommonType.h"
#include "LinkList.h"

typedef LinkList Stack;

/**
 * @description: initialize a Stack
 * @param {Stack *} - point to a Stack
 * @return {Status}
 */
Status initStack(Stack *);

/**
 * @description: destroy a Stack
 * @param {Stack *} - point to a Stack
 * @return {Status}
 */
Status destroyStack(Stack *);

/**
 * @description: reset a Stack to empty
 * @param {Stack *} - point to a Stack
 * @return {Status}
 */
Status clearStack(Stack *);

/**
 * @description: destory the first node
 * @param {Stack *} - point to a Stack
 * @return {Status}
 */
Status popStack(Stack *);

/**
 * @description: append a node to tail
 * @param {Stack *} - point to a Stack
 * @param {ElemType} - element to push
 * @return {Status}
 */
Status pushStack(Stack *, ElemType);

/**
 * @description: return the first node
 * @param {Stack *} - point to a Stack
 * @return {ElemType *} - the first node
 */
ElemType *frontStack(Stack *);