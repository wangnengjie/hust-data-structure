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

/**
 * @description: save a tree to file
 * @param {BiTree *} - point to a tree to save
 * @return {void}
 */
void saveToFile(BiTree *);

/**
 * @description: help to save a tree
 * @param {BiTNode *} - traverse tree
 * @return {void}
 */
void saveFunc(BiTNode *);

/**
 * @description: load a tree from file
 * @param {BiTree *} - point to a tree to load
 * @return {void}
 */
void loadFromFile(BiTree *);

int main(void)
{
    system("mode con cols=150 lines=40");
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
                RS == OVERFLOW &&printf("[OVERFLOW]: out of memory\n");
                RS == ERRORS &&printf(
                          "[Error]: tree has exist or input is invalid\n");
                clearBuf();
                break;
            }
            case 2:
            {
                printf("Destroy Tree %d\n", treeIndex);
                Status st = DestroyBiTree(curTree);
                st == OK &&printf("[Info]: Success destroy Tree %d\n",
                                  treeIndex + 1);
                st == ERRORS &&printf(
                          "[Error]: tree has not existed or other ERRORS\n");
                break;
            }
            case 3:
            {
                printf("Clear Tree %d\n", treeIndex);
                Status st = ClearBiTree(curTree);
                st == OK &&printf("[Info]: Success clear Tree %d\n",
                                  treeIndex + 1);
                st == ERRORS &&printf(
                          "[Error]: tree has not existed or other ERRORS\n");
                break;
            }
            case 4:
            {
                int b = BiTreeEmpty(curTree);
                if (b == ERRORS)
                    printf("[Error]: Tree %d does not exist\n", treeIndex + 1);
                else
                    printf("[Info]: Tree %d is %sempty\n", treeIndex + 1,
                           BiTreeEmpty(curTree) == true ? "" : "not ");
                break;
            }
            case 5:
            {
                int d = BiTreeDepth(curTree);
                if (d == ERRORS)
                    printf("[Error]: Tree %d does not exist\n", treeIndex + 1);
                else
                    printf("[Info]: Depth of tree %d is %d\n", treeIndex + 1,
                           d);
                break;
            }
            case 6:
            {
                printf("Please enter the key of the node: ");
                char key[MAX_KEY_LENGTH];
                scanf("%s", key);
                BiTNode *node = LocateNode(curTree, key);
                if (node)
                    printf("key: %s\tvalue: %d\n", node->data.key,
                           node->data.value);
                else
                    printf("[Error]: Node does not exist or you should "
                           "initialize the tree\n");
                clearBuf();
                break;
            }
            case 7:
            {
                printf("Please enter the key of the node: ");
                char key[MAX_KEY_LENGTH];
                scanf("%s", key);
                printf("Please enter the value to assign: ");
                int value;
                scanf("%d", &value);
                Status st = Assign(curTree, key, value);
                if (st == OK)
                    printf("[Info]: Success\n");
                else
                    printf("[Error]: Node does not exist or you should "
                           "initialize the tree\n");
                clearBuf();
                break;
            }
            case 8:
            {
                printf("Please enter the key of the node: ");
                char key[MAX_KEY_LENGTH];
                scanf("%s", key);
                BiTNode *node = GetSibling(curTree, key);
                if (node)
                    printf("key: %s\tvalue: %d\n", node->data.key,
                           node->data.value);
                else
                    printf("[Error]: Node does not exist or you should "
                           "initialize the tree\n");
                clearBuf();
                break;
            }
            case 9:
            {
                printf("Please enter the key of the node you what to insert: ");
                char key[MAX_KEY_LENGTH];
                scanf("%s", key);
                clearBuf();
                printf("Please enter key and value of new node (key value): ");
                BiTNode *newNode = (BiTNode *)malloc(sizeof(BiTNode));
                scanf("(%s %d)", newNode->data.key, &newNode->data.value);
                clearBuf();
                printf("Please enter left or right child you want to insert "
                       "(0:left 1:right): ");
                enum LR L_R;
                scanf("%d", &L_R);
                if (L_R != 0 && L_R != 1)
                {
                    printf("[Error]: input error\n");
                    break;
                }

                Status st = InsertNode(curTree, key, L_R, newNode);
                if (st == OK)
                    printf("[Info]: Success\n");
                else
                    printf("[Error]: Node does not exist or you should "
                           "initialize the tree\n");
                clearBuf();
                break;
            }
            case 10:
            {
                printf("Please enter the key of the node: ");
                char key[MAX_KEY_LENGTH];
                scanf("%s", key);
                Status st = DeleteNode(curTree, key);
                if (st == OK)
                    printf("[Info]: Success");
                else
                    printf("[Error]: Node does not exist or you should "
                           "initialize the tree\n");
                clearBuf();
                break;
            }
            case 11:
            case 12:
            case 13:
            case 14:
            {

                printTree(curTree);
                printf("Traverse Tree %d: \n", treeIndex + 1);
                Status st = TraverseTree(curTree, option - 11, printValue);
                st ==
                    ERRORS &&printf(
                        "[Error]: Tree has not exist. Please initialize it.\n");
                break;
            }
            case 15:
            {
                printf("Print Tree %d: \n", treeIndex + 1);
                Status st = printTree(curTree);
                st == ERRORS &&printf("[Error]: Please initialize tree\n");
                break;
            }
            case 16:
            {
                printf("Please enter the index of tree to switch: ");
                int index;
                scanf("%d", &index);
                if (index < 1 || index > MAX_TREE_TABLE_SIZE)
                    printf("[Error]: Range error\n");
                else
                {
                    treeIndex = index - 1;
                    curTree = TreeTable + treeIndex;
                    printf("[Info]: Success\n");
                }
                clearBuf();
                break;
            }
            case 17:
            {
                printf("Save tree %d to file\n", treeIndex + 1);
                saveToFile(curTree);
                break;
            }
            case 18:
            {
                printf("load tree from file to tree %d\n", treeIndex + 1);
                loadFromFile(curTree);
                break;
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
           "     |   15. printTree          16. switchTree          | \n"
           "     |   17. saveToFile         18. loadFromFile        | \n"
           "    ------------------------------------------------------\n\n");
}

