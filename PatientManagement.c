#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store patient information
typedef struct Patient {
    int id;
    char name[50];
    int age;
    char gender[10];
    int priority; // 1 = Emergency, 2 = Normal
    struct Patient* next;
} Patient;

// Front and rear pointers for both queues
Patient *emergencyFront = NULL, *emergencyRear = NULL;
Patient *normalFront = NULL, *normalRear = NULL;

// Function to create a new patient node
Patient* createPatient() {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    if (!newPatient) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    getchar(); // Consume leftover newline

    printf("Enter Name: ");
    scanf(" %[^\n]", newPatient->name); // to accept spaces

    printf("Enter Age: ");
    scanf("%d", &newPatient->age);

    printf("Enter Gender: ");
    scanf("%s", newPatient->gender);

    // Input validation for priority
    do {
        printf("Enter Priority (1 = Emergency, 2 = Normal): ");
        scanf("%d", &newPatient->priority);
        if (newPatient->priority != 1 && newPatient->priority != 2) {
            printf("Invalid input. Please enter 1 or 2.\n");
        }
    } while (newPatient->priority != 1 && newPatient->priority != 2);

    newPatient->next = NULL;
    return newPatient;
}

// Enqueue patient to the appropriate queue
void enqueuePatient(Patient* p) {
    if (p->priority == 1) {
        // Emergency Queue
        if (emergencyRear == NULL) {
            emergencyFront = emergencyRear = p;
        } else {
            emergencyRear->next = p;
            emergencyRear = p;
        }
    } else {
        // Normal Queue
        if (normalRear == NULL) {
            normalFront = normalRear = p;
        } else {
            normalRear->next = p;
            normalRear = p;
        }
    }
    printf("Patient registered successfully!\n");
}

// Dequeue patient (serve next)
void dequeuePatient() {
    Patient* temp = NULL;
    if (emergencyFront != NULL) {
        temp = emergencyFront;
        emergencyFront = emergencyFront->next;
        if (emergencyFront == NULL) emergencyRear = NULL;
    } else if (normalFront != NULL) {
        temp = normalFront;
        normalFront = normalFront->next;
        if (normalFront == NULL) normalRear = NULL;
    } else {
        printf("No patients in queue.\n");
        return;
    }

    printf("\n--- Calling Patient ---\n");
    printf("ID: %d\nName: %s\nAge: %d\nGender: %s\nPriority: %s\n",
           temp->id, temp->name, temp->age, temp->gender,
           temp->priority == 1 ? "Emergency" : "Normal");
    free(temp);
}

// Display all patients in both queues
void displayPatients() {
    Patient* temp;

    printf("\n--- Emergency Queue ---\n");
    temp = emergencyFront;
    if (!temp) printf("No emergency patients.\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %s\n",
               temp->id, temp->name, temp->age, temp->gender);
        temp = temp->next;
    }

    printf("\n--- Normal Queue ---\n");
    temp = normalFront;
    if (!temp) printf("No normal patients.\n");
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Gender: %s\n",
               temp->id, temp->name, temp->age, temp->gender);
        temp = temp->next;
    }
}

// Free all remaining patients from memory
void freeQueue(Patient* front) {
    Patient* temp;
    while (front != NULL) {
        temp = front;
        front = front->next;
        free(temp);
    }
}

// Main Menu
void menu() {
    int choice;
    while (1) {
        printf("\n\n=== Hospital Patient Management ===\n");
        printf("1. Register New Patient\n");
        printf("2. Call Next Patient\n");
        printf("3. Display All Patients\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enqueuePatient(createPatient());
                break;
            case 2:
                dequeuePatient();
                break;
            case 3:
                displayPatients();
                break;
            case 4:
                printf("Exiting... Thank you!\n");
                freeQueue(emergencyFront);
                freeQueue(normalFront);
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// Main function
int main() {
    menu();
    return 0;
}
