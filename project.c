#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* -----------------------------------------
   STRUCT DEFINITIONS
----------------------------------------- */

typedef struct {
    char username[100];   // roll number only
    char password[100];
    char role[20];
} User;

typedef struct {
    int id;
    char name[100];
    char dept[20];
    float cgpa;
} Student;

/* -----------------------------------------
   UTILITIES
----------------------------------------- */

void clearInput() {
    while (getchar() != '\n');
}

/* -----------------------------------------
   AUTH MODULE
----------------------------------------- */

void lockCheck(int attempts) {
    if (attempts >= 3) {
        printf("\nToo many wrong attempts! System locked.\n");
        exit(0);
    }
}

int login(User *out) {
    FILE *f = fopen("credentials.txt", "r");
    char u[100], p[100], r[20];

    if (!f) {
        printf("credentials.txt missing!\n");
        exit(0);
    }

    printf("\n=== LOGIN ===\n");
    printf("Roll Number: ");
    scanf("%s", out->username);
    printf("Password: ");
    scanf("%s", out->password);

    while (fscanf(f, "%[^,],%[^,],%s\n", u, p, r) == 3) {
        if (strcmp(out->username, u) == 0 &&
            strcmp(out->password, p) == 0) {

            strcpy(out->role, r);
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}

/* -----------------------------------------
   ROLL NUMBER → STUDENT ID MAPPING
   EX: AP24110011210 → ID = 10
----------------------------------------- */

int getIDFromRoll(char *roll) {
    int len = strlen(roll);
    int id = atoi(roll + (len - 2));  
    return id;
}

/* -----------------------------------------
   VIEW STUDENT DETAILS
----------------------------------------- */

void viewMyProfile(int id) {
    FILE *f = fopen("students.txt", "r");
    Student s;

    if (!f) { printf("students.txt missing!\n"); return; }

    while (fscanf(f, "%d,%[^,],%[^,],%f\n",
                  &s.id, s.name, s.dept, &s.cgpa) == 4) {

        if (s.id == id) {
            printf("\n--- MY PROFILE ---\n");
            printf("ID: %d\nName: %s\nDept: %s\nCGPA: %.2f\n",
                   s.id, s.name, s.dept, s.cgpa);
            fclose(f);
            return;
        }
    }

    fclose(f);
    printf("Profile not found!\n");
}

void viewMyAttendance(int id) {
    FILE *f = fopen("attendance.txt", "r");
    int sid, total, present;

    if (!f) { printf("attendance.txt missing!\n"); return; }

    while (fscanf(f, "%d,%d,%d\n", &sid, &total, &present) == 3) {

        if (sid == id) {
            float percent = (present * 100.0) / total;
            printf("\n--- MY ATTENDANCE ---\n");
            printf("Present: %d/%d (%.2f%%)\n",
                    present, total, percent);
            fclose(f);
            return;
        }
    }

    fclose(f);
    printf("Attendance not found!\n");
}

/* -----------------------------------------
   VIEW STUDENT MARKS
----------------------------------------- */

void viewMyMarks(int id) {
    FILE *f = fopen("markss.txt", "r");
    int sid;
    float m1, m2, m3, m4, m5;

    if (!f) { printf("markss.txt missing!\n"); return; }

    while (fscanf(f, "%d,%f,%f,%f,%f,%f\n",
                  &sid, &m1,&m2,&m3,&m4,&m5) == 6) {

        if (sid == id) {
            printf("\n--- MY MARKS ---\n");
            printf("Maths: %.1f\n", m1);
            printf("DSA: %.1f\n", m2);
            printf("Digital Logic: %.1f\n", m3);
            printf("DBMS: %.1f\n", m4);
            printf("C Programming: %.1f\n", m5);
            fclose(f);
            return;
        }
    }

    fclose(f);
    printf("Marks not found!\n");
}

/* -----------------------------------------
   VIEW FEE STATUS
----------------------------------------- */

void viewMyFee(int id) {
    FILE *f = fopen("fees.txt", "r");
    int sid, total, paid;

    if (!f) { printf("fees.txt missing!\n"); return; }

    while (fscanf(f, "%d,%d,%d\n",
                  &sid, &total, &paid) == 3) {

        if (sid == id) {
            printf("\n--- MY FEE STATUS ---\n");
            printf("Total Fee : %d\nPaid Fee  : %d\nDue Fee   : %d\n",
                   total, paid, total - paid);
            fclose(f);
            return;
        }
    }

    fclose(f);
    printf("Fee record not found!\n");
}

/* -----------------------------------------
   TIMETABLE MODULE (FIXED)
----------------------------------------- */

void showMyTimetable(int id) {
    FILE *stu = fopen("students.txt", "r");
    FILE *tt = fopen("timetable.txt", "r");

    if (!tt) { printf("timetable.txt missing!\n"); return; }

    Student s;
    char myDept[20];

    while (stu && fscanf(stu, "%d,%[^,],%[^,],%f\n",
                         &s.id, s.name, s.dept, &s.cgpa) == 4) {

        if (s.id == id) {
            strcpy(myDept, s.dept);
            break;
        }
    }
    fclose(stu);

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char today[20];
    strftime(today, sizeof(today), "%A", &tm);

    printf("\n--- TODAY'S TIMETABLE (%s - %s) ---\n",
           myDept, today);

    char dept[20], day[20], sub1[50], sub2[50], sub3[50];
    int found = 0;

    while (fscanf(tt, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                  dept, day, sub1, sub2, sub3) == 5) {

        if (strcmp(dept, myDept) == 0 &&
            strcmp(day, today) == 0) {

            printf("1. %s\n2. %s\n3. %s\n", sub1, sub2, sub3);
            found = 1;
        }
    }

    fclose(tt);

    if (!found)
        printf("No classes today!\n");
}

/* -----------------------------------------
   STUDENT MENU
----------------------------------------- */

void studentMenu(int id) {
    int ch;

    while (1) {
        printf("\n--- STUDENT MENU ---\n");
        printf("1. View My Profile\n");
        printf("2. View My Attendance\n");
        printf("3. View My Marks\n");
        printf("4. View My Fee Status\n");
        printf("5. View Today's Timetable\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: viewMyProfile(id); break;
            case 2: viewMyAttendance(id); break;
            case 3: viewMyMarks(id); break;
            case 4: viewMyFee(id); break;
            case 5: showMyTimetable(id); break;
            case 0: return;
            default: printf("Invalid option\n");
        }
    }
}

/* -----------------------------------------
   ADMIN MENU
----------------------------------------- */

void addStudent() {
    FILE *f = fopen("students.txt", "a");
    Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    clearInput();

    printf("Enter Name: ");
    scanf("%s", s.name);
    clearInput();

    printf("Enter Department: ");
    scanf("%s", s.dept);
    clearInput();

    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);
    clearInput();

    fprintf(f, "%d,%s,%s,%.2f\n", s.id, s.name, s.dept, s.cgpa);

    fclose(f);
    printf("Student added successfully!\n");
}


void viewAllStudents() {
    FILE *f = fopen("students.txt", "r");
    Student s;

    printf("\n--- ALL STUDENTS ---\n");

    while (fscanf(f, "%d,%[^,],%[^,],%f\n",
                  &s.id, s.name, s.dept, &s.cgpa) == 4) {

        printf("ID: %d | Name: %s | Dept: %s | CGPA: %.2f\n",
               s.id, s.name, s.dept, s.cgpa);
    }

    fclose(f);
}

void deleteStudent() {
    int id;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    FILE *f = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    Student s;
    int deleted = 0;

    while (fscanf(f, "%d,%[^,],%[^,],%f\n",
                  &s.id, s.name, s.dept, &s.cgpa) == 4) {

        if (s.id == id) {
            deleted = 1;
            continue;
        }

        fprintf(temp, "%d,%s,%s,%.2f\n",
                s.id, s.name, s.dept, s.cgpa);
    }

    fclose(f);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        printf("Student deleted successfully.\n");
    else
        printf("ID not found.\n");
}

void updateStudentCGPA() {
    int id;
    printf("\nEnter ID to update CGPA: ");
    scanf("%d", &id);

    FILE *f = fopen("students.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    Student s;
    int updated = 0;
    float newCGPA;

    printf("Enter new CGPA: ");
    scanf("%f", &newCGPA);

    while (fscanf(f, "%d,%[^,],%[^,],%f\n",
                  &s.id, s.name, s.dept, &s.cgpa) == 4) {

        if (s.id == id) {
            updated = 1;
            s.cgpa = newCGPA;
        }

        fprintf(temp, "%d,%s,%s,%.2f\n",
                s.id, s.name, s.dept, s.cgpa);
    }

    fclose(f);
    fclose(temp);

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (updated)
        printf("CGPA updated successfully.\n");
    else
        printf("ID not found.\n");
}

void adminMenu() {
    int ch;

    while (1) {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Delete Student\n");
        printf("4. Update Student CGPA\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: deleteStudent(); break;
            case 4: updateStudentCGPA(); break;
            case 0: return;
            default: printf("Invalid option\n");
        }
    }
}

/* -----------------------------------------
   MAIN FUNCTION
----------------------------------------- */

int main() {
    User u;
    int attempts = 0;

    while (!login(&u)) {
        attempts++;
        printf("Wrong login!\n");
        lockCheck(attempts);
    }

    printf("\nLogin Success! Role: %s\n", u.role);

    if (strcmp(u.role, "ADMIN") == 0) {
        adminMenu();
    } else {
        int id = getIDFromRoll(u.username);

        if (id < 1 || id > 50) {
            printf("Invalid student ID mapping!\n");
            return 0;
        }

        studentMenu(id);
    }

    return 0;
}
