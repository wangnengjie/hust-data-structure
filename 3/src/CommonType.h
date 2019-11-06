#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef int Status;
#define OK 1
#define ERROR -1
#define OVERFLOW -2

#define MAX_KEY_LENGTH 20

#define PRE_ORDER 1
#define IN_ORDER 2
#define POST_ORDER 3
#define LEVEL_ORDER 4

typedef struct ElemType
{
    char key[MAX_KEY_LENGTH];
    int value;
} ElemType;