#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>

#define INITIAL_CAPACITY 4
#define MAX_INPUT 1024  

//declaring function
void insertLine(char ***lines, int *count, int *capacity, int index, const char *text);
void deleteLine(char ***lines, int *count, int index);
void printAllLines(char **lines, int count);
void shrinkToFit(char ***lines, int *capacity, int count);
void saveToFile(char **lines, int count, const char *filename);
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename);
void freeAll(char ***lines, int *count);


void checkAllocation(void *ptr) {
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        exit(1);
    }
}


void insertLine(char ***lines, int *count, int *capacity, int index, const char *text) {
    if (index < 0 || index > *count) {
        printf("Invalid index for insertion.\n");
        return;
    }

    
    if (*count == *capacity) {
        *capacity *= 2;
        *lines = realloc(*lines, (*capacity) * sizeof(char*));
        checkAllocation(*lines);
    }

    
    memmove(&((*lines)[index + 1]), &((*lines)[index]),
            (*count - index) * sizeof(char*));

    
    (*lines)[index] = malloc(strlen(text) + 1);
    checkAllocation((*lines)[index]);

    strcpy((*lines)[index], text);
    (*count)++;
}


void deleteLine(char ***lines, int *count, int index) {
    if (index < 0 || index >= *count) {
        printf("Invalid index for deletion.\n");
        return;
    }

    free((*lines)[index]);

    
    memmove(&((*lines)[index]), &((*lines)[index + 1]),
            (*count - index - 1) * sizeof(char*));

    (*count)--;

    printf("Line %d deleted.\n", index);
}


void printAllLines(char **lines, int count) {
    printf("\n--- TEXT BUFFER CONTENT ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, lines[i]);
    }
    printf("----------------------------\n\n");
}


void shrinkToFit(char ***lines, int *capacity, int count) {
    *capacity = count;
    *lines = realloc(*lines, (*capacity) * sizeof(char*));
    checkAllocation(*lines);
    printf("Buffer shrunk to fit exactly %d lines.\n", count);
}
//save file
void saveToFile(char **lines, int count, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", lines[i]);
    }

    fclose(fp);
    printf("File saved successfully.\n");
}

// load from file
void loadFromFile(char ***lines, int *count, int *capacity, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file for reading.\n");
        return;
    }

    freeAll(lines, count);

    *capacity = INITIAL_CAPACITY;
    *lines = malloc((*capacity) * sizeof(char*));
    checkAllocation(*lines);

    char buffer[MAX_INPUT];

    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = '\0';  
        insertLine(lines, count, capacity, *count, buffer);
    }

    fclose(fp);
    printf("File loaded successfully.\n");
}

// FREE ALL MEMORY
void freeAll(char ***lines, int *count) {
    for (int i = 0; i < *count; i++) {
        free((*lines)[i]);
    }
    free(*lines);
    *lines = NULL;
    *count = 0;
}

//MAIN EDITOR SYSTEM 
int main() {
    char **lines = NULL;
    int count = 0;
    int capacity = INITIAL_CAPACITY;

    lines = malloc(capacity * sizeof(char*));
    checkAllocation(lines);

    int choice;
    char buffer[MAX_INPUT];
    int index;

    while (1) {
        printf("\n--- MINI TEXT EDITOR ---\n");
        printf("1. Insert line\n");
        printf("2. Delete line\n");
        printf("3. Print all lines\n");
        printf("4. Shrink to fit\n");
        printf("5. Save to file\n");
        printf("6. Load from file\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
        case 1:
            printf("Enter index: ");
            scanf("%d", &index);
            getchar();
            printf("Enter text: ");
            fgets(buffer, MAX_INPUT, stdin);
            buffer[strcspn(buffer, "\n")] = '\0';
            insertLine(&lines, &count, &capacity, index, buffer);
            break;

        case 2:
            printf("Enter index: ");
            scanf("%d", &index);
            deleteLine(&lines, &count, index);
            break;

        case 3:
            printAllLines(lines, count);
            break;

        case 4:
            shrinkToFit(&lines, &capacity, count);
            break;

        case 5:
            saveToFile(lines, count, "output.txt");
            break;

        case 6:
            loadFromFile(&lines, &count, &capacity, "output.txt");
            break;

        case 7:
            freeAll(&lines, &count);
            printf("Exiting editor.\n");
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}

