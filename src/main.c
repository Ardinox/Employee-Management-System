#include "employee.h"

int main()
{
    EmployeeList list = {NULL, NULL};
    loadCSV(&list);
    int options = -1;
    do
    {
        printHeader("EMPLOYEE MANAGEMENT SYSTEM");
        printf("|                                      1.        Create New List                                         |\n");
        printf("|                                      2.        Print All Details                                       |\n");
        printf("|                                      3.        Search By ID                                            |\n");
        printf("|                                      4.        Insert new data                                         |\n");
        printf("|                                      5.        Delete Employee Details                                 |\n");
        printf("|                                      6.        Reverse Print                                           |\n");
        printf("|                                      7.        Reverse the List                                        |\n");
        printf("|                                      8.        Exit                                                    |\n");
        printf("+--------------------------------------------------------------------------------------------------------+\n");

        options = getPositiveInt("Enter Your Choice: ");

        switch (options)
        {
        case 1:
            createList(&list);
            break;
        case 2:
            display(&list);
            break;
        case 3:
            searchById(&list);
            break;
        case 4:
            Insertion(&list);
            break;
        case 5:
            deleteEmp(&list);
            break;
        case 6:
            reversed_print(&list);
            break;
        case 7:
            reverse(&list);
            break;
        case 8:
            saveToCSV(&list);
            freeall(&list);
            printf("Exiting program...\n");
            waitForEnter();
            break;
        default:
            printf("(!) Invalid Input: Please select 1-8.\n");
            waitForEnter();
            break;
        }
    } while (options != 8);
    return 0;
}