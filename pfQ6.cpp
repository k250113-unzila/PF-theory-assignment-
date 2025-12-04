#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "members.dat"


typedef struct {
    int studentID;
    char fullName[100];
    char batch[20];            
    char membershipType[10];   
    char regDate[20];           
    char dob[20];               
    char interest[10];          
} Student;

// Global dynamic list
Student *students = NULL;
int studentCount = 0;


void loadDatabase(const char *filename);
void saveDatabase(const char *filename);
void addStudent(Student s, const char *filename);
int checkDuplicateID(int id);
void updateStudent(int studentID);
void deleteStudent(int studentID);
void displayAll();
void batchReport();
void menu();


void loadDatabase(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;  // File not created yet

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

fseek(fp, 0, SEEK_END);
long size = ftell(fp);
rewind(fp);

// Ensure file size matches struct size
if (size % sizeof(Student) != 0) {
    printf("Corrupted file format.\n");
    fclose(fp);
    return;
}

studentCount = size / sizeof(Student);

// Allocate memory only if count > 0
if (studentCount > 0) {
    students = (Student *)malloc(studentCount * sizeof(Student));
    if (!students) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    size_t readCount = fread(students, sizeof(Student), studentCount, fp);
    if (readCount != studentCount) {
        printf("File read error.\n");
        free(students);
        students = NULL;
        studentCount = 0;
    }
}


    fclose(fp);
}


void saveDatabase(const char *filename) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Error: Cannot save file.\n");
        return;
    }

    fwrite(students, sizeof(Student), studentCount, fp);
    fclose(fp);
}


int checkDuplicateID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == id)
            return 1;
    }
    return 0;
}


void addStudent(Student s, const char *filename) {
    if (checkDuplicateID(s.studentID)) {
        printf("Error: Student ID already exists.\n");
        return;
    }

    students = realloc(students, (studentCount + 1) * sizeof(Student));
    students[studentCount++] = s;

    saveDatabase(filename);

    printf("Student added successfully.\n");
}


void updateStudent(int studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {

            printf("Update batch (CS/SE/Cyber/AI): ");
            scanf("%s", students[i].batch);

            printf("Update Membership (IEEE/ACM): ");
            scanf("%s", students[i].membershipType);

            saveDatabase(FILENAME);

            printf("Record updated successfully.\n");
            return;
        }
    }
    printf("Student not found.\n");
}


void deleteStudent(int studentID) {
    int idx = -1;

    for (int i = 0; i < studentCount; i++) {
        if (students[i].studentID == studentID) {
            idx = i;
            break;
        }
    }

    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }

    for (int i = idx; i < studentCount - 1; i++)
        students[i] = students[i + 1];

    studentCount--;
    students = realloc(students, studentCount * sizeof(Student));

    saveDatabase(FILENAME);

    printf("Record deleted successfully.\n");
}


void displayAll() {
    printf("\n----- ALL STUDENT RECORDS -----\n");
    for (int i = 0; i < studentCount; i++) {
        Student s = students[i];
        printf("ID: %d | Name: %s | Batch: %s | Membership: %s | Reg: %s | DOB: %s | Interest: %s\n",
               s.studentID, s.fullName, s.batch, s.membershipType,
               s.regDate, s.dob, s.interest);
    }
    printf("--------------------------------\n");
}


void batchReport() {
    char targetBatch[20];
    char targetInterest[10];

    printf("Enter Batch (CS/SE/Cyber/AI): ");
    scanf("%s", targetBatch);

    printf("Interest (IEEE/ACM/Both): ");
    scanf("%s", targetInterest);

    printf("\n----- REPORT FOR %s (%s) -----\n", targetBatch, targetInterest);

    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].batch, targetBatch) == 0 &&
            strcmp(students[i].interest, targetInterest) == 0) {
            printf("ID: %d | Name: %s\n", students[i].studentID, students[i].fullName);
        }
    }

    printf("-----------------------------------\n");
}


void menu() {
    int choice;

    while (1) {
        printf("\n===== IEEE/ACM Membership Manager =====\n");
        printf("1. Register New Student\n");
        printf("2. Update Student\n");
        printf("3. Delete Student\n");
        printf("4. View All Registrations\n");
        printf("5. Generate Batch Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Student s;

            printf("Enter Student ID: ");
            scanf("%d", &s.studentID);

            printf("Full Name: ");
            getchar();
            fgets(s.fullName, 100, stdin);
            s.fullName[strcspn(s.fullName, "\n")] = '\0';

            printf("Batch (CS/SE/Cyber/AI): ");
            scanf("%s", s.batch);

            printf("Membership (IEEE/ACM): ");
            scanf("%s", s.membershipType);

            printf("Registration Date (YYYY-MM-DD): ");
            scanf("%s", s.regDate);

            printf("Date of Birth (YYYY-MM-DD): ");
            scanf("%s", s.dob);

            printf("Interest (IEEE/ACM/Both): ");
            scanf("%s", s.interest);

            addStudent(s, FILENAME);
        }

        else if (choice == 2) {
            int id;
            printf("Enter Student ID to update: ");
            scanf("%d", &id);
            updateStudent(id);
        }

        else if (choice == 3) {
            int id;
            printf("Enter Student ID to delete: ");
            scanf("%d", &id);
            deleteStudent(id);
        }

        else if (choice == 4) {
            displayAll();
        }

        else if (choice == 5) {
            batchReport();
        }

        else if (choice == 6) {
            saveDatabase(FILENAME);
            printf("Exiting. Data saved.\n");
            return;
        }

        else {
            printf("Invalid option.\n");
        }
    }
}


int main() {
    loadDatabase(FILENAME);
    menu();

    free(students);
    return 0;
}

