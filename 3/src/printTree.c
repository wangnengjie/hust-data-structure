#include "printTree.h"

int calc(BiTNode *node, bool isLeft, int offset, int depth, char **buffer)
{
    char b[20] = "";
    if (!node)
        return 0;

    int value = node->data.value;
    int digits = 1;
    while (value / 10)
    {
        value /= 10;
        digits++;
    }
    int width = 2 + digits;
    width += strlen(node->data.key) + 1;
    // insert to buffer
    sprintf(b, "(%s %d)", node->data.key, node->data.value);

    // width of left child
    int left = calc(node->leftChild, 1, offset, depth + 1, buffer);
    // width of right child
    int right =
        calc(node->rightChild, 0, offset + left + width, depth + 1, buffer);

    // element on root, which is in even row of `buffer`
    for (int i = 0; i < width; i++)
        buffer[2 * depth][offset + left + i] = b[i];

    // connection line
    if (depth)
    { // not root
        buffer[2 * depth - 1][offset + left + width / 2] = '+';
        if (isLeft)
        { // is left child
            for (int i = 1; i < width + right; i++)
                buffer[2 * depth - 1][offset + left + width / 2 + i] = '-';
            // get parent position
            buffer[2 * depth - 1][offset + left + width + right + width / 2] =
                '+';
        }
        else
        { // is right child
            for (int i = 0; i <= left + width - 1; i++)
                buffer[2 * depth - 1][offset - width / 2 + i] = '-';
            // get parent position
            buffer[2 * depth - 1][offset - width / 2 - 1] = '+';
        }
    }

    return left + width + right;
}

Status create(BiTree *T, int height, int width)
{
    // initialize buffer
    char **s = malloc(sizeof(char *) * height);
    for (int i = 0; i < height; i++)
    {
        s[i] = malloc(sizeof(char) * width);
        memset(s[i], ' ', sizeof(char) * width);
        s[i][width - 1] = '\0';
    }

    int finalWidth = calc(T->root, 0, 0, 0, s);
    if (finalWidth > width)
    { // width exceeds
        printf("[WARNING: The width of console CANNOT show the whole tree!]\n");
        return ERRORS;
    }

    for (int i = 0; i < height; i++)
    { // print items from buffer
        printf("%s\n", s[i]);
        free(s[i]); // free buffer item
    }
    free(s); // free buffer
    return OK;
}

Status printTree(BiTree *T)
{
    if (!T->initialized)
        return ERRORS;

    int consoleWidth;
    // get console width

    CONSOLE_SCREEN_BUFFER_INFO buffer_info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
    consoleWidth = buffer_info.srWindow.Right - buffer_info.srWindow.Left + 1;

    int height = 2 * BiTreeDepth(T) - 1;

    putchar('\n');

    Status status = create(T, height, consoleWidth);
    if (status != OK)
        return ERRORS;

    putchar('\n');
    return OK;
}
