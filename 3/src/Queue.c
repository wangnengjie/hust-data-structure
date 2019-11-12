#include "Queue.h"

Status initQueue(Queue *queue) { return initList(queue); }

Status destroyQueue(Queue *queue) { return destroyList(queue); }

Status clearQueue(Queue *queue) { return clearList(queue); }

bool queueEmpty(Queue *queue) { return listEmpty(*queue); }

Status queuePop(Queue *queue)
{
    ElemType temp = NULL;
    return listDelete(queue, 1, &temp);
}

Status queuePush(Queue *queue, ElemType e)
{
    return listInsert(queue, listLength(*queue) + 1, e);
}

ElemType queueFront(Queue *queue) { return queue->head->data; }
