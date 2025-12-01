#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "data.csv"

// UI Macros
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

typedef struct employee
{
    int empID;
    int age;
    int salary;
    char name[50];
    char department[50];
    struct employee *next;
} emp;

typedef struct EmployeeList
{
    emp *head;
    emp *tail;
} EmployeeList;

// --- UI Helper Functions ---

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void waitForEnter()
{
    printf("\nPress [ENTER] to continue...");
    getchar();
}

void printHeader(char *title)
{
    clearScreen();
    printf("==========================================================================================================\n");
    printf("                                         %s\n", title);
    printf("==========================================================================================================\n");
}

// --- Validation Helpers ---

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

// BASE FUNCTION: Accepts ANY integer (Positive or Negative)
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

// WRAPPER FUNCTION:
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

// --- Utility Functions ---

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

emp *newNode(EmployeeList *list)
{
    emp *temp = (emp *)malloc(sizeof(emp));
    if (temp == NULL)
        return NULL;

    printf("[NEW ENTRY]\n");
    do
    {
        temp->empID = getPositiveInt("Enter the Employee ID: ");
        if (!isIdUnique(list, temp->empID))
            printf("(!) Error: ID %d already exists.\n", temp->empID);
    } while (!isIdUnique(list, temp->empID));

    // Name Check
    getValidString("Enter the Name: ", temp->name, 50);

    do
    {
        temp->age = getValidInt("Enter the Age: ");
        if (temp->age < 18 || temp->age > 100)
            printf("(!) Please enter a valid age (18-100).\n");
    } while (temp->age < 18 || temp->age > 100);

    getValidString("Enter the Department Name: ", temp->department, 50);

    temp->salary = getPositiveInt("Enter the Salary: ");

    temp->next = NULL;
    return temp;
}

void reversed_print_util(emp *curr)
{
    if (curr == NULL)
        return;
    reversed_print_util(curr->next);
    printf("%-10d | %-40s | %-4d | %-30s | %10d\n",
           curr->empID, curr->name, curr->age, curr->department, curr->salary);
}

// --- Core Functions ---

void createList(EmployeeList *list)
{
    printHeader("BATCH DATA ENTRY");
    if (list->head != NULL)
    {
        char choice;
        printf("(!) Warning: A list already exists. Overwrite it? (y/n): ");
        scanf(" %c", &choice);
        clearInputBuffer();

        if (choice == 'y' || choice == 'Y')
        {
            freeall(list);
        }
        else
        {
            return;
        }
    }

    int count = getValidInt("Enter number of records to add: ");

    if (count < 1)
    {
        printf("(!) Operation Cancelled.\n");
        waitForEnter();
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\n--- Record %d of %d ---\n", i + 1, count);
        emp *new_node = newNode(list);
        if (new_node == NULL)
        {
            printf("(!) System out of memory\n");
            waitForEnter();
            return;
        }
        if (list->head == NULL)
        {
            list->head = new_node;
            list->tail = new_node;
        }
        else
        {
            list->tail->next = new_node;
            list->tail = new_node;
        }
        printf("Employee-%d added successfully.\n", new_node->empID);
        waitForEnter();
    }
}

void display(EmployeeList *list)
{
    emp *curr = list->head;
    if (list->head == NULL)
    {
        printf("(!) The database is Empty\n");
        waitForEnter();
        return;
    }
    printHeader("Details of Employees");
    printf("%-10s | %-40s | %-4s | %-30s | %10s\n", "ID", "NAME", "AGE", "DEPT", "SALARY");
    while (curr != NULL)
    {
        printf("%-10d | %-40s | %-4d | %-30s | %10d\n",
               curr->empID, curr->name, curr->age, curr->department, curr->salary);
        curr = curr->next;
    }
    waitForEnter();
}

void searchById(EmployeeList *list)
{
    printHeader("SEARCH RECORD");

    int empId = getPositiveInt("Enter the Employee Id to Search: ");

    emp *curr = list->head;
    while (curr != NULL)
    {
        if (curr->empID == empId)
        {
            printf("\n  [ Record Found ]\n");
            printf("  ------------------------\n");
            printf("  ID     : %d\n", curr->empID);
            printf("  Name   : %s\n", curr->name);
            printf("  Dept   : %s\n", curr->department);
            printf("  Age    : %d\n", curr->age);
            printf("  Salary : %d\n", curr->salary);
            printf("  ------------------------\n");
            waitForEnter();
            return;
        }
        curr = curr->next;
    }
    printf("(!) Records not Found!\n");
    waitForEnter();
}

