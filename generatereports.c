
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX_STUDENTS 100
#define MAX_COURSES 100 // Define the maximum number of courses
#define MAX_GRADES 5
#define MAX_ATTENDANCE 20

typedef struct {
    int id;
    char name[50];
    char lastName[50];
    int age;
    char gender[10];
    char nationality[20];
    char email[50];
    char address[100];
    char password;
    int semster;
    char courseid;
    float grades[MAX_GRADES];
    int attendance[MAX_ATTENDANCE];
} Student;

typedef struct {
    int  courseID;
    char courseName[50];
    char courseType[50];
    char lecturerName[50];
    int lecturerID;
    float duration;
} Course;

// Function declarations
float calculateAttendancePercentage(int attendance[], int numClasses);
float calculateCGPA(float grades[], int numCourses);
char* evaluateOverallPerformance(float cgpa);

//calculate average grade for whole class
float calculateAverageLecturerGrade(int lecturerID, Student students[], int numStudents, int courseID) {
    float totalGrade = 0;
    int countStudents = 0;
    for (int i = 0; i < numStudents; i++) {
        if (students[i].grades[courseID] >= 0) {
            totalGrade += students[i].grades[courseID];
            countStudents++;
        }
    }
    return countStudents > 0 ? totalGrade / countStudents : 0;
}
// average performaceFeedback
char* averagePerformaceFeedback()
{

}

// Dummy implementations for functions
float calculateAttendancePercentage(int attendance[], int numClasses) {
    // Dummy implementation - Calculate attendance percentage
    return 85.5; // Just a placeholder value
}
// Function to calculate attendance percentage
/*
float calculateAttendancePercentage(int attendance[], int maxAttendance) {
    int totalDays = maxAttendance;
    int presentDays = 0;
    for (int i = 0; i < maxAttendance; i++) {
        if (attendance[i] == 1) {
            presentDays++;
        }
    }
    return (float) presentDays / totalDays * 100;
}
*/
float calculateCGPA(float grades[], int numCourses) {
    // Dummy implementation - Calculate CGPA
    return 3.75; // Just a placeholder value
}

char* evaluateOverallPerformance(float cgpa) {
    // Dummy implementation - Evaluate overall performance
    if (cgpa >= 3.5) {
        return "Excellent";
    } else if (cgpa >= 3.0) {
        return "Good";
    } else if (cgpa >= 2.5) {
        return "Average";
    } else {
        return "Below Average";
    }
}
// date and time
void printCurrentDate() {
    time_t currentTime;
    struct tm *localTime;

    time(&currentTime);
    localTime = localtime(&currentTime);

    printf("%02d/%02d/%d\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
}

void readCoursesFromFile(const char* filename, Course courses[], int* numCourses, int maxCourses) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening %s\n", filename);
        exit(1); // Exit the program if file opening fails
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip the header line

    int index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, " | %d | %49[^|] | %49[^|] | %49[^|] | %f",
                   &courses[index].courseID, courses[index].courseName, courses[index].courseType,
                   courses[index].lecturerName, &courses[index].duration) == 5) {
            index++;
            if (index >= maxCourses) {
                printf("Maximum number of courses reached. Increase maxCourses if needed.\n");
                break;
            }
        } else {
            printf("Error reading data from line: %s\n", line);
            continue; // Skip to the next line
        }
    }

    *numCourses = index; // Update the number of courses read
    fclose(file);
}


void readGradesFromFile(const char* filename, Student students[], int numStudents) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening %s\n", filename);
        exit(1);
    }

    char line[256];
    fgets(line, sizeof(line), fp); // Skip the header line
    fgets(line, sizeof(line), fp);

    while (fgets(line, sizeof(line), fp) != NULL) {
        int id;
        float grades[MAX_GRADES];

        // format specifiers for reading data
        if (sscanf(line, "%d | %f | %f | %f | %f | %f", &id, &grades[0], &grades[1], &grades[2], &grades[3], &grades[4]) == 6) {
            for (int i = 0; i < numStudents; i++) {
                if (students[i].id == id) {
                    // Copy grades to the corresponding student's grades array
                    for (int j = 0; j < MAX_GRADES; j++) {
                        students[i].grades[j] = grades[j];
                    }
                    break;
                }
            }
        } else {
            printf("Error reading grade data from file %s\n", filename);
            exit(1);
        }
    }

    fclose(fp);
}


void readStudentsFromFile(const char* filename, Student students[], int* numStudents) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }




    char line[256];
    fgets(line, sizeof(line), file); // Skip the header line
    fgets(line, sizeof(line), file);
    int index = 0;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d | %d | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n] ",
                   &students[index].id, &students[index].password, students[index].name,
                   students[index].lastName, &students[index].age, students[index].gender,
                   students[index].nationality, students[index].email, students[index].address,&students[index].courseid) == 10) {
            index++;
            if (index >= MAX_STUDENTS) {
                printf("Maximum number of students reached. Increase MAX_STUDENTS if needed.\n");
                break;
            }
        } else {
            printf("Error reading data from line: %s\n", line);
            continue; // Skip to the next line
        }
    }

    *numStudents = index;
    fclose(file);
}


