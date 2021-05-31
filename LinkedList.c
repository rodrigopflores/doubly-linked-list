#include <stdio.h>
#include <malloc.h>

typedef struct listNode
{
    int element;
    struct listNode *nextNode;
    struct listNode *previousNode;
} listNode;

void addElementEnd(listNode **head, int element);
void addElementBeginning(listNode **head, int element);
void addElementToEmptyList(listNode **head, int element);
void printList(listNode *head);
void printListBackwards(listNode *head);
void printListAsNodes(listNode *head);
void setIndex(listNode **head, int index, int element);
void addElementIndex(listNode **head, int index, int element);
void removeIndex(listNode **head, int index);
void removeElement(listNode **head, int element);
int getElementIndex(listNode *head, int element);
int getListSize(listNode *head);
void sortList(listNode **head);

int main(void)
{

    listNode *head = NULL;

    addElementEnd(&head, 44);
    addElementEnd(&head, 48);
    addElementEnd(&head, 34);
    addElementEnd(&head, 98);
    addElementEnd(&head, 15);
    printList(head);
    printf("\n");

    addElementBeginning(&head, 32);
    printList(head);
    printf("\n");

    addElementIndex(&head, 3, 78);
    printList(head);
    printf("\n");

    setIndex(&head, 1, 21);
    printList(head);
    printf("\n");

    removeElement(&head, 98);
    printList(head);
    printf("\n");

    removeIndex(&head, 0);
    printList(head);
    printf("\n");

    sortList(&head);
    printList(head);
    printf("\n");

    printListBackwards(head);
    printf("\n");

    printListAsNodes(head);

        return 0;
}

void addElementEnd(listNode **head, int element)
{

    if (*head == NULL)
        addElementToEmptyList(head, element);
    else
    {
        listNode *currentPtr = *head;
        while (currentPtr->nextNode != NULL)
        {
            currentPtr = currentPtr->nextNode;
        }
        currentPtr->nextNode = (listNode *)malloc(sizeof(listNode));
        currentPtr->nextNode->previousNode = currentPtr;
        currentPtr->nextNode->element = element;
        currentPtr->nextNode->nextNode = NULL;
    }
}

void addElementBeginning(listNode **head, int element)
{
    if (*head == NULL)
        addElementToEmptyList(head, element);
    else
    {
        listNode *oldHead = *head;
        *head = (listNode *)malloc(sizeof(listNode));
        (*head)->element = element;
        (*head)->nextNode = oldHead;
        (*head)->previousNode = NULL;
        oldHead->previousNode = *head;
    }
}

void addElementToEmptyList(listNode **head, int element)
{
    *head = (listNode *)malloc(sizeof(listNode));
    (*head)->element = element;
    (*head)->nextNode = NULL;
    (*head)->previousNode = NULL;
}

void printList(listNode *head)
{
    listNode *currentPtr = head;
    if (currentPtr == NULL)
        printf("Empty list\n");
    while (currentPtr != NULL)
    {
        printf("%d\n", currentPtr->element);
        currentPtr = currentPtr->nextNode;
    }
}

void printListAsNodes(listNode *head)
{
    listNode *currentPtr = head;
    if (currentPtr == NULL)
        printf("Empty list\n");
    while (currentPtr != NULL)
    {
        printf(" ______________________________\n| Address: %p    |\n-------------------------------\n| Element: %d\t               |\n| PrevNode: %p   |\n| NextNode: %p   |\n-------------------------------\n", currentPtr, currentPtr->element, currentPtr->previousNode, currentPtr->nextNode);
        if (currentPtr->nextNode != NULL)
            printf("             |\n             V\n");
        currentPtr = currentPtr->nextNode;
    }
}

void printListBackwards(listNode *head)
{
    listNode *currentPtr = head;
    if (currentPtr == NULL)
        printf("Empty list\n");
    else
    {
        while (currentPtr->nextNode != NULL)
        {
            currentPtr = currentPtr->nextNode;
        }
        while (currentPtr->previousNode != NULL)
        {
            printf("%d\n", currentPtr->element);
            currentPtr = currentPtr->previousNode;
        }
        printf("%d\n", currentPtr->element);
    }
}