void Insertion(EmployeeList *list)
{
    printHeader("INSERT NEW RECORD");
    printf("  0  : At Beginning\n  -1 : At End\n  N  : At Index N\n");

    int position = getValidInt("\n  Position: ");

    if (position != -1 && position < 0)
    {
        printf("Invalid Input!\n");
        waitForEnter();
        return;
    }

    emp *insert = newNode(list);
    if (insert == NULL)
    {
        printf("(!) System out of memory.\n");
        waitForEnter();
        return;
    }

    if (list->head == NULL)
    {
        list->head = insert;
        list->tail = insert;
    }
    else if (position == 0)
    {
        insert->next = list->head;
        list->head = insert;
    }
    else if (position == -1)
    {
        list->tail->next = insert;
        list->tail = insert;
    }
    else
    {
        emp *curr = list->head;
        emp *prev = NULL;
        int curr_pos = 0;

        while (curr != NULL && curr_pos < position)
        {
            prev = curr;
            curr = curr->next;
            curr_pos++;
        }

        if (curr == NULL)
        {
            printf("Position out of bounds. Appending to end instead.\n");
            list->tail->next = insert;
            list->tail = insert;
        }
        else
        {
            prev->next = insert;
            insert->next = curr;
        }
    }

    printf("Insertion Successful.\n");
    waitForEnter();
}

void deleteEmp(EmployeeList *list)
{
    printHeader("DELETE RECORD");
    if (list->head == NULL)
    {
        printf("The database is empty, nothing to delete.\n");
        waitForEnter();
        return;
    }

    int empId = getPositiveInt("Enter ID to Delete: ");

    emp *curr = list->head;
    emp *prev = NULL;

    if (curr->empID == empId)
    {
        list->head = curr->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        free(curr);
        printf("Deletion Successful.\n");
        waitForEnter();
        return;
    }

    while (curr != NULL && curr->empID != empId)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("(!) The Id doesn't exist.\n");
        waitForEnter();
        return;
    }
    else
    {
        if (curr == list->tail)
        {
            list->tail = prev;
            prev->next = NULL;
        }
        else
        {
            prev->next = curr->next;
        }
        free(curr);
        printf("Deletion Successful.\n");
        waitForEnter();
    }
}

void reversed_print(EmployeeList *list)
{
    if (list->head == NULL)
    {
        printf("(!) The Dataset is empty.\n");
        return;
    }
    printHeader("Reverse View");
    printf("%-10s | %-40s | %-4s | %-30s | %10s\n", "ID", "NAME", "AGE", "DEPARTMENT", "SALARY");
    reversed_print_util(list->head);
    waitForEnter();
}

void reverse(EmployeeList *list)
{
    printHeader("REVERSE LIST ORDER");
    if (list->head == NULL)
    {
        printf("(!) The database is Empty.\n");
        waitForEnter();
        return;
    }
    emp *prev = NULL, *curr = list->head, *next = NULL;
    emp *old_head = list->head;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
    list->tail = old_head;
    printf("List reversed successfully!\n");
    waitForEnter();
}

void saveToCSV(EmployeeList *list)
{
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("(!) Error opening file for writing!\n");
        return;
    }
    fprintf(fp, "EmpID,Name,Age,Department,Salary\n");
    emp *curr = list->head;
    while (curr != NULL)
    {
        fprintf(fp, "%d,%s,%d,%s,%d\n", curr->empID, curr->name, curr->age, curr->department, curr->salary);
        curr = curr->next;
    }
    fclose(fp);
    printf("Data Saved in data.csv file successfully.\n");
}

void loadCSV(EmployeeList *list)
{
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL)
    {
        return;
    }
    char buffer[200];
    fgets(buffer, 200, fp);
    int id, age, salary;
    char name[50], dept[50];

    while (fscanf(fp, "%d,%49[^,],%d,%49[^,],%d\n", &id, name, &age, dept, &salary) == 5)
    {
        emp *temp = (emp *)malloc(sizeof(emp));
        if (temp == NULL)
        {
            printf("Memory Allocation Failed!\n");
            waitForEnter();
            return;
        }
        temp->empID = id;
        strcpy(temp->name, name);
        temp->age = age;
        strcpy(temp->department, dept);
        temp->salary = salary;
        temp->next = NULL;
        if (list->head == NULL)
        {
            list->head = temp;
            list->tail = temp;
        }
        else
        {
            list->tail->next = temp;
            list->tail = temp;
        }
    }
    fclose(fp);
}

int main()
{
    EmployeeList list = {NULL, NULL};
    loadCSV(&list);
    int options = -1;
    do
    {
        printHeader("EMPLOYEE MANAGEMENT SYSTEM");
        printf("|                                     1.        Create New List                                          |\n");
        printf("|                                     2.        Print All Details                                        |\n");
        printf("|                                     3.        Search By ID                                             |\n");
        printf("|                                     4.        Insert new data                                          |\n");
        printf("|                                     5.        Delete Employee Details                                  |\n");
        printf("|                                     6.        Reverse Print                                            |\n");
        printf("|                                     7.        Reverse the List                                         |\n");
        printf("|                                     8.        Exit                                                     |\n");
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