int num = 0,num1 = 3.0;
void generatePerformanceReport(Student students[], int numStudents, Course courses[], int numCourses, int semester, int studentID, int courseID, int viewAll) {
    printf("\n============================= Performance Report =====================================================\n");

    // Option 1: View all students' performance
    if (semester == 0 && studentID == 0 && courseID == 0 && viewAll == 1) {
        for (int i = 0; i < numStudents; i++) {
            printf("Name: %s %s\n", students[i].name, students[i].lastName);
            printf("Semester: %d\n", students[i].semster);
            for (int j = 0; j < numCourses; j++) {
                float grade = students[i].grades[j];
                if (grade >= 0) {
                    printf("Grades for Course %d (%s): %.2f\n", courses[j].courseID, courses[j].courseName, grade);
                }
            }
            float attendancePercentage = calculateAttendancePercentage(students[i].attendance, MAX_ATTENDANCE);
            float cgpa = calculateCGPA(students[i].grades, numCourses);
            char* performance = evaluateOverallPerformance(cgpa);
            printf("Attendance Percentage: %.2f%%\n", attendancePercentage);
            printf("CGPA: %.2f\n", cgpa);
            printf("Overall Performance: %s\n", performance);
            printf("Date: ");
            printCurrentDate();
            printf("Signature: _______________________\n\n");
        }
    }

    // Option 2: View specific student's performance
    else if (studentID != 0) {
        for (int i = 0; i < numStudents; i++) {
            if (students[i].id == studentID) {
                printf("Name: %s %s\n", students[i].name, students[i].lastName);
                printf("Semester: %d\n", students[i].semster);
                for (int j = 0; j < numCourses; j++) {
                    float grade = students[i].grades[j];
                    if (grade >= 0) {
                        printf("Grades for Course %d (%s): %.2f\n", courses[j].courseID, courses[j].courseName, grade);
                    }
                }
                float attendancePercentage = calculateAttendancePercentage(students[i].attendance, MAX_ATTENDANCE);
                float cgpa = calculateCGPA(students[i].grades, numCourses);
                char* performance = evaluateOverallPerformance(cgpa);
                printf("Attendance Percentage: %.2f%%\n", attendancePercentage);
                printf("CGPA: %.2f\n", cgpa);
                printf("Overall Performance: %s\n", performance);
                printf("Date: ");
                printCurrentDate();
                printf("Signature: _______________________\n\n");
                break;  // Found the specific student, so exit the loop
            }
        }
    }

    // Option 3: View overall class performance for a specific semester
    else if (semester != 0) {
        float totalGrades[MAX_COURSES] = {0}; // Initialize total grades for each course
        int countStudents = 0; // Count the number of students in the specified semester
        for (int i = 0; i < numStudents; i++) {
            if (students[i].semster == semester) {
                countStudents++;
                for (int j = 0; j < numCourses; j++) {
                    float grade = students[i].grades[j];
                    if (grade >= 0) {
                        totalGrades[j] += grade;
                    }
                }
            }
        }
        if (countStudents > 0) {
            printf("Semester: %d\n", semester);
            for (int j = 0; j < numCourses; j++) {
                float avgGrade = totalGrades[j] / countStudents;
                printf("Course ID: %d\n", courses[j].courseID);
                printf("Course Name: %s\n", courses[j].courseName);
                printf("Number of Students Taking Course: %d\n", countStudents);
                printf("Average Grade: %.2f\n", avgGrade);
                float attendancePercentage = calculateAttendancePercentage(students[j].attendance, MAX_ATTENDANCE);
                printf("Average Attendance Percentage: %.2f%%\n", attendancePercentage);
                printf("Lecturers Teaching This Course:\n");
                for (int k = 0; k < numCourses; k++) {
                    if (courses[k].courseID == courses[j].courseID) {
                        printf("- %s: ", courses[k].lecturerName);
                        // Here you can calculate and print the average grade for each lecturer
                        // You can use a similar approach as calculating the average grade for the course
                        printf("average grade for his class: %.2f\n", calculateAverageLecturerGrade(courses[k].lecturerID, students, numStudents, courses[k].courseID));
                    }
                }
                printf("\n");
            }
        } else {
            printf("No students found in semester %d.\n", semester);
        }
    }

    // Option 4: View overall performance for a specific course and its lecturers

    else if (courseID != 0) {
        printf("==================Overall class performance for specific lecturer==========================\n");
        printf("Course ID: %d\n", courseID);

        int courseIndex = -1;
        for (int i = 0; i < numCourses; i++) {
            if (courses[i].courseID == courseID) {
                courseIndex = i;
                break;
            }
        }

        if (courseIndex == -1) {
            printf("Course not found.\n");
            return;
        }

        printf("Course Name: %s\n", courses[courseIndex].courseName);

        for (int j = 0; j < numCourses; j++) {
            if (courses[j].courseID == courseID) {
                printf("Lecturer: %s\n", courses[j].lecturerName);

                int countStudents = 0;
                float totalGrade = 0;

                for (int k = 0; k < numStudents; k++) {
                    if (courses[k].courseID == courseID && students[k].semster == semester) {
                        float grade = students[k].grades[courseIndex];
                        if (grade >= 0) {
                            countStudents++;
                            totalGrade += grade;
                        }
                    }
                }

                if (countStudents > 0) {
                    float avgGrade = totalGrade / countStudents;
                    printf("Number of Students Taking Course: %d\n", countStudents);
                    printf("Semester: %d\n", semester);
                    printf("Average Grade for whole class: %.2f\n", avgGrade);
                    //based on average grade
                    //printf("Overall Performance: %s\n", performance);
                    float attendancePercentage = calculateAttendancePercentage(students[j].attendance, MAX_ATTENDANCE);
                    printf("Average Attendance Percentage for whole class: %.2f%%\n", attendancePercentage);
                } else {
                    printf("No students taking this course with this lecturer.\n");
                }

                printf("\n");
            }
        }
    }
  printf("============================================================================================\n");
}






