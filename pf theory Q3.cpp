#include <stdio.h>
#include <string.h>

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

// display function for all employees
void displayEmployees(struct Employee emp[], int n) {
    printf("                 EMPLOYEE LIST              \n");
    printf("      ---------------------------------------\n");
    printf("%-10s %-20s %-15s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("                                               \n");

    for (int i = 0; i < n; i++) {
        printf("%-10d %-20s %-15s %-10.2f\n",
               emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
    printf("                                             \n");
}

// this function tells us the highest salary of employee
void findHighestSalary(struct Employee emp[], int n) {
    int highestIndex = 0;

    for (int i = 1; i < n; i++) {
        if (emp[i].salary > emp[highestIndex].salary)
            highestIndex = i;
    }

    printf("\nEmployee With Highest Salary:\n");
    printf("ID: %d\n", emp[highestIndex].id);
    printf("Name: %s\n", emp[highestIndex].name);
    printf("Designation: %s\n", emp[highestIndex].designation);
    printf("Salary: %.2f\n", emp[highestIndex].salary);
}

// Function to search employee by ID or Name
void searchEmployee(struct Employee emp[], int n) {
    int choice;
    printf("\nSearch by:\n1. Employee ID\n2. Name\nEnter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int id;
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for (int i = 0; i < n; i++) {
            if (emp[i].id == id) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }

        printf("No employee found with ID %d\n", id);
    }

    else if (choice == 2) {
        char name[50];
        printf("Enter Employee Name: ");
        scanf("%s", name);

        for (int i = 0; i < n; i++) {
            if (strcmp(emp[i].name, name) == 0) {
                printf("\nEmployee Found:\n");
                printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
                       emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
                return;
            }
        }

        printf("No employee found with name %s\n", name);
    }

    else {
        printf("Invalid choice!\n");
    }
}

int main() {
    int n;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    struct Employee emp[n];

    //  employee records
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for Employee %d\n", i + 1);
        printf("ID: ");
        scanf("%d", &emp[i].id);

        printf("Name: ");
        scanf("%s", emp[i].name);

        printf("Designation: ");
        scanf("%s", emp[i].designation);

        printf("Salary: ");
        scanf("%f", &emp[i].salary);
    }

    //calling functions
    displayEmployees(emp, n);

    findHighestSalary(emp, n);

    searchEmployee(emp, n);

    return 0;
}

