#include <stdio.h>
#include "src/SqList.h"

#define LIST_TABLE_SIZE 10

/**
 * @description: print the menu
 * @param {void}
 * @return {void}
 */
void printMenu();

Status printElement(ElemType *);

int main(void)
{
    SqList *listArray = (SqList *)malloc(LIST_TABLE_SIZE * sizeof(SqList));
    for (int i = 0; i < LIST_TABLE_SIZE; i++)
        (listArray + i)->elem = NULL;

    int listIndex = 0;
    SqList *curList = listArray + listIndex;
    do
    {
        printMenu();
        int option, input;
        Status status;
        ElemType e;
        if (!scanf("%d", &option))
        {
            printf("You've entered an invalid number\n");
            while (getchar() != '\n')
                ;
        }
        else
        {
            getchar();
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
           "     |                                      | \n"
           "    ------------------------------------------\n\n");
}

Status printElement(ElemType *e)
{
    printf("%d->", e->value);
    return OK;
}