#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Water Usage Record
struct WaterRecord {
    int id;
    char name[50];
    float usage;
    char date[20];
    struct WaterRecord *next;
};

// Head pointer of Linked List
struct WaterRecord *head = NULL;


// Function to create a new record
struct WaterRecord* createRecord() {
    struct WaterRecord *newRecord;

    newRecord = (struct WaterRecord*)malloc(sizeof(struct WaterRecord));

    if (newRecord == NULL) {
        printf("\nMemory allocation failed!\n");
        exit(1);
    }

    printf("\nEnter User ID: ");
    scanf("%d", &newRecord->id);

    printf("Enter User Name: ");
    scanf(" %[^\n]", newRecord->name);

    printf("Enter Water Usage (litres): ");
    scanf("%f", &newRecord->usage);

    printf("Enter Date (DD-MM-YYYY): ");
    scanf("%s", newRecord->date);

    newRecord->next = NULL;

    return newRecord;
}


// Function to add a record
void addRecord() {
    struct WaterRecord *newRecord = createRecord();

    if (head == NULL) {
        head = newRecord;
    } else {
        struct WaterRecord *temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newRecord;
    }

    printf("\nRecord added successfully!\n");
}


// Function to display all records
void displayRecords() {
    struct WaterRecord *temp = head;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("                    WATER USAGE RECORDS\n");
    printf("===============================================================\n");

    printf("%-10s %-20s %-15s %-15s\n",
           "ID", "Name", "Usage(L)", "Date");

    printf("---------------------------------------------------------------\n");

    while (temp != NULL) {
        printf("%-10d %-20s %-15.2f %-15s\n",
               temp->id,
               temp->name,
               temp->usage,
               temp->date);

        temp = temp->next;
    }

    printf("===============================================================\n");
}


// Function to search a record
void searchRecord() {
    int id;
    int found = 0;

    struct WaterRecord *temp = head;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nEnter User ID to search: ");
    scanf("%d", &id);

    while (temp != NULL) {
        if (temp->id == id) {
            printf("\nRecord Found!\n");
            printf("-----------------------------\n");
            printf("User ID       : %d\n", temp->id);
            printf("User Name     : %s\n", temp->name);
            printf("Water Usage   : %.2f litres\n", temp->usage);
            printf("Date          : %s\n", temp->date);
            printf("-----------------------------\n");

            found = 1;
            break;
        }

        temp = temp->next;
    }

    if (!found) {
        printf("\nRecord not found.\n");
    }
}


// Function to update a record
void updateRecord() {
    int id;
    struct WaterRecord *temp = head;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nEnter User ID to update: ");
    scanf("%d", &id);

    while (temp != NULL) {

        if (temp->id == id) {

            printf("\nEnter New User Name: ");
            scanf(" %[^\n]", temp->name);

            printf("Enter New Water Usage (litres): ");
            scanf("%f", &temp->usage);

            printf("Enter New Date (DD-MM-YYYY): ");
            scanf("%s", temp->date);

            printf("\nRecord updated successfully!\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nRecord not found.\n");
}


// Function to delete a record
void deleteRecord() {
    int id;

    struct WaterRecord *temp = head;
    struct WaterRecord *previous = NULL;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nEnter User ID to delete: ");
    scanf("%d", &id);

    // If first node is to be deleted
    if (head->id == id) {
        head = head->next;
        free(temp);

        printf("\nRecord deleted successfully!\n");
        return;
    }

    // Search for the record
    while (temp != NULL && temp->id != id) {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nRecord not found.\n");
        return;
    }

    previous->next = temp->next;
    free(temp);

    printf("\nRecord deleted successfully!\n");
}


// Function to sort records by water usage
void sortRecords() {
    struct WaterRecord *i;
    struct WaterRecord *j;

    int tempId;
    float tempUsage;
    char tempName[50];
    char tempDate[20];

    if (head == NULL || head->next == NULL) {
        printf("\nNot enough records to sort.\n");
        return;
    }

    // Bubble Sort
    for (i = head; i != NULL; i = i->next) {

        for (j = i->next; j != NULL; j = j->next) {

            if (i->usage > j->usage) {

                tempId = i->id;
                i->id = j->id;
                j->id = tempId;

                tempUsage = i->usage;
                i->usage = j->usage;
                j->usage = tempUsage;

                strcpy(tempName, i->name);
                strcpy(i->name, j->name);
                strcpy(j->name, tempName);

                strcpy(tempDate, i->date);
                strcpy(i->date, j->date);
                strcpy(j->date, tempDate);
            }
        }
    }

    printf("\nRecords sorted by water usage successfully!\n");
}


// Function to calculate total water usage
void totalUsage() {
    struct WaterRecord *temp = head;
    float total = 0;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    while (temp != NULL) {
        total += temp->usage;
        temp = temp->next;
    }

    printf("\nTotal Water Usage = %.2f litres\n", total);
}


// Function to find highest water consumer
void highestConsumer() {
    struct WaterRecord *temp = head;
    struct WaterRecord *highest;

    if (head == NULL) {
        printf("\nNo records available.\n");
        return;
    }

    highest = head;
    temp = head->next;

    while (temp != NULL) {

        if (temp->usage > highest->usage) {
            highest = temp;
        }

        temp = temp->next;
    }

    printf("\n====================================\n");
    printf("       HIGHEST WATER CONSUMER\n");
    printf("====================================\n");

    printf("User ID     : %d\n", highest->id);
    printf("User Name   : %s\n", highest->name);
    printf("Water Usage : %.2f litres\n", highest->usage);
    printf("Date        : %s\n", highest->date);

    printf("====================================\n");
}


// Function to save records into file
void saveToFile() {
    FILE *file;
    struct WaterRecord *temp = head;

    file = fopen("water_records.txt", "w");

    if (file == NULL) {
        printf("\nUnable to open file.\n");
        return;
    }

    while (temp != NULL) {

        fprintf(file, "%d|%s|%.2f|%s\n",
                temp->id,
                temp->name,
                temp->usage,
                temp->date);

        temp = temp->next;
    }

    fclose(file);

    printf("\nRecords saved to file successfully!\n");
}


// Main Function
int main() {

    int choice;

    printf("\n");
    printf("====================================================\n");
    printf("     WATER USAGE MONITORING AND MANAGEMENT SYSTEM\n");
    printf("====================================================\n");

    do {

        printf("\n------------------- MAIN MENU -------------------\n");
        printf("1. Add Water Usage Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Delete Record\n");
        printf("6. Sort Records by Water Usage\n");
        printf("7. Calculate Total Water Usage\n");
        printf("8. Find Highest Water Consumer\n");
        printf("9. Save Records to File\n");
        printf("10. Exit\n");
        printf("--------------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addRecord();
                break;

            case 2:
                displayRecords();
                break;

            case 3:
                searchRecord();
                break;

            case 4:
                updateRecord();
                break;

            case 5:
                deleteRecord();
                break;

            case 6:
                sortRecords();
                break;

            case 7:
                totalUsage();
                break;

            case 8:
                highestConsumer();
                break;

            case 9:
                saveToFile();
                break;

            case 10:
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 10);

    return 0;
}