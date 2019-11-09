#include "LinkList.h"

Status listTraverse(LinkList list, void (*visit)(LinkNode *))
{
    if (!list.initialized)
        return ERROR;
    LinkNode *p = list.head;
    while (p)
    {
        LinkNode *next = p->next;
        visit(p);
        p = next;
    }
    return OK;
}

Status initList(LinkList *list)
{
    if (list->initialized)
        return ERROR;
    list->head = NULL;
    list->length = 0;
    list->initialized = true;
    return OK;
}

Status destroyList(LinkList *list)
{
    if (!list->initialized)
        return ERROR;
    listTraverse(*list, free);
    list->length = 0;
    list->initialized = false;
    list->head = NULL;
    return OK;
}

Status clearList(LinkList *list)
{
    if (!list->initialized)
        return ERROR;
    listTraverse(*list, free);
    list->length = 0;
    list->head = NULL;
    return OK;
}

bool listEmpty(LinkList list)
{
    if (!list.initialized)
        return ERROR;
    return list.length == 0;
}

int listLength(LinkList list)
{
    if (!list.initialized)
        return ERROR;
    return list.length;
}

Status getElem(LinkList list, int i, ElemType *e)
{
    if (!list.initialized || i < 1 || i > list.length)
        return ERROR;
    LinkNode *p = list.head;
    for (int j = 1; j < i; j++)
        p = p->next;
    *e = p->data;
    return OK;
}

int locateElem(LinkList list, ElemType e, bool (*compare)(ElemType, ElemType))
{
    if (!list.initialized)
        return ERROR;
    LinkNode *p = list.head;
    int i = 1;
    for (; p && !compare(p->data, e); i++, p = p->next)
        ;
    return i > listLength(list) ? 0 : i;
}

Status priorElem(LinkList list, ElemType cur, ElemType *pre)
{
    if (!list.initialized)
        return ERROR;
    LinkNode *p1 = list.head;
    LinkNode *p2 = p1->next;
    if (!p1 || !p2 || isEqual(cur, p1->data))
        return ERROR;
    for (; p2; p1 = p1->next, p2 = p2->next)
    {
        if (isEqual(p2->data, cur))
        {
            *pre = p1->data;
            return OK;
        }
    }
    return ERROR;
}

Status nextElem(LinkList list, ElemType cur, ElemType *next)
{
    if (!list.initialized)
        return ERROR;
    for (LinkNode *p1 = list.head; p1; p1 = p1->next)
    {
        if (isEqual(p1->data, cur))
        {
            LinkNode *n = p1->next;
            if (n)
            {
                *next = n->data;
                return OK;
            }
        }
    }
    return ERROR;
}

Status listInsert(LinkList *list, int i, ElemType value)
{
    if (!list->initialized || i < 1 || i > list->length + 1)
        return ERROR;
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode));
    if (!newNode)
        return OVERFLOW;
    newNode->data = value;
    newNode->next = NULL;
    if (i == 1)
    {
        newNode->next = list->head;
        list->head = newNode;
    }
    else
    {
        LinkNode *p = list->head;
        for (int j = 1; j < i - 1; j++, p = p->next)
            ;
        newNode->next = p->next;
        p->next = newNode;
    }
    list->length++;
    return OK;
}

Status listDelete(LinkList *list, int i, ElemType *e)
{
    if (!list->initialized || i < 1 || i > list->length)
        return ERROR;
    LinkNode *p = list->head;
    LinkNode *deleteNode = NULL;
    if (i == 1)
    {
        list->head = p->next;
        deleteNode = p;
    }
    else
    {
        for (int j = 1; j < i - 1; j++, p = p->next)
            ;
        deleteNode = p->next;
        p->next = deleteNode->next;
    }
    *e = deleteNode->data;
    free(deleteNode);
    list->length--;
    return OK;
}
