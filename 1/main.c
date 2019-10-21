#include <stdio.h>
#include "src/SqList.h"

#define LIST_TABLE_SIZE 10

/**
 * @description: print the menu
 * @param {void}
 * @return {void}
 */
void printMenu();

/**
 * @description: print the element
 * @param {ElemType *} - element
 * @return {Status}
 */
Status printElement(ElemType *);

/**
 * @description: Save data to file
 * @param {SqList *} - list
 * @return {Status}
 */
Status saveToFile(SqList *);

/**
 * @description: Load data from file
 * @param {SqList *} - list to load
 * @return {Status}
 */
Status loadFromFile(SqList *);

int main(void)
{
    SqList *listArray = (SqList *)malloc(LIST_TABLE_SIZE * sizeof(SqList));
    for (int i = 0; i < LIST_TABLE_SIZE; i++)
        (listArray + i)->elem = NULL;

    int listIndex = 0, previousIndex = 0;
    SqList *curList = listArray + listIndex;
    do
    {
        printMenu();
        int option, input;
        Status status;
        ElemType e;
        if (!scanf("%d", &option))
            printf("You've entered an invalid number\n");
        else
        {
            while (getchar() != '\n')
                ;
            if (option == 0)
                break;
            switch (option)
            {
            case 1:
                printf("Initialize list %d\n", listIndex + 1);
                status = initList(curList);
                status == OK ? printf("[Info]: Successfully initialized\n")
                             : printf("[Error]: List had initialized before\n");
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
                    printf(isEmpty ? "[Info]: List is empty\n" : "[Info]: List is not empty\n");
                break;
            case 5:
                int len = listLength(*curList);
                len < 0 ? printf("[Error]: List doesn't initialize or doesn't exist\n")
                        : printf("[Info]: The length of list %d is %d\n", listIndex + 1, len);
                break;
            case 6:
                printf("Please enter the index of the element:\n");
                if (scanf("%d", &input))
                {
                    status = getElem(*curList, input, &e);
                    status == OK ? printf("[Info]: The value is %d\n", e.value)
                                 : printf("[Error]: fail to find element. Out of range or list doesn't initialize\n");
                }
                else
                    printf("Invalid input\n");

                while (getchar() != '\n')
                    ;
                break;
            case 7:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &e.value))
                {
                    int index = locateElem(*curList, e, isEqual);
                    index <= 0 ? printf("[Error]: Element doesn't exist\n")
                               : printf("[Info]: The index of the element is %d\n", index);
                }
                else
                    printf("Invalid input\n");

                while (getchar() != '\n')
                    ;
                break;
            case 8:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &e.value))
                {
                    ElemType prior;
                    status = priorElem(*curList, e, &prior);
                    status == OK ? printf("[Info]: The previous element is %d\n", prior.value)
                                 : printf("[Error]: Can not find previous element\n");
                }
                else
                    printf("Invalid input\n");

                while (getchar() != '\n')
                    ;
                break;
            case 9:
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &e.value))
                {
                    ElemType prior;
                    status = nextElem(*curList, e, &prior);
                    status == OK ? printf("[Info]: The next element is %d\n", prior.value)
                                 : printf("[Error]: Can not find next element\n");
                }
                else
                    printf("Invalid input\n");

                while (getchar() != '\n')
                    ;
                break;
            case 10:
                printf("Please enter the index of the element to insert:\n");
                if (!scanf("%d", &input))
                {
                    printf("Invalid value!\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
                printf("Please enter the value of the element:\n");
                if (scanf("%d", &e.value))
                {
                    status = listInsert(curList, input, e);
                    status == OK ? printf("[Info]: Insert successfully")
                                 : printf("[Error]: Failed to insert element");
                }
                else
                    printf("Invalid value!\n");
                while (getchar() != '\n')
                    ;
                break;
            case 11:
                printf("Please enter the index of the element to be deleted:\n");
                if (scanf("%d", &input))
                {
                    status = listDelete(curList, input, &e);
                    status == OK ? printf("[Info]: Successfully delete %d\n", e.value)
                                 : printf("[Error]: Failed to delete");
                }
                else
                    printf("Invalid input\n");

                while (getchar() != '\n')
                    ;
                break;
            case 12:
                printf("Traverse list %d\n", listIndex + 1);
                status = listTraverse(*curList, printElement);
                status != OK &&printf("\nFailed to traverse!\n");
                break;
            case 13:
                printf("Please enter the list to switch:\n");
                if (!scanf("%d", &listIndex) || listIndex > LIST_TABLE_SIZE || listIndex < 1)
                {
                    printf("[Error]: Invalid value\n");
                    listIndex = previousIndex;
                    while (getchar() != '\n')
                        ;
                    break;
                }
                listIndex--;
                printf("[Info]: Success\n");
                curList = listArray + listIndex;
                while (getchar() != '\n')
                    ;
                break;
            case 14:
                printf("Choose a list to save:\n");
                if (!scanf("%d", &input) || input > LIST_TABLE_SIZE || input < 1)
                {
                    printf("[Error]: Invalid value\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
                status = saveToFile(&listArray[input - 1]);
                printf(status == OK ? "[Info]: Saved successfully\n"
                                    : "[Error]: Failed to save\n");
                while (getchar() != '\n')
                    ;
                break;
            case 15:
                printf("Choose a list to save the date from a file:\n");
                if (!scanf("%d", &input) || input > LIST_TABLE_SIZE || input < 1)
                {
                    printf("[Error]: Invalid value\n");
                    while (getchar() != '\n')
                        ;
                    break;
                }
                status = loadFromFile(&listArray[input - 1]);
                printf(status == OK ? "[Info]: Loaded successfully\n"
                                    : "[Error]: Failed to load\n");
                while (getchar() != '\n')
                    ;
                break;
            default:
                break;
            }
        }

        printf("\nType anything to continue\n");
        while (getchar() != '\n')
            ;

        system("cls");
    } while (true);

    printf("Done!\n");
    getchar();
    return 0;
}

void printMenu()
{
    printf("             Menu of SqList's options         \n"
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

Status printElement(ElemType *e)
{
    printf("%d->", e->value);
    return OK;
}

Status saveToFile(SqList *list)
{
    FILE *fp = fopen("./list.txt", "w");
    if (fp == NULL)
        fp = fopen("./list.txt", "wb");

    if (!list->elem)
        return ERROR;

    fprintf(fp, "%d\n", list->length);
    fprintf(fp, "%d\n", list->listSize);
    for (int i = 0; i < listLength(*list); i++)
        fprintf(fp, "%d,", list->elem[i].value);
    fclose(fp);
    return OK;
}

Status loadFromFile(SqList *list)
{
    FILE *fp = fopen("./list.txt", "r");
    if (fp == NULL)
    {
        printf("File doesn't exist\n");
        return ERROR;
    }
    Status result = initList(list);
    if (result == ERROR)
    {
        printf("list has been initialized before\n");
        fclose(fp);
        return ERROR;
    }
    else
    {
        ElemType element;
        int i = 1;
        int length, listSize;
        fscanf(fp, "%d\n", &length);
        fscanf(fp, "%d\n", &listSize);
        for (int i = 1; fscanf(fp, "%d,", &element.value) != EOF; i++)
            listInsert(list, i, element);
        fclose(fp);
        return OK;
    }
}