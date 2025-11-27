#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct employee
{
    int empID;
    int age;
    int salary;
    char name[50];
    char department[50];
    struct employee *next;
} emp;

emp *head = NULL;

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

emp *newNode()
{
    emp *temp = (emp *)malloc(sizeof(emp));

    if (temp == NULL)
    {
        printf("Memory Allocation Failed!\n");
        exit(1);
    }

    printf("Enter the Employee ID: ");
    scanf("%d", &temp->empID);
    clearInputBuffer();

    printf("Enter the Employee Name: ");
    scanf("%49[^\n]", temp->name); 
    clearInputBuffer(); 

    printf("Enter the age: ");
    scanf("%d", &temp->age);
    clearInputBuffer();

    printf("Enter the Department Name: ");
    scanf("%49[^\n]", temp->department);
    clearInputBuffer();

    printf("Enter the Salary: ");
    scanf("%d", &temp->salary);
    clearInputBuffer();

    temp->next = NULL;

    return temp;
}

void createList()
{
    emp *new_node = newNode();

    if (head == NULL)
    {
        head = new_node;
    }
    else
    {
        emp *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->next = new_node;
    }
    printf("Employee added successfully.\n");
}

void display()
{
    emp *curr = head;
    if (head == NULL)
    {
        printf("The database is Empty!\n");
        return;
    }
    printf("+----------------------Details of Employees-----------------------+\n");
    while (curr != NULL)
    {
        printf("ID: %d\n | Name: %s\n | Age: %d\n | Dept: %s\n | Salary: %d\n",
               curr->empID, curr->name, curr->age, curr->department, curr->salary);
        printf("+-----------------------------------------------------------------+\n");
        curr = curr->next;
    }
}

void searchById()
{
    int empId;
    emp *curr = head;
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

void Insertion()
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

    if (position == 0)
    {
        insert->next = head;
        head = insert;
    }

    else if (head == NULL || position == -1)
    {
        if (head == NULL)
        {
            head = insert;
        }
        else
        {
            emp *curr = head;
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
            curr->next = insert;
        }
    }

    else
    {
        emp *curr = head;
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
            emp *temp = head;
            while(temp->next != NULL) temp = temp->next;
            temp->next = insert;
        }
    }
    printf("Insertion Successful.\n");
}

void deleteEmp()
{
    if (head == NULL) {
        printf("The database is empty, nothing to delete.\n");
        return;
    }

    int empId;
    emp *curr = head;
    emp *prev = NULL;
    
    printf("Enter the Employee Id to Delete: ");
    scanf("%d", &empId);
    clearInputBuffer();

    if (curr->empID == empId)
    {
        head = curr->next;
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
        prev->next = curr->next;
        free(curr);
        printf("Deletion Successful.\n");
    }
}

void reversed_print_util(emp *curr)
{
    if (curr == NULL)
        return;

    reversed_print_util(curr->next);

    printf("ID: %d | Name: %s | Age: %d | Dept: %s | Salary: %d\n",
           curr->empID, curr->name, curr->age, curr->department, curr->salary);
    printf("+-----------------------------------------------------------------+\n");
}

void reversed_print()
{
    if (head == NULL)
    {
        printf("The Dataset is empty.\n");
        return;
    }
    printf("+----------------------Reverse Details----------------------------+\n");
    reversed_print_util(head);
}

void reverse()
{
    emp *prev = NULL, *curr = head, *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
    printf("List reversed successfully!\n");
}

int main()
{
    int options = -1;
    do
    {
        printf("\n+-----------------------------------------------------+\n");
        printf("|                                                     |\n");
        printf("|              EMPLOYEE MANAGEMENT SYSTEM             |\n");
        printf("|                                                     |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|              1. Create List (Add Node)              |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|                2. Print All Details                 |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|                 3. Search By ID                     |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|                4. Insert new data                   |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|            5. Delete Employee Details               |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|                 6. Reverse Print                    |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|               7. Reverse the List                   |\n");
        printf("+-----------------------------------------------------+\n");
        printf("|                     8. Exit                         |\n");
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
            createList();
            break;
        case 2:
            display();
            break;
        case 3:
            searchById();
            break;
        case 4:
            Insertion();
            break;
        case 5:
            deleteEmp();
            break;
        case 6:
            reversed_print();
            break;
        case 7:
            reverse();
            break;
        case 8:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid Input! Please select 1-8.\n");
            break;
        }
    } while (options != 8);
    return 0;
}