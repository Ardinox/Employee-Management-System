#include "employee.h"

int isIdUnique(EmployeeList *list, int id)
{
    emp *curr = list->head;
    while (curr != NULL)
    {
        if (curr->empID == id)
            return 0; // Not Unique
        curr = curr->next;
    }
    return 1; // Unique
}

// Accepts ANY integer (Positive or Negative)
int getValidInt(char *prompt)
{
    int value;
    char buffer[100];
    char *endptr;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0)
            {
                printf("(!) Input cannot be empty. Please try again.\n");
                continue;
            }
            
            value = strtol(buffer, &endptr, 10);
            
            if (endptr == buffer || *endptr != '\0')
            {
                printf("(!) Invalid input. Please enter a number.\n");
            }
            else
            {
                return value;
            }
        }
    }
}

// Wrapper: Enforces Positive Integers Only
int getPositiveInt(char *prompt)
{
    int value;
    while (1)
    {
        value = getValidInt(prompt);
        if (value < 0)
        {
            printf("(!) Input must be a positive number.\n");
        }
        else
        {
            return value;
        }
    }
}

void getValidString(char *prompt, char *buffer, int size)
{
    while (1)
    {
        printf("%s", prompt);
        inputString(buffer, size);

        if (strlen(buffer) == 0 || buffer[0] == ' ')
        {
            printf("(!) Field cannot be empty. Please try again.\n");
        }
        else
        {
            break;
        }
    }
}