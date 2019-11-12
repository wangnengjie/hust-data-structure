#define _CRT_SECURE_NO_WARNINGS

#include "src/BiTree.h"
#include "src/printTree.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_TABLE_SIZE 20

/**
 * @description: print the menu
 * @param {void}
 * @return {void}
 */
void printMenu();

/**
 * @description: print the tree
 * @param {BiTNode *}
 * @return {void}
 */
void printValue(BiTNode *);

/**
 * @description: clear the buffer
 * @param {void}
 * @return {void}
 */
void clearBuf();

/**
 * @description: help to create a tree
 * @param {void}
 * @return {Status}
 */
Status createHelper(BiTree *);

int main(void)
{
    system("mode con cols=100 lines=40");
    BiTree *TreeTable = (BiTree *)malloc(MAX_TREE_TABLE_SIZE * sizeof(BiTree));
    for (int i = 0; i < MAX_TREE_TABLE_SIZE; i++)
    {
        TreeTable[i].root = NULL;
        TreeTable[i].initialized = false;
    }
    int treeIndex = 0, previousIndex = 0;
    BiTree *curTree = TreeTable + treeIndex;
    int option;
    do
    {
        printMenu();
        if (!scanf("%d", &option))
        {
            printf("[Error]: invalid option.");
            clearBuf();
        }
        else
        {
            if (option)
                clearBuf();
            switch (option)
            {
            case 0:
                break;
            case 1:
            {
                Status RS;
                printf("To create binary tree %d.\n", treeIndex + 1);
                RS = createHelper(curTree);
                RS == OK &&printf("[Info]: Successfully create\n");
                RS == OVERFLOW &&printf("[OVERFLOW]: out of memory");
                RS == ERROR &&printf(
                          "[ERROR]: tree has exist or input is invalid\n");
                clearBuf();
                break;
            }
            case 2:
            {
                printf("Destroy Tree %d\n", treeIndex);
                Status st = DestroyBiTree(curTree);
                st == OK &&printf("[Info]: Success destroy Tree %d\n",
                                  treeIndex + 1);
                st == ERROR &&printf(
                          "[ERROR]: tree has not existed or other error\n");
                break;
            }
            case 3:
            {
                printf("Clear Tree %d\n", treeIndex);
                Status st = ClearBiTree(curTree);
                st == OK &&printf("[Info]: Success clear Tree %d\n",
                                  treeIndex + 1);
                st == ERROR &&printf(
                          "[ERROR]: tree has not existed or other error\n");
                break;
            }
            case 11:
            case 12:
            case 13:
            case 14:
            {
                printf("Traverse Tree %d: \n", treeIndex + 1);
                Status st = TraverseTree(curTree, option - 11, printValue);
                st ==
                    ERROR &&printf(
                        "[Error]: Tree has not exist. Please initialize it.\n");
                break;
            }
            case 15:
            {
                Status st = printTree(curTree);
                st == ERROR &&printf("[Error]: Please initialize tree\n");
            }
            default:
                break;
            }
        }
        clearBuf();
        system("cls");
    } while (option);
    return 0;
}

void printMenu()
{
    printf("                    Menu of BiTree's options              \n"
           "    ------------------------------------------------------\n"
           "     |                      0. exit                     | \n"
           "     |                                                  | \n"
           "     |   1. CreateBiTree        2. DestroyBiTree        | \n"
           "     |   3. ClearBiTree         4. BiTreeEmpty          | \n"
           "     |   5. BiTreeDepth         6. LocateNode           | \n"
           "     |   7. Assign              8. GetSibling           | \n"
           "     |   9. InsertNode          10. DeleteNode          | \n"
           "     |   11. PreOrderTraverse   12. InOrderTraverse     | \n"
           "     |   13. PostOrderTraverse  14. LevelOrderTraverse  | \n"
           "     |   15. printTree                                  | \n"
           "     |                                                  | \n"
           "    ------------------------------------------------------\n\n");
}

void clearBuf()
{
    while (getchar() != '\n')
        ;
}

void printValue(BiTNode *node)
{
    printf("(%s,%d) ", node->data.key, node->data.value);
}

Status createHelper(BiTree *T)
{
    if (T->initialized)
        return ERROR;

    // printf("Please enter the number of nodes (include empty node): ");
    // int length;
    // if (!scanf("%d", &length))
    //     return ERROR;
    // clearBuf();
    printf("Please enter a list of tree node by preorder.\n"
           "(key value) like (first 666)(wnj 111)(# 0): \n");

    TElemType elem;
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->initialized = false;
    initList(list);

    while (scanf("(%s %d)", elem.key, &elem.value) == 2)
    {
        // if (scanf("(%s %d)", elem.key, &elem.value) != 2)
        //     return ERROR;

        BiTNode *newNode = NULL;
        if (strcmp("#", elem.key) != 0 && strcmp("NULL", elem.key) != 0)
        {
            newNode = (BiTNode *)malloc(sizeof(BiTNode));
            newNode->data = elem;
            newNode->leftChild = NULL;
            newNode->rightChild = NULL;
        }
        listInsert(list, listLength(*list) + 1, newNode);
    }

    CreateBiTree(T, list);
    destroyList(list);
    free(list);
    return OK;
}
