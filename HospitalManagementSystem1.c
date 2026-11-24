#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_DOCTORS 4
#define MAX_APPOINTMENTS 50

// Structure for Patient
struct Patient {
    int id;
    char name[50];
    int age;
    char issue[50];
};

// Structure for Doctor
struct Doctor {
    int id;
    char name[50];
    char specialization[50];
};

// Structure for Appointment
struct Appointment {
    int patientId;
    int doctorId;
    char timeSlot[20];
};

// Global arrays and counters for easy understanding
struct Patient patients[MAX_PATIENTS];
int patientCount = 0;

struct Doctor doctors[MAX_DOCTORS] = {
    {1, "Dr. Sharma", "General Physician"},
    {2, "Dr. Nair", "Cardiologist"},
    {3, "Dr. Kulkarni", "Orthopedic"},
    {4, "Dr. Mehta", "Pediatrician"}
};

struct Appointment appointments[MAX_APPOINTMENTS];
int appointmentCount = 0;

// Helper function to clear leftover newline characters from input
void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

// Helper function to read a full line of text safely
void readLine(char str[], int size) {
    if (fgets(str, size, stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }
}

// 1. Add a new patient
void addPatients() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nPatient list is full!\n");
        return;
    }

    struct Patient p;
    printf("\n--- Add Patient ---\n");
    printf("Enter Patient ID: ");
    scanf("%d", &p.id);
    clearInputBuffer();

    printf("Enter Patient Name: ");
    readLine(p.name, sizeof(p.name));

    printf("Enter Age: ");
    scanf("%d", &p.age);
    clearInputBuffer();

    printf("Enter Health Issue: ");
    readLine(p.issue, sizeof(p.issue));

    patients[patientCount] = p;
    patientCount++;

    printf("Patient added successfully!\n");
}

// 2. View all patients
void viewPatient() {
    printf("\n--- Patient List ---\n");
    if (patientCount == 0) {
        printf("No patients found.\n");
        return;
    }

    for (int i = 0; i < patientCount; i++) {
        printf("ID: %d | Name: %s | Age: %d | Issue: %s\n",
               patients[i].id,
               patients[i].name,
               patients[i].age,
               patients[i].issue);
    }
}

// 3. View available doctors
void viewDoctors() {
    printf("\n--- Available Doctors ---\n");
    for (int i = 0; i < MAX_DOCTORS; i++) {
        printf("ID: %d | Name: %s | Specialization: %s\n",
               doctors[i].id,
               doctors[i].name,
               doctors[i].specialization);
    }
}

// Check if a patient ID exists
int isValidPatient(int id) {
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// Check if a doctor ID exists
int isValidDoctor(int id) {
    for (int i = 0; i < MAX_DOCTORS; i++) {
        if (doctors[i].id == id) {
            return 1;
        }
    }
    return 0;
}

// 4. Book an appointment
void bookAppointment() {
    if (appointmentCount >= MAX_APPOINTMENTS) {
        printf("\nAppointment slots are full!\n");
        return;
    }

    if (patientCount == 0) {
        printf("\nPlease add a patient first before booking an appointment.\n");
        return;
    }

    struct Appointment app;
    printf("\n--- Book Appointment ---\n");

    viewPatient();
    printf("Enter Patient ID: ");
    scanf("%d", &app.patientId);
    clearInputBuffer();

    if (!isValidPatient(app.patientId)) {
        printf("Invalid Patient ID!\n");
        return;
    }

    viewDoctors();
    printf("Enter Doctor ID: ");
    scanf("%d", &app.doctorId);
    clearInputBuffer();

    if (!isValidDoctor(app.doctorId)) {
        printf("Invalid Doctor ID!\n");
        return;
    }

    printf("Enter Time Slot (e.g., 10:30 AM): ");
    readLine(app.timeSlot, sizeof(app.timeSlot));

    appointments[appointmentCount] = app;
    appointmentCount++;

    printf("Appointment booked successfully!\n");
}

//View all booked appointments
void viewAppointments() {
    printf("\n--- Booked Appointments ---\n");
    if (appointmentCount == 0) {
        printf("No appointments booked yet.\n");
        return;
    }

    for (int i = 0; i < appointmentCount; i++) {
        printf("Appointment %d -> Patient ID: %d | Doctor ID: %d | Time: %s\n",
               i + 1,
               appointments[i].patientId,
               appointments[i].doctorId,
               appointments[i].timeSlot);
    }
}

int main() {
    int choice;

    do {
        printf("\n==============================\n");
        printf("   HOSPITAL MANAGEMENT MENU   \n");
        printf("==============================\n");
        printf("1. Add Patient\n");
        printf("2. View Patients\n");
        printf("3. View Doctors\n");
        printf("4. Book Appointment\n");
        printf("5. View Appointments\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a valid number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addPatients();
                break;
            case 2:
                viewPatient();
                break;
            case 3:
                viewDoctors();
                break;
            case 4:
                bookAppointment();
                break;
            case 5:
                viewAppointments();
                break;
            case 6:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}