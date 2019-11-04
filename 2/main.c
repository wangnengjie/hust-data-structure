#define LIST_TABLE_SIZE 10

#include <stdio.h>
#include "src/LinkList.h"

/**
 * @description: print the menu
 * @param {void}
 * @return {void}
 */
void printMenu();

/**
 * @description: clear the buffer
 * @param {void}
 * @return {void}
 */
void clearBuf();

/**
 * @description: print the element
 * @param {LinkNode *} - node
 * @return {void}
 */
void printElement(LinkNode *);

/**
 * @description: Save data to file
 * @param {LinkList *} - list
 * @return {Status}
 */
Status saveToFile(LinkList *);

/**
 * @description: Load data from file
 * @param {LinkList *} - list to load
 * @return {Status}
 */
Status loadFromFile(LinkList *);

int main(void)
{
    LinkList *listTable = (LinkList *)malloc(sizeof(LinkList) * LIST_TABLE_SIZE);
    for (int i = 0; i < LIST_TABLE_SIZE; i++)
    {
        listTable[i].head = NULL;
        listTable[i].initialized = false;
    }
    int listIndex = 0, previousIndex = 0;
    LinkList *curList = listTable + listIndex;
    int option;
    do
    {
        int inputValue; // mostly for index;
        ElemType inputElem, getReturnElem;
        Status status;
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
                printf("Initialize list %d\n", listIndex + 1);
                status = initList(curList);
                status == OK ? printf("[Info]: Successfully initialized.\n")
                             : printf("[Error]: List had initialized before.\n");
                break;
            case 2:
                printf("Destroy list %d\n", listIndex + 1);
                status = destroyList(curList);
                status == OK ? printf("[Info]: Successfully destroyed\n")
                             : printf("[Error]: List doesn't initialize or doesn't exist\n");
                break;
            case 3:
                printf("Clear lise %d\n", listIndex + 1);
                status = clearList(curList);
                status == OK ? printf("[Info]: Successfully cleared\n")
                             : printf("[Error]: List doesn't initialize or doesn't exist\n");
                break;
            case 4:
                printf("Is list %d empty?\n", listIndex + 1);
                bool isEmpty = listEmpty(*curList);
                if (isEmpty == ERROR)
                    printf("[Error]: List doesn't initialize or doesn't exist\n");
                else
                    printf(isEmpty ? "[Info]: List %d is empty\n" : "[Info]: List %d is not empty\n", listIndex + 1);
                break;
            case 5:
                int len = listLength(*curList);
                len < 0 ? printf("[Error]: List doesn't initialize or doesn't exist\n")
                        : printf("[Info]: The length of list %d is %d\n", listIndex + 1, len);
                break;
            case 6:
                printf("Please enter the index of the element:\n");
                if (scanf("%d", &inputValue))
                {
                    status = getElem(*curList, inputValue, &getReturnElem);
                    status == OK ? printf("[Info]: The value is %d\n", getReturnElem)
                                 : printf("[Error]: fail to find element. Out of range or list doesn't initialize\n");
                }
                else
                    printf("Invalid input\n");
                clearBuf();
                break;
            case 7:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &inputElem))
                {
                    int index = locateElem(*curList, inputElem, isEqual);
                    if (index == ERROR)
                        printf("[Error]: List doesn't initialize or doesn't exist\n");
                    else
                        index == 0
                            ? printf("[Error]: Element doesn't exist\n")
                            : printf("[Info]: The index of the element is %d\n", index);
                }
                else
                    printf("Invalid input\n");
                clearBuf();
                break;
            case 8:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &inputElem))
                {
                    status = priorElem(*curList, inputElem, &getReturnElem);
                    status == OK ? printf("[Info]: The previous element is %d\n", getReturnElem)
                                 : printf("[Error]: Can not find previous element\n");
                }
                else
                    printf("Invalid input\n");
                clearBuf();
                break;
            case 9:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &inputElem))
                {
                    status = nextElem(*curList, inputElem, &getReturnElem);
                    status == OK ? printf("[Info]: The next element is %d\n", getReturnElem)
                                 : printf("[Error]: Can not find next element\n");
                }
                else
                    printf("Invalid input\n");
                clearBuf();
                break;
            case 10:
                printf("Please enter the index of the element to insert:\n");
                if (!scanf("%d", &inputValue))
                {
                    printf("Invalid value!\n");
                }
                else
                {
                    printf("Please enter the value of the element:\n");
                    if (scanf("%d", &inputElem))
                    {
                        status = listInsert(curList, inputValue, inputElem);
                        status == OVERFLOW &&printf("[Error]: Out of memory\n");
                        status == OK &&printf("[Info]: Insert successfully\n");
                        status == ERROR &&printf("[Error]: Failed to insert element\n");
                    }
                    else
                        printf("Invalid value!\n");
                }
                clearBuf();
                break;
            case 11:
                printf("Please enter the index of the element to be deleted:\n");
                if (scanf("%d", &inputValue))
                {
                    status = listDelete(curList, inputValue, &getReturnElem);
                    status == OK &&printf("[Info]: Successfully delete %d\n", getReturnElem);
                    status == ERROR &&printf("[Error]: Failed to delete\n");
                }
                else
                    printf("Invalid input\n");
                clearBuf();
                break;
            case 12:
                printf("Traverse list %d\n", listIndex + 1);
                status = listTraverse(*curList, printElement);
                printf("\n");
                status == ERROR &&printf("Failed to traverse!\n");
                break;
            case 13:
                printf("Please enter the list to switch:\n");
                if (!scanf("%d", &listIndex) || listIndex > LIST_TABLE_SIZE || listIndex < 1)
                {
                    printf("[Error]: Invalid value\n");
                    listIndex = previousIndex;
                    clearBuf();
                    break;
                }
                listIndex--;
                printf("[Info]: Success\n");
                curList = listTable + listIndex;
                clearBuf();
                break;
            case 14:
                printf("Choose a list to save:\n");
                if (!scanf("%d", &inputValue) || inputValue > LIST_TABLE_SIZE || inputValue < 1)
                {
                    printf("[Error]: Invalid value\n");
                    clearBuf();
                    break;
                }
                status = saveToFile(&listTable[inputValue - 1]);
                printf(status == OK ? "[Info]: Saved successfully\n"
                                    : "[Error]: Failed to save\n");
                clearBuf();
                break;
            case 15:
                printf("Choose a list to save the date from a file:\n");
                if (!scanf("%d", &inputValue) || inputValue > LIST_TABLE_SIZE || inputValue < 1)
                {
                    printf("[Error]: Invalid value\n");
                    clearBuf();
                    break;
                }
                status = loadFromFile(&listTable[inputValue - 1]);
                printf(status == OK ? "[Info]: Loaded successfully\n"
                                    : "[Error]: Failed to load\n");
                clearBuf();
                break;
            default:
                break;
            }
        }
        clearBuf();
        system("cls");
    } while (option);
    printf("\nDone!\n");
    getchar();
    return 0;
}

