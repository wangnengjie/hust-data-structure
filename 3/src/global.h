#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define OK 1
#define ERRORS -1
#define OVERFLOW -2

#define MAX_KEY_LENGTH 20

typedef struct TElemType
{
    char key[MAX_KEY_LENGTH];
    int value;
} TElemType;

typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *leftChild;
    struct BiTNode *rightChild;
} BiTNode, *ElemType;

/**
 * @description: comparing function
 * @param {ElemType} - elem
 * @param {ElemType} - elem
 * @return {bool}
 */
bool isEqual(ElemType, ElemType);

/**
 * @description: comparing function
 * @param {ElemType} - elem
 * @param {char *} - key
 * @return {bool}
 */
bool isEqualByKey(ElemType, char *);
