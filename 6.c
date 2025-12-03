#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record
{
int id;
char fullname[100];
char batch[20];
char membership[20];
char registration_date[20];
char birth[20];
} record;

record *students = NULL;
int count = 0;

// Load all students from file into memory
void loadDatabase(char *filename)
{
FILE *fp = fopen(filename, "rb"); // read binary
if (!fp) return;

record temp;
while (fread(&temp, sizeof(record), 1, fp))
{
    students = realloc(students, (count + 1) * sizeof(record));
    if (!students) { perror("Memory allocation failed"); exit(EXIT_FAILURE); }

    students[count] = temp;
    count++;
}


}

// Save all students to file
void saveDatabase(char *filename)
{
FILE *fp = fopen(filename, "wb");
if (!fp) { perror("Error saving file"); return; }

fwrite(students, sizeof(record), count, fp);
fclose(fp);

}

// Add a new student
void addStudent(record s, char *filename)
{
for (int i = 0; i < count; i++)
{
if (students[i].id == s.id)
{
printf("This ID already exists in the system\n");
return;
}
}

students = realloc(students, sizeof(record) * (count + 1));
if (!students) { perror("Memory allocation failed"); exit(EXIT_FAILURE); }
students[count] = s;
count++;

FILE *fp = fopen(filename, "ab"); // append
if (!fp) { perror("Error appending file"); return; }
fwrite(&s, sizeof(record), 1, fp);
fclose(fp);

printf("The data was successfully added to the system\n");


}

// Update student batch or membership
void updateStudent(int id, char *filename)
{
for (int i = 0; i < count; i++)
{
if (students[i].id == id)
{
printf("Updating student %s\n", students[i].fullname);
printf("Enter new batch (CS/SE/AI/Cyber Security): ");
fgets(students[i].batch, 20, stdin);
students[i].batch[strcspn(students[i].batch, "\n")] = 0;


        printf("Enter new membership (IEEE/ACM): ");
        fgets(students[i].membership, 20, stdin);
        students[i].membership[strcspn(students[i].membership, "\n")] = 0;

        saveDatabase(filename);
        printf("Student updated successfully\n");
        return;
    }
}
printf("Student ID not found\n");


}

// Delete a student
void deleteStudent(int id, char *filename)
{
int found = 0;
for (int i = 0; i < count; i++)
{
if (students[i].id == id)
{
found = 1;
for (int j = i; j < count - 1; j++)
students[j] = students[j + 1];
count--;
students = realloc(students, count * sizeof(record));
if (!students && count > 0) { perror("Memory allocation failed"); exit(EXIT_FAILURE); }


        saveDatabase(filename);
        printf("Student deleted successfully\n");
        return;
    }
}
if (!found) printf("Student ID not found\n");


}

// Print all students
void printAll()
{
if (count == 0) { printf("No students found\n"); return; }
for (int i = 0; i < count; i++)
{
printf("\nID: %d\nName: %s\nBatch: %s\nMembership: %s\nRegistration: %s\nDOB: %s\n",
students[i].id, students[i].fullname, students[i].batch,
students[i].membership, students[i].registration_date, students[i].birth);
}
}

// Generate batch-wise report
void batchReport()
{
char batch[20];
printf("Enter batch to generate report (CS/SE/AI/Cyber Security): ");
fgets(batch, 20, stdin);
batch[strcspn(batch, "\n")] = 0;


int found = 0;
for (int i = 0; i < count; i++)
{
    if (strcmp(students[i].batch, batch) == 0)
    {
        if (!found) printf("\nStudents in batch %s:\n", batch);
        printf("ID: %d, Name: %s, Membership: %s\n",
               students[i].id, students[i].fullname, students[i].membership);
        found = 1;
    }
}
if (!found) printf("No students found in this batch\n");

}

int main()
{
loadDatabase("members.dat");

int choice;
while (1)
{
    printf("\n==== MEMBERSHIP SYSTEM ====\n");
    printf("1. Register New Student\n");
    printf("2. Update Student\n");
    printf("3. Delete Student\n");
    printf("4. View All Students\n");
    printf("5. Batch-wise Report\n");
    printf("6. Exit\n");

    printf("Enter choice: ");
    scanf("%d", &choice);
    getchar(); // consume newline

    if (choice == 1)
    {
        record s;
        printf("Enter ID: ");
        scanf("%d", &s.id);
        getchar();

        printf("Enter Full Name: ");
        fgets(s.fullname, 100, stdin);
        s.fullname[strcspn(s.fullname, "\n")] = 0;

        printf("Enter Batch (CS/SE/AI/Cyber Security): ");
        fgets(s.batch, 20, stdin);
        s.batch[strcspn(s.batch, "\n")] = 0;

        printf("Enter Membership (IEEE/ACM): ");
        fgets(s.membership, 20, stdin);
        s.membership[strcspn(s.membership, "\n")] = 0;

        printf("Enter Registration Date (YYYY-MM-DD): ");
        fgets(s.registration_date, 20, stdin);
        s.registration_date[strcspn(s.registration_date, "\n")] = 0;

        printf("Enter Date of Birth (YYYY-MM-DD): ");
        fgets(s.birth, 20, stdin);
        s.birth[strcspn(s.birth, "\n")] = 0;

        addStudent(s, "members.dat");
    }
    else if (choice == 2)
    {
        int id;
        printf("Enter ID to update: ");
        scanf("%d", &id);
        getchar();
        updateStudent(id, "members.dat");
    }
    else if (choice == 3)
    {
        int id;
        printf("Enter ID to delete: ");
        scanf("%d", &id);
        getchar();
        deleteStudent(id, "members.dat");
    }
    else if (choice == 4)
    {
        printAll();
    }
    else if (choice == 5)
    {
        batchReport();
    }
    else if (choice == 6)
    {
        printf("Saving & exiting...\n");
        saveDatabase("members.dat");
        break;
    }
    else
    {
        printf("Invalid choice! Try again.\n");
    }
}

free(students);
return 0;

}
