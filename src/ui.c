#include "employee.h"

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void printHeader(char *title)
{
    clearScreen();
    printf("==========================================================================================================\n");
    printf("                                         %s\n", title);
    printf("==========================================================================================================\n");
}

void waitForEnter()
{
    printf("\nPress [ENTER] to continue...");
    getchar();
}

// Helper for the recursive print function
void reversed_print_util(emp *curr)
{
    if (curr == NULL)
        return;

    reversed_print_util(curr->next);

    printf("%-10d | %-40s | %-4d | %-30s | %10d\n",
           curr->empID, curr->name, curr->age, curr->department, curr->salary);
}