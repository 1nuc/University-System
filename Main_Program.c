//Kashave Sathyvell A/L Sathyvell TP075164
//Amiraj Singh TP074793
//Abdul Wahab Moosa TP075747
//Ahmed Alyafai TP074799
//Abdirashid Mohamed Akira TP076161


/*SYSTEM ADMIN LOGIN FUNCTION:

    username:   systemadmin1
    password:   systemadmin123

*/

#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "allLogin.h" // Include the header file containing login functions
#include "amiraj.h"
#include "grades.h"
#include"C_Assignment_Kashave.h"
#include"studentsinfo.h"
#include "lecturer_Amiraj.h"
#include "programadmin5.h"
#include "grades_weightage.h"
#include "akira_Genaratereport.h"
#define MAX_OPTIONS 2
#define MAX_DESCRIPTION_LENGTH 50

typedef struct {
    int userTypeCode;
    char userDescription[MAX_DESCRIPTION_LENGTH];
} UserTypeOption;

void displayUserTypeMenu(UserTypeOption menu[], int numOptions);
void displayMenu(int userTypeCode);
void displayStudentMenu();
void displaySysAdminMenu();
void displayLecturerMenu();
void displayAdminMenu();


int userType = 0;
int login() {
    //int userType;
    printf("Select user type:\n1. Lecturer\n2. Student\n3. Program Admin\n4. System Admin\n");
    scanf("%d", &userType);
    getchar(); // Consume newline

    switch (userType) {
        case 1: // Lecturer
            if (LoginLecturer()) {
                printf("Lecturer logged in successfully.\n");
                return 1; // Successful login
            } else {
                printf("Lecturer login failed.\n");
                return 0; // Failed login
            }
            break;
        case 2: {
            if (LoginStudent()) {
                printf("Student logged in successfully.\n");
                return 1;
            } else {
                printf("Student login failed.\n");
                return 0;
            }// Student
            break;
            }

        case 3: // Program Admin
            if (LoginPadmin()) {
                printf("Program Admin logged in successfully.\n");
                return 1; // Successful login
            } else {
                printf("Program Admin login failed.\n");
                return 0; // Failed login
            }
            break;
        case 4: // System Admin
            if (LoginSystemAdmin()) {
                printf("System Admin logged in successfully.\n");
                return 1; // Successful login
            } else {
                printf("System Admin login failed.\n");
                return 0; // Failed login
            }
            break;
        default:
            printf("Invalid user type selected.\n");
            return 0; // Failed login
            break;
    }
}


void printLetterByLetter(const char *str, unsigned int delay) {
    struct timespec ts;
    ts.tv_sec = delay / 1000; // Convert delay from milliseconds to seconds
    ts.tv_nsec = (delay % 1000) * 1000000; // Convert remainder to nanoseconds

    while (*str) {
        putchar(*str++);
        fflush(stdout); // Flush output to ensure immediate display
        nanosleep(&ts, NULL); // Delay specified by ts
    }
}


int main() {
    int choice;
    int userTypeCode;

    // Define user type menu options
    UserTypeOption userTypeMenu[MAX_OPTIONS] = {
        {1, "Login"},
        {2, "Quit application"}
    };
    char *heading = "===============================Welcome to the student Information System===============================";

    unsigned int delay = 10; // Delay in milliseconds (adjust as needed)
    printLetterByLetter(heading, delay);


    displayUserTypeMenu(userTypeMenu, MAX_OPTIONS);
    printf("\t\t\t\tChoose Your option: ");
    scanf("%d", &choice);
    getchar();

    // Validate the user's choice
    if (choice < 1 || choice > MAX_OPTIONS) {
        printf("\nInvalid choice. Please enter a number between 1 and %d.\n", MAX_OPTIONS);
        return 1;
    }
    if (choice == 2) {
        printf("Exiting application...\n");
        return 0; // Quit the application
    }


    // Get the user type code based on the choice
    userTypeCode = userTypeMenu[choice - 1].userTypeCode;

    // Perform login and check if successful before displaying menu
    if (login() == 1) {
        displayMenu(userType);
    } else {
        printf("Login failed. Exiting...\n");
        main();
    }

    return 0;
}

void displayUserTypeMenu(UserTypeOption menu[], int numOptions) {
    system("cls");
    //printf("\n===========================\n");
    printf("\t\t\t\t\t\t\tMain menu\n");
    printf("\t\t\t\t===============================\n");
    for (int i = 0; i < numOptions; i++) {
        printf("\t\t\t\t%d. %s\n", menu[i].userTypeCode, menu[i].userDescription);
    }
    printf("\t\t\t\t===============================\n");
}

void displayMenu(int userType) {
    switch (userType) {
        case 1:
            displayLecturerMenu();
            break;
        case 2:
            displayStudentMenu();
            break;
        case 3:
            displayAdminMenu();
            break;
        case 4:
            displaySysAdminMenu();
            break;
        default:
            printf("\nInvalid user type code. Please try again.\n");
            break;
    }
}