void clearBuf()
{
    while (getchar() != '\n')
        ;
}

void printValue(BiTNode *node)
{
    if (node)
        printf("(%s %d)", node->data.key, node->data.value);
}

Status createHelper(BiTree *T)
{
    if (T->initialized)
        return ERRORS;

    // printf("Please enter the number of nodes (include empty node): ");
    // int length;
    // if (!scanf("%d", &length))
    //     return ERRORS;
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
        //     return ERRORS;

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

void saveFunc(BiTNode *node)
{
    FILE *fp = fopen("./tree.txt", "a");
    if (node)
        fprintf(fp, "(%s %d)", node->data.key, node->data.value);
    else
        fprintf(fp, "(# 0)");
    fclose(fp);
}

void saveToFile(BiTree *T)
{
    if (!T->initialized)
    {
        printf("[Error]: tree has not been initialized\n");
        return;
    }
    FILE *fp = fopen("./tree.txt", "w+");
    fclose(fp);
    PreOrderTraverse(T->root, saveFunc);
    printf("[Info]: Success");
}

void loadFromFile(BiTree *T)
{
    if (T->initialized)
    {
        printf("[Error]: tree has been initialized before\n");
        return;
    }
    FILE *fp = fopen("tree.txt", "r");
    if (fp == NULL)
    {
        printf("[Error]: File doesn't exist!\n");
        return;
    }

    TElemType elem;
    LinkList *list = (LinkList *)malloc(sizeof(LinkList));
    list->initialized = false;
    initList(list);

    while (fscanf(fp, "(%s %d)", elem.key, &elem.value) == 2)
    {
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

    if (CreateBiTree(T, list) == ERRORS)
    {
        printf("[Error]: Something went wrong\n");
        return;
    }
    printf("[Info]: Success\n");
}
