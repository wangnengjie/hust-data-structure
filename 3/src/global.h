#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Status;
#define OK 1
#define ERROR -1
#define OVERFLOW -2

#define MAX_KEY_LENGTH 20

typedef struct ElemType
{
    char key[MAX_KEY_LENGTH];
    int value;
} ElemType;

/**
 * @description: comparing function
 * @param {ElemType} - elem
 * @param {ElemType} - elem
 * @return {bool}
 */
bool isEqual(ElemType, ElemType);
