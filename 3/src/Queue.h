#pragma once

#include "LinkList.h"
#include "global.h"

typedef LinkList Queue;

/**
 * @description: initialize a Queue
 * @param {Queue *} - point to a Queue
 * @return {Status}
 */
Status initQueue(Queue *);

/**
 * @description: destroy a Queue
 * @param {Queue *} - point to a Queue
 * @return {Status}
 */
Status destroyQueue(Queue *);

/**
 * @description: reset a Queue to empty
 * @param {Queue *} - point to a Queue
 * @return {Status}
 */
Status clearQueue(Queue *);

/**
 * @description:  whether a queue is empty
 * @param {Queue *} - point to a Queue
 * @return {bool}
 */
bool queueEmpty(Queue *);

/**
 * @description: destory the first node
 * @param {Queue *} - point to a Queue
 * @return {Status}
 */
Status queuePop(Queue *);

/**
 * @description: append a node to tail
 * @param {Queue *} - point to a Queue
 * @param {ElemType} - element to push
 * @return {Status}
 */
Status queuePush(Queue *, ElemType);

/**
 * @description: return the first node
 * @param {Queue *} - point to a Queue
 * @return {ElemType} - the first node
 */
ElemType queueFront(Queue *);
