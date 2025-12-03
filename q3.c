#include <stdio.h>
#include <string.h>

struct employee
{
    int id;
    char name[50];
    char designation[50];
    float salary;
};

void employee_info(struct employee emp[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter The Details For Employee %d", i + 1);

        printf("\nEmployee ID : ");
        scanf("%d", &emp[i].id);
        getchar();

        printf("\nEmployee Name : ");
        scanf("%s", emp[i].name);

        printf("\nDesignation : ");
        scanf("%s", emp[i].designation);

        printf("\nSalary : ");
        scanf("%f", &emp[i].salary);
        getchar();
    }
}

void displayEmployees(struct employee emp[], int n)
{
    printf("\n%-5s %-20s %-20s %-10s\n", "ID", "Name", "Designation", "Salary");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-5d %-20s %-20s %-10.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
    }
}

void find_highestsalary(struct employee emp[], int n)
{
    int maxindex = 0;
    for (int i = 1; i < n; i++)
    {
        if (emp[i].salary > emp[maxindex].salary)
        {
            maxindex = i;
        }
    }

    printf("\nEmployee with Highest Salary:\n");
    printf("ID: %d\nName: %s\nDesignation: %s\nSalary: %.2f\n",
           emp[maxindex].id,
           emp[maxindex].name,
           emp[maxindex].designation,
           emp[maxindex].salary);
}

void search_employee(struct employee emp[], int n)
{
    int choice;
    printf("Enter Your Choice To Find An Employee : ");
    printf("1. By ID \n2. By Name");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        int id;
        printf("Enter The ID : ");
        scanf("%d", &id);

        for (int i = 0; i < n; i++)
        {
            if (emp[i].id == id)
            {
                printf("Employee Is Found\n");
                printf("Found: %d ,%s, %s, %.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
            }
        }
        break;
    }

    case 2:
    {
        char name[50];
        printf("Enter The Name : ");
        scanf("%s", name);

        for (int i = 0; i < n; i++)
        {
            if (strcmp(emp[i].name, name) == 0)
            {
                printf("Employee Is Found\n");
                printf("Found: %d, %s , %s, %.2f\n", emp[i].id, emp[i].name, emp[i].designation, emp[i].salary);
            }
        }
        break;
    }

    default:
        printf("Invalid Choice");
        break;
    }
}

void Bonus(struct employee emp[], int n, float threshold)
{
    for (int i = 0; i < n; i++)
    {
        if (emp[i].salary < threshold)
        {
            emp[i].salary = emp[i].salary + (emp[i].salary * 0.10);
        }
    }
}

int main()
{
    int n;
    float threshold = 50000;

    printf("Enter The Number Of Employees : ");
    scanf("%d", &n);

    struct employee emp[n];

    employee_info(emp, n);
    displayEmployees(emp, n);
    find_highestsalary(emp, n);
    search_employee(emp, n);

    Bonus(emp, n, threshold);

    printf("\nAfter Bonus:\n");
    displayEmployees(emp, n);

    return 0;
}