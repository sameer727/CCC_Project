#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"

char currentUser[50];
char currentRole[20];


// ==============================
// LOGIN SYSTEM
// ==============================
int login() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];

    printf("=====================================\n");
    printf("         STUDENT RECORD SYSTEM       \n");
    printf("=====================================\n");
    printf("              LOGIN PAGE             \n");
    printf("-------------------------------------\n");

    printf("USERNAME : ");
    scanf("%s", inUser);
    printf("PASSWORD : ");
    scanf("%s", inPass);

    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) {
        printf("ERROR: credential file missing!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", u, p, r) == 3) {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            fclose(fp);

            printf("\n✔ Login successful! Logged in as: %s\n", r);
            return 1;
        }
    }

    fclose(fp);
    printf("\n✘ Invalid username or password!\n");
    return 0;
}


// ==============================
// ADD STUDENT
// ==============================
void addStudent() {
    int roll;
    char name[50];
    float mark;

    printf("\nEnter Roll Number : ");
    scanf("%d", &roll);
    printf("Enter Name        : ");
    scanf(" %[^\n]", name);
    printf("Enter Marks       : ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    if (!fp) {
        printf("ERROR: Cannot open student file!\n");
        return;
    }

    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);

    printf("✔ Student added successfully!\n");
}


// ==============================
// DISPLAY ALL STUDENTS
// ==============================
void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("ERROR: No student records found!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;

    printf("\n=====================================\n");
    printf("        STUDENT RECORD LIST\n");
    printf("=====================================\n");
    printf("ROLL\tNAME\t\tMARKS\n");
    printf("-------------------------------------\n");

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        printf("%d\t%-15s %.2f\n", roll, name, mark);
    }

    fclose(fp);
}


// ==============================
// SEARCH STUDENT
// ==============================
void searchStudent() {
    int find;
    printf("\nEnter roll number to search: ");
    scanf("%d", &find);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("ERROR: File missing!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == find) {
            printf("\n✔ Record Found!\n");
            printf("Roll : %d\nName : %s\nMarks: %.2f\n", roll, name, mark);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("✘ No student found with roll %d\n", find);
}


// ==============================
// DELETE STUDENT
// ==============================
void deleteStudent() {
    int delRoll;
    printf("\nEnter roll number to delete: ");
    scanf("%d", &delRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll) {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("✔ Student deleted successfully!\n");
    else
        printf("✘ Roll not found!\n");
}


// ==============================
// UPDATE STUDENT
// ==============================
void updateStudent() {
    int updateRoll;
    printf("\nEnter roll to update: ");
    scanf("%d", &updateRoll);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int roll;
    char name[50];
    float mark;
    int found = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            char newName[50];
            float newMark;

            printf("New Name  : ");
            scanf(" %[^\n]", newName);
            printf("New Marks : ");
            scanf("%f", &newMark);

            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (found)
        printf("✔ Student updated successfully!\n");
    else
        printf("✘ Roll not found!\n");
}


// ==============================
// MENUS BASED ON ROLE
// ==============================
void adminMenu() {
    int c;
    while (1) {
        printf("\n============== ADMIN MENU ==============\n");
        printf("1. Add Student\n2. Display All\n3. Search\n4. Update\n5. Delete\n6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();
        else return;
    }
}

void staffMenu() {
    int c;
    while (1) {
        printf("\n============== STAFF MENU ==============\n");
        printf("1. Add Student\n2. Display All\n3. Search\n4. Update\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) displayStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else return;
    }
}

void guestMenu() {
    int c;
    while (1) {
        printf("\n============== GUEST MENU ==============\n");
        printf("1. Display All\n2. Search\n3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else return;
    }
}

void userMenu() {
    int c;
    while (1) {
        printf("\n============== USER MENU ==============\n");
        printf("1. Display All\n2. Search\n3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &c);

        if (c == 1) displayStudents();
        else if (c == 2) searchStudent();
        else return;
    }
}


// ==============================
// MAIN PROGRAM
// ==============================
int main() {
    if (!login())
        return 0;

    if (strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "staff") == 0)
        staffMenu();
    else if (strcmp(currentRole, "user") == 0)
        userMenu();
    else
        guestMenu();

    return 0;
}
