#include "global.h"

bool isEqual(ElemType e1, ElemType e2)
{
    if (!e1 || !e2)
        return false;
    return strcmp(e1->data.key, e2->data.key) == 0;
}

bool isEqualByKey(ElemType e, char *key)
{
    if (!e || !key)
        return false;
    return strcmp(e->data.key, key) == 0;
}
