#include "Stack.h"

Status initStack(Stack *stack) { return initList(stack); }

Status destroyStack(Stack *stack) { return destroyList(stack); }

Status clearStack(Stack *stack) { return clearList(stack); }

Status popStack(Stack *stack)
{
    ElemType temp;
    return listDelete(stack, 1, &temp);
}

Status pushStack(Stack *stack, ElemType e) { return listInsert(stack, 1, e); }

ElemType *topStack(Stack *stack) { return &stack->head->data; }