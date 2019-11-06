#include "Queue.h"

Status initQueue(Queue *queue)
{
    return initList(queue);
}

Status destroyQueue(Queue *queue)
{
    return destroyList(queue);
}

Status clearQueue(Queue *queue)
{
    return clearList(queue);
}

Status popQueue(Queue *queue)
{
    ElemType temp;
    return listDelete(queue, 1, &temp);
}

Status pushQueue(Queue *queue, ElemType e)
{
    return listInsert(queue, listLength(*queue) + 1, e);
}

ElemType *frontQueue(Queue *queue)
{
    return queue->head;
}