void printMenu()
{
    printf("             Menu of LinkList's options       \n"
           "    ------------------------------------------\n"
           "     |              0. exit                 | \n"
           "     |                                      | \n"
           "     |   1. initList      2. destroyList    | \n"
           "     |   3. clearList     4. listEmpty      | \n"
           "     |   5. listLength    6. getElem        | \n"
           "     |   7. locateElem    8. priorElem      | \n"
           "     |   9. nextElem      10. listInsert    | \n"
           "     |   11. listDelete   12. listTraverse  | \n"
           "     |   13. switchList   14. saveToFile    | \n"
           "     |   15. loadFromFile                   | \n"
           "     |                                      | \n"
           "    ------------------------------------------\n\n");
}

void clearBuf()
{
    while (getchar() != '\n')
        ;
}

void printElement(LinkNode *node)
{
    printf("%d->", node->data);
}

Status saveToFile(LinkList *list)
{
    if (!list->initialized)
        return ERROR;

    FILE *fp = fopen("./list.txt", "w");
    if (fp == NULL)
        fp = fopen("./list.txt", "wb");

    ElemType temp;
    for (int i = 0; i < listLength(*list); i++)
    {
        getElem(*list, i + 1, &temp);
        fprintf(fp, "%d,", temp);
    }
    fclose(fp);
    return OK;
}

Status loadFromFile(LinkList *list)
{
    FILE *fp = fopen("./list.txt", "r");
    if (fp == NULL)
    {
        printf("[Error]: File doesn't exist\n");
        return ERROR;
    }
    Status result = initList(list);
    if (result == ERROR)
    {
        printf("[Info]: list has been initialized before\n");
        fclose(fp);
        return ERROR;
    }
    else
    {
        ElemType element;
        int i = 1;
        for (; fscanf(fp, "%d,", &element) != EOF; i++)
            listInsert(list, i, element);
        fclose(fp);
        return OK;
    }
}