void generateAttendanceReport(Student students[], int numStudents) {
    printf("\n===== Attendance Report =====\n");

    for (int i = 0; i < numStudents; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Name: %s %s\n", students[i].name, students[i].lastName);
        printf("Semester: %d\n", students[i].semster);
        printf("Attendance: ");
        for (int j = 0; j < MAX_ATTENDANCE; j++) {
            printf("%d ", students[i].attendance[j]);
        }
        printf("\n\n");
    }

    printf("==============================\n");
}

/*void generateGradeReport(Student students[], int numStudents) {
    printf("\n===== Grade Report =====\n");

    for (int i = 0; i < numStudents; i++) {
        printf("Student ID: %d\n", students[i].id);
        printf("Name: %s %s\n", students[i].name, students[i].lastName);
        printf("Class: %d\n", students[i].class);
        printf("Grades: ");
        for (int j = 0; j < MAX_GRADES; j++) {
            printf("%.2f ", students[i].grades[j]);
        }
        printf("\n\n");
    }

    printf("==============================\n");
}*/

void generateGradeReport(Student students[], int numStudents) {
    printf("\n===== Grade Report =====\n");

    int choice;
    printf("1. Generate overall grade report\n");
    printf("2. Check individual student's grades\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Generate overall grade report for all students
            for (int i = 0; i < numStudents; i++) {
                printf("Student ID: %d\n", students[i].id);
                printf("Name: %s %s\n", students[i].name, students[i].lastName);
                printf("Class: %d\n", students[i].semster);
                printf("Grades: ");
                for (int j = 0; j < MAX_GRADES; j++) {
                    printf("%.2f ", students[i].grades[j]);
                }
                printf("\n\n");
            }
            break;
        case 2:
            // Check individual student's grades
            {
                int studentId;
                printf("Enter student ID to check grades: ");
                scanf("%d", &studentId);

                int found = 0;
                for (int i = 0; i < numStudents; i++) {
                    if (students[i].id == studentId) {
                        found = 1;
                        printf("\n===== Grades for Student ID: %d =====\n", studentId);
                        printf("Name: %s %s\n", students[i].name, students[i].lastName);
                        printf("Class: %d\n", students[i].semster);
                        printf("Grades: ");
                        for (int j = 0; j < MAX_GRADES; j++) {
                            printf("%.2f ", students[i].grades[j]);
                        }
                        printf("\n");
                        break;
                    }
                }

                if (!found) {
                    printf("Student with ID %d not found.\n", studentId);
                }
            }
            break;
        default:
            printf("Invalid choice! Please enter a valid option.\n");
            break;
    }

    printf("==============================\n");
}


void transferCourse(int studentId, int courseId, int newSemester, Student students[]) {
    for (int i = 0; i < MAX_STUDENTS; i++) {
        if (students[i].id == studentId) {
            students[i].semster = newSemester;
            break;
        }
    }
}

void transferUniversity(int studentId, int universityId, Student students[], int* numStudentsPtr) {
    for (int i = 0; i < *numStudentsPtr; i++) {
        if (students[i].id == studentId) {
            // Shift the remaining students to fill the gap
            for (int j = i; j < *numStudentsPtr - 1; j++) {
                students[j] = students[j + 1];
            }
            // Clear the values of the last student
            students[*numStudentsPtr - 1] = (Student){0};  // Assuming Student struct has default initializer
            (*numStudentsPtr)--;
            break;
        }
    }
}

