#include "employee.h"

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void inputString(char *buffer, int size)
{
    if (fgets(buffer, size, stdin) != NULL)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
        {
            buffer[len - 1] = '\0';
        }
        else
        {
            clearInputBuffer();
        }
    }
}

void freeall(EmployeeList *list)
{
    emp *curr = list->head;
    emp *nextNode;
    while (curr != NULL)
    {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }
    list->head = NULL;
    list->tail = NULL;
}