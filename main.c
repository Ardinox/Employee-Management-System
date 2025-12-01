#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "data.csv"

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

// Helper Function
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

emp *newNode()
{
    emp *temp = (emp *)malloc(sizeof(emp));

    if (temp == NULL)
    {
        return NULL;
    }

    printf("Enter the Employee ID: ");
    scanf("%d", &temp->empID);
    clearInputBuffer();

    printf("Enter the Name: ");
    inputString(temp->name, 50);

    printf("Enter the age: ");
    scanf("%d", &temp->age);
    clearInputBuffer();

    printf("Enter the Department Name: ");
    inputString(temp->department, 50);

    printf("Enter the Salary: ");
    scanf("%d", &temp->salary);
    clearInputBuffer();

    temp->next = NULL;

    return temp;
}

void createList(EmployeeList *list)
{

    if (list->head != NULL)
    {
        char choice;
        printf("Warning: A list already exists. Overwrite it? (y/n): ");
        scanf(" %c", &choice);
        clearInputBuffer();

        if (choice == 'y' || choice == 'Y')
        {
            freeall(list);
        }
        else
        {
            printf("Operation cancelled.\n");
            return;
        }
    }
    int count;
    printf("Enter number of Data You want to insert: ");
    scanf("%d", &count);
    if (count < 1)
    {
        printf("Operation Cancelled: Invalid Input!\n");
        return;
    }

    while (count--)
    {
        emp *new_node = newNode();
        if (new_node == NULL)
        {
            printf("Could not add employee: System out of memory\n");
            return;
        }
        if (list->head == NULL)
        {
            list->head = new_node;
            list->tail = new_node;
        }
        else
        {
            emp *curr = list->head;
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = new_node;
            list->tail = new_node;
        }
        printf("Employee-%d added successfully.\n", new_node->empID);
    }
}

void display(EmployeeList *list)
{
    emp *curr = list->head;
    if (list->head == NULL)
    {
        printf("The database is Empty!\n");
        return;
    }
    printf("+-----------------Details of Employees----------------+\n");
    while (curr != NULL)
    {
        printf("ID: %d\n | Name: %s\n | Age: %d\n | Dept: %s\n | Salary: %d\n", curr->empID, curr->name, curr->age, curr->department, curr->salary);
        printf("+-----------------------------------------------------+\n");
        curr = curr->next;
    }
}

void searchById(EmployeeList *list)
{
    int empId;
    emp *curr = list->head;
    printf("Enter the Employee Id to Search: ");
    scanf("%d", &empId);
    clearInputBuffer();

    while (curr != NULL)
    {
        if (curr->empID == empId)
        {
            printf("Employee Details Found:\n");
            printf("ID: %d | Name: %s\n", curr->empID, curr->name);
            return;
        }
        curr = curr->next;
    }
    printf("Employee details not Found!\n");
}

void Insertion(EmployeeList *list)
{
    int position;

    printf("Choose a position to insert\n");
    printf("Enter '0' to insert at beginning\n");
    printf("Enter '-1' to insert at the end\n");
    printf("Enter position (e.g., 1, 2) to insert specific index: ");
    scanf("%d", &position);
    clearInputBuffer();

    if (position != -1 && position < 0)
    {
        printf("Invalid Input!\n");
        return;
    }

    emp *insert = newNode();
    if (insert == NULL)
    {
        printf("Could not add employee: System out of memory\n");
        return;
    }

    if (position == 0)
    {
        insert->next = list->head;
        list->head = insert;

        if (list->tail == NULL)
        {
            list->tail = insert;
        }
    }

    else if (list->head == NULL || position == -1)
    {
        if (list->head == NULL)
        {
            list->head = insert;
            list->tail = insert;
        }
        else
        {
            list->tail->next = insert;
            list->tail = insert;
        }
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

        if (prev != NULL)
        {
            prev->next = insert;
            insert->next = curr;
        }
        else
        {
            printf("Position out of bounds. Appending to end instead.\n");
            list->tail->next = insert;
            list->tail = insert;
        }
    }
    printf("Insertion Successful.\n");
}

void deleteEmp(EmployeeList *list)
{
    if (list->head == NULL)
    {
        printf("The database is empty, nothing to delete.\n");
        return;
    }

    int empId;
    emp *curr = list->head;
    emp *prev = NULL;

    printf("Enter the Employee Id to Delete: ");
    scanf("%d", &empId);
    clearInputBuffer();

    if (curr->empID == empId)
    {
        list->head = curr->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
        free(curr);
        printf("Deletion Successful.\n");
        return;
    }

    while (curr != NULL && curr->empID != empId)
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
    {
        printf("The Employee Id doesn't exist.\n");
        return;
    }
    else
    {
        if (curr == list->tail)
        {
            list->tail = prev;
        }
        prev->next = curr->next;
        free(curr);
        printf("Deletion Successful.\n");
    }
}

// Recurssion Utility Function
void reversed_print_util(emp *curr)
{
    if (curr == NULL)
        return;

    reversed_print_util(curr->next);

    printf("ID: %d \n| Name: %s \n| Age: %d \n| Dept: %s \n| Salary: %d\n",
           curr->empID, curr->name, curr->age, curr->department, curr->salary);
    printf("+-----------------------------------------------------+\n");
}

void reversed_print(EmployeeList *list)
{
    if (list->head == NULL)
    {
        printf("The Dataset is empty.\n");
        return;
    }
    printf("+-------------------Reverse Details-------------------+\n");
    reversed_print_util(list->head);
}

void reverse(EmployeeList *list)
{
    if (list->head == NULL)
    {
        printf("The database is Empty.\n");
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
}

// File Handling
void saveToCSV(EmployeeList *list)
{
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL)
    {
        printf("Error opening file for writing!\n");
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
    while (fscanf(fp, "%d,%[^,],%d,%[^,],%d\n", &id, name, &age, dept, &salary) == 5)
    {
        emp *temp = (emp *)malloc(sizeof(emp));
        if (temp == NULL)
        {
            printf("Memory Allocation Failed!\n");
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
        printf("=======================================================\n");
        printf("|              EMPLOYEE MANAGEMENT SYSTEM             |\n");
        printf("=======================================================\n");
        printf("|            1.     Create New List                   |\n");
        printf("|            2.     Print All Details                 |\n");
        printf("|            3.      Search By ID                     |\n");
        printf("|            4.     Insert new data                   |\n");
        printf("|            5. Delete Employee Details               |\n");
        printf("|            6.      Reverse Print                    |\n");
        printf("|            7.    Reverse the List                   |\n");
        printf("|            8.          Exit                         |\n");
        printf("+-----------------------------------------------------+\n");
        printf("Enter Your Choice: ");

        if (scanf("%d", &options) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

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
            break;
        default:
            printf("Invalid Input! Please select 1-8.\n");
            break;
        }
    } while (options != 8);
    return 0;
}