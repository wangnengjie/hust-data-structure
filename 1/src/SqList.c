#include "SqList.h"

Status initList(SqList *list)
{
    if (list->elem)
        return ERROR;

    list->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (!list->elem)
        exit(OVERFLOW);
    list->length = 0;
    list->listSize = LIST_INIT_SIZE;
    return OK;
}

Status destroyList(SqList *list)
{
    if (!list->elem)
        return ERROR;

    free(list->elem);
    list->elem = NULL;
    return OK;
}

Status clearList(SqList *list)
{
    if (!list->elem)
        return ERROR;

    list->length = 0;
    return OK;
}

bool listEmpty(SqList list)
{
    if (!list.elem)
        return ERROR;

    return list.length == 0 ? true : false;
}

int listLength(SqList list)
{
    if (!list.elem)
        return ERROR;

    return list.length;
}

Status getElem(SqList list, int i, ElemType *e)
{
    if (!list.elem || i < 1 || i > list.length)
        return ERROR;

    *e = list.elem[i - 1];
    return OK;
}

int locateElem(SqList list, ElemType e, bool (*compare)(ElemType, ElemType))
{
    if (!list.elem)
        return ERROR;

    int i = 1;
    for (; i <= list.length && !compare(e, list.elem[i - 1]); i++)
        ;
    return i > list.length ? 0 : i;
}

bool isEqual(ElemType a, ElemType b)
{
    return a.value == b.value;
}

Status priorElem(SqList list, ElemType curElem, ElemType *preElem)
{
    if (!list.elem)
        return ERROR;

    int position = locateElem(list, curElem, isEqual);
    if (position <= 1)
        return ERROR;
    *preElem = list.elem[position - 2];
    return OK;
}

Status nextElem(SqList list, ElemType curElem, ElemType *next)
{
    if (!list.elem)
        return ERROR;

    int position = locateElem(list, curElem, isEqual);
    if (position == 0 || position == list.length)
        return ERROR;
    *next = list.elem[position];
    return OK;
}

Status listInsert(SqList *list, int i, ElemType e)
{
    if (!list->elem || i < 1 || i > list->length + 1)
        return ERROR;

    if (list->length >= list->listSize)
    {
        ElemType *newPointer = (ElemType *)realloc(list->elem, (list->listSize + LISTINCREMENT) * sizeof(ElemType));
        if (!newPointer)
            exit(OVERFLOW);
        list->elem = newPointer;
        list->listSize += LISTINCREMENT;
    }

    for (int t = list->length; t >= i; t--)
        list->elem[t] = list->elem[t - 1];

    list->elem[i - 1] = e;
    list->length++;
    return OK;
}

Status listDelete(SqList *list, int i, ElemType *e)
{
    if (!list->elem || i < 1 || i > list->length)
        return ERROR;

    *e = list->elem[i - 1];

    for (int t = i; t < list->length; t++)
        list->elem[t - 1] = list->elem[t];

    list->length--;
    return OK;
}

Status listTraverse(SqList list, Status (*visit)(ElemType *))
{
    if (!list.elem)
        return ERROR;

    for (int i = 0; i < list.length; i++)
    {
        if (visit(&list.elem[i]) != OK)
            return ERROR;
    }

    return OK;
}