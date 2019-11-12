#include "Stack.h"

Status initStack(Stack *stack) { return initList(stack); }

Status destroyStack(Stack *stack) { return destroyList(stack); }

Status clearStack(Stack *stack) { return clearList(stack); }

bool stackEmpty(Stack *stack) { return listEmpty(*stack); }

Status stackPop(Stack *stack)
{
    ElemType temp;
    return listDelete(stack, 1, &temp);
}

Status stackPush(Stack *stack, ElemType e) { return listInsert(stack, 1, e); }

ElemType stackTop(Stack *stack) { return stack->head->data; }