void displayStudentMenu() {
    int choice9;
    //int studentCount = 0;
    //int courseCount = 0;
    //int lecturerCount = 0;
    //int gradeCount = 0;
    //Student students[200];
    //Course courses[50];
    //Grades grades[200];
    //readCourseInfomation(courses, &courseCount);
    //readgrades(grades, &gradeCount);
    do {
        system("cls");
        printf("\n===========================\n");
        printf("          Student Menu\n");
        printf("===========================\n");
        printf("1. View Personal Details\n");
        printf("2. Update Personal Details\n");
        printf("3. View Enrolled Courses\n");
        printf("4. View Grades and CGPA\n");
        printf("5. View Attendance\n");
        printf("6. Main menu\n");
        printf("7. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice9);
        getchar();

        switch (choice9) {
            case 1:
                student_view();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 2:
                printf("*************************************************\n");
                printf("Enter your Student ID to update details:\n");
                updateStuInfo();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 3:
                viewEnrolledCourses();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 4:
                //("Enter Student ID: ");
                //scanf("%d", &studentID);
                //getchar();
                //getchar(); // Consume the newline character left in the input buffer
                //iewGrades(students, studentCount, courses, courseCount, grades, gradeCount, studentID);
               
                //viewGrades(grades, gradeCount, courses, courseCount);
                //viewGradesReport(grades, gradeCount);
                viewGrades();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 5:
                retrieveAttendanceInfoforstudent("attendance_record.txt");
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 6:
                main();
                break;
            case 7:
                exit(1);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice9 != 6 && choice9 != 7);
}


void displayAdminMenu() {
    int choice,choice1,choice2;
    do{
    system("cls");
    printf("\n===========================\n");
    printf("  Programme Administrator Menu\n");
    printf("===========================\n");
    printf("1. View Student Profiles\n");
    printf("2. View course information.\n");
    printf("3. Update course information.\n");
    printf("4. Delete a course.\n");
    printf("5. Assign Course to student.\n");
    printf("6. Remove Course from student.\n");
    printf("7. Add a new Courses\n");
    printf("8. Main menu\n");
    printf("9. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

        switch (choice) {
            case 1:
                    printf("1.View all Students Information.\n");
                    printf("2.Retrieve Specific Student Information.\n");
                    scanf("%d",&choice2);
                    getchar();
                if (choice2 == 1)
                {
                    student_view();
                    printf("\n\nPress Enter to continue...");
                    getchar(); // Wait for Enter key
                }else if(choice2 == 2){
                    Retrieve_Student_Info();
                    printf("\n\nPress Enter to continue...");
                    getchar(); // Wait for Enter key
                    getchar();
                }else
                {
                    printf("Choose either 1 or 2\n");
                }

                break;
            case 2:
                readCourseInfo1();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
            case 3:
                readCourseInfo1();
                updateCourseInfo();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 4:
                deleteCourseInfo();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 5:
                AssignCourse();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                displayAdminMenu();
            case 6:
                RemoveCourse();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                displayAdminMenu();
            case 7:
                addCourseDetails();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
            case 8:
                main();
            case 9:
                exit(1);
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 5 && choice != 6);
    }


void displayLecturerMenu() {
    int choice;
    do{
    system("cls");
    printf("\n===========================\n");
    printf("        Lecturer Menu\n");
    printf("===========================\n");
    printf("1. Manage Student Attendance\n");
    printf("2. Manage Course Marks\n");
    printf("3. Main menu\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

        switch (choice) {
            case 1:
                attendace();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 2:
                marks();
                printf("\n\nPress Enter to continue...");
                getchar(); // Wait for Enter key
                break;
            case 3:
                main();
                break;
            case 4:
                exit(1);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (choice != 6 && choice != 7);
}


void displaySysAdminMenu() {
    int choice4,choice5;
    do{
    system("cls");
    printf("\n=====================================\n");
    printf("  System Administrator Menu\n");
    printf("==========================================\n");
    printf("1. Register and Manage users\n");
    printf("2. Define Grading System\n");
    printf("3. Generate Performance Reports\n");
    printf("4. Main menu\n");
    printf("5. Logout\n");
    printf("=======================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice4);
    getchar();
    switch(choice4){

    case 1:
        printf("=======================================\n");
        printf("1.Manage Students.\n");
        printf("2.Manage program administrators.\n");
        printf("3.Manage Lecturer's.\n");
        printf("=======================================\n");

        printf("\nEnter choice:");
        scanf("%d",&choice5);
        getchar();
        if (choice5 == 1){
            managestudents();
            printf("\n\nPress Enter to continue...");
            getchar(); // Wait for Enter key
        }
        else if(choice5 == 2){
            manageprogrameadmin();
            printf("\n\nPress Enter to continue...");
            getchar(); // Wait for Enter key
            getchar();
        }
        else if (choice5== 3){
            managelecturer();
            printf("\n\nPress Enter to continue...");
            getchar(); // Wait for Enter key
        }
        else{
            printf("Enter correct option\n");
        }
        break;

    case 2:
        managegrading();
        printf("\n\nPress Enter to continue...");
        getchar(); // Wait for Enter key
        break;
    case 3:
        generatereports();
        printf("\n\nPress Enter to continue...");
        getchar(); // Wait for Enter key
        break;
    case 4:
        main();
        break;
    case 5:
        exit(1);
        break;
    default:
        printf("Invalid choice! Please try again.\n");
        break;
    }
  }while(choice4 != 4 && choice4 != 5);
}
