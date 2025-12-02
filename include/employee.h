#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Macros ---
#define FILENAME "data.csv"

#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// --- Data Structures ---
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

// --- Function Prototypes ---

// ui.c
void clearScreen();
void printHeader(char *title);
void waitForEnter();
void reversed_print_util(emp *curr);

// utils.c
void clearInputBuffer();
void inputString(char *buffer, int size);
void freeall(EmployeeList *list);

// validation.c
int isIdUnique(EmployeeList *list, int id);
int getValidInt(char *prompt);
int getPositiveInt(char *prompt);
void getValidString(char *prompt, char *buffer, int size);

// core.c
emp *newNode(EmployeeList *list);
void createList(EmployeeList *list);
void display(EmployeeList *list);
void searchById(EmployeeList *list);
void Insertion(EmployeeList *list);
void deleteEmp(EmployeeList *list);
void reversed_print(EmployeeList *list);
void reverse(EmployeeList *list);
void saveToCSV(EmployeeList *list);
void loadCSV(EmployeeList *list);

#endif