void setIndex(listNode **head, int index, int element)
{
    listNode *currentPtr = *head;
    if (currentPtr == NULL)
        printf("Empty list");
    else
    {
        for (int i = 0; i < index; i++)
        {
            currentPtr = currentPtr->nextNode;
            if (currentPtr == NULL)
            {
                printf("No such index");
                break;
            }
        }
        if (currentPtr != NULL)
            currentPtr->element = element;
    }
}

void addElementIndex(listNode **head, int index, int element)
{
    listNode *currentPtr = *head;
    if (currentPtr == NULL)
        printf("Empty list");
    else
    {
        for (int i = 0; i < index; i++)
        {
            currentPtr = currentPtr->nextNode;
            if (currentPtr == NULL)
            {
                printf("No such index");
                break;
            }
        }
        if (currentPtr != NULL)
        {
            listNode *newNode = (listNode *)malloc(sizeof(listNode));

            if (currentPtr->previousNode != NULL)
                currentPtr->previousNode->nextNode = newNode;
            else
                *head = newNode;

            newNode->previousNode = currentPtr->previousNode;
            currentPtr->previousNode = newNode;
            newNode->element = element;
            newNode->nextNode = currentPtr;
        }
    }
}

void removeIndex(listNode **head, int index)
{
    listNode *currentPtr = *head;
    if (currentPtr == NULL)
        printf("Empty list\n");
    else
    {
        if (index == 0)
        {
            listNode *oldHead = *head;
            *head = currentPtr->nextNode;
            (*head)->previousNode = NULL;
            free(oldHead);
        }
        else
        {
            for (int i = 0; i < index; i++)
            {
                currentPtr = currentPtr->nextNode;
                if (currentPtr == NULL)
                {
                    printf("No such index in list\n");
                    break;
                }
            }
            if (currentPtr != NULL)
            {
                listNode *oldNode = currentPtr;
                currentPtr->previousNode->nextNode = currentPtr->nextNode;
                if (currentPtr->nextNode != NULL)
                {
                    currentPtr->nextNode->previousNode = currentPtr->previousNode;
                }
                free(oldNode);
            }
        }
    }
}

void removeElement(listNode **head, int element)
{
    int index = getElementIndex(*head, element);
    if (index >= 0)
        removeIndex(head, index);
    else
        printf("Element not found\n");
}

int getElementIndex(listNode *head, int element)

{
    listNode *currentPtr = head;
    int index = 0;
    while (currentPtr != NULL)
    {
        if (currentPtr->element == element)
            return index;
        currentPtr = currentPtr->nextNode;
        index++;
    }
    return -1;
}

void sortList(listNode **head)
{
    int size = getListSize(*head);
    if (size > 1)
    {
        listNode *listArray[size];
        listNode *currentPtr = *head;
        for (int i = 0; i < size; i++)
        {
            listArray[i] = currentPtr;
            currentPtr = currentPtr->nextNode;
        }

        // Bubble sort :(
        int changed = 0;
        do
        {
            changed = 0;
            for (int i = 0; i < size - 1; i++)
            {
                if (listArray[i]->element > listArray[i + 1]->element)
                {
                    listNode *temp = listArray[i];
                    listArray[i] = listArray[i + 1];
                    listArray[i + 1] = temp;
                    changed = 1;
                }
            }
        } while (changed);

        *head = listArray[0];
        listArray[0]->previousNode = NULL;
        for (int i = 0; i < size - 1; i++)
        {
            listArray[i]->nextNode = listArray[i + 1];
            listArray[i + 1]->previousNode = listArray[i];
        }
        listArray[size - 1]->nextNode = NULL;
    }
}

int getListSize(listNode *head)
{
    listNode *currentPtr = head;
    int size = 0;
    while (currentPtr != NULL)
    {
        size++;
        currentPtr = currentPtr->nextNode;
    }
    return size;
}