void saveTransferredStudents(const char* filename, Student students[], int numStudents) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error opening %s for writing\n", filename);
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(fp, "%d,%s,%d\n", students[i].id, students[i].name, students[i].semster);
    }

    fclose(fp);
}

void displayMenu() {
    printf("\n===== Student Information System Menu =====\n");
    printf("1. Generate Performance Report\n");
    printf("2. Generate Attendance Report\n");
    printf("3. Generate Grade Report\n");
    printf("4. Transfer Course\n");
    printf("5. Transfer to Another University\n");
    printf("6. Save Transferred Students\n");
    printf("7. Exit\n");
    printf("===========================================\n");
    printf("Enter your choice: ");
}



int main() {
    Course courses[MAX_COURSES];
    int numCourses = 0; // Initially zero courses
    int maxCourses = MAX_COURSES; // Define the maximum number of courses to read
    Student students[MAX_STUDENTS];
    int numStudents = 0; // Initially zero students
    readStudentsFromFile("StuInfo.txt", students, &numStudents);
    readGradesFromFile("grades.txt", students, numStudents);
    readCoursesFromFile("courseInfo.txt", courses, &numCourses, maxCourses);

    int choice;
    do {
        displayMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');  // Clear input buffer
            continue;  // Skip the rest of the loop body
        }

        switch (choice) {
            case 1: {
                int semester, studentID, courseID;
                int viewAll, option;
                printf("1: View all students' performance\n");
                printf("2: View specific student's performance\n");
                printf("3: View overall class performance for a specific semester\n");
                printf("4: View overall performance for a specific course and its lecturers\n");
                printf("Enter option: ");
                scanf("%d", &option);

                // Error handling for invalid option
                if (option < 1 || option > 4) {
                    printf("Invalid option\n");
                    break;  // Exit the case
                }

                if (option == 1) {
                    viewAll = 1; // Set viewAll to 1 for viewing all students
                    semester = 0; // Set semester to 0 for all semesters
                    studentID = 0; // Set studentID to 0 for all students
                    courseID = 0; // Set courseID to 0 for all courses
                } else if (option == 2) {
                    printf("Enter student ID: ");
                    scanf("%d", &studentID);
                    //getchar(); // Consume newline character from the input buffer
                    viewAll = 0; // Set viewAll to 0 for viewing a specific student
                    semester = 0; // Set semester to 0 for all semesters
                    courseID = 0; // Set courseID to 0 for all courses
                } else if (option == 3) {
                    printf("Enter semester (0 for all): ");
                    scanf("%d", &semester);
                    getchar(); // Consume newline character from the input buffer
                    viewAll = 0; // Set viewAll to 0 for viewing specific semester
                    studentID = 0; // Set studentID to 0 for all students
                    courseID = 0; // Set courseID to 0 for all courses
                } else if (option == 4) {
                    printf("Enter course ID: ");
                    scanf("%d", &courseID);
                    viewAll = 0; // Set viewAll to 0 for viewing a specific course
                    semester = 0; // Set semester to 0 for all semesters
                    studentID = 0; // Set studentID to 0 for all students
                }

                generatePerformanceReport(students, numStudents, courses, numCourses, semester, studentID, courseID, viewAll);
                break;
            }

            case 2:
                generateAttendanceReport(students, numStudents);
                break;

            case 3:
                generateGradeReport(students, numStudents);
                break;

            case 4: {
                int studentId, courseId, newSemester;
                printf("Enter student ID, course ID, and new semester: ");
                if (scanf("%d %d %d", &studentId, &courseId, &newSemester) != 3) {
                    printf("Invalid input. Please enter three numbers.\n");
                    while (getchar() != '\n');  // Clear input buffer
                    break;  // Skip transferring course
                }
                transferCourse(studentId, courseId, newSemester, students);
                printf("Transferring Course...\n");
                break;
            }

            case 5: {
                int studentId, universityId;
                printf("Enter student ID and university ID: ");
                if (scanf("%d %d", &studentId, &universityId) != 2) {
                    printf("Invalid input. Please enter two numbers.\n");
                    while (getchar() != '\n');  // Clear input buffer
                    break;  // Skip transferring to university
                }
                transferUniversity(studentId, universityId, students, &numStudents);
                printf("Transferring to Another University...\n");
                break;
            }

            case 6:
                saveTransferredStudents("transferred_students.txt", students, numStudents);
                printf("Transferred students saved to file.\n");
                break;

            case 7:
                printf("Exiting the program...\n");
                break;

            default:
                printf("Invalid choice! Please enter a valid option.\n");
                break;
        }

        // Clear input buffer before next iteration
        while (getchar() != '\n');


    } while (choice != 7);

    return 0;
}

