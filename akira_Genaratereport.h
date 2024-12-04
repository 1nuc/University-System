#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <stdbool.h>
#define GE_ID_WIDTH 10
#define GE_PASS_WIDTH 15
#define GE_NAME_WIDTH 15
#define GE_LAST_NAME_WIDTH 15
#define GE_AGE_WIDTH 5
#define GE_GENDER_WIDTH 8
#define GE_NATIONALITY_WIDTH 15
#define GE_EMAIL_WIDTH 25
#define GE_ADDRESS_WIDTH 25
#define GE_COURSE_WIDTH 15
#define GE_COURSEID_WIDTH 10
#define GE_COURSENAME_WIDTH 50
#define GE_COURSETYPE_WIDTH 20
#define GE_LECTURERNAME_WIDTH 50
#define GE_DURATION_WIDTH 10
#define attendace_Duration 100
#define MAX_COURSES_studnet 5
#define MAX_ATTENDANCE 100




typedef struct {
    int courseId;
    float assessment1;
    float assessment2;
    float assessment3;
} assessmets;
typedef struct {
    char name[50];
    char Last_Name[50];
    int age;
    int Student_Id;
    char Password[50];
    char Gender[50];
    char Nationality[50];
    char email[50];
    char address[50];
    int course[10]; // Assuming a maximum of 10 courses per student
} Student;


typedef struct {
    char courseName[50];
    int studentID;
    float percentage;
    int totalClasses;
    int attendedClasses;
} Attendance;

typedef struct {
    int studentID;
    float assessment1;
    float assessment2;
    float assessment3;
    int courseID;
    float total;
    float GPA;
} Grades;

typedef struct {
    char name[50];
    int age;
    int id;
    char password[GE_PASS_WIDTH];
} Lecturer_struct;

typedef struct {
    int courseID;
    char courseName[100];
    char courseType[20];
    char lecturerName[100];
    float duration;
} Course_struct;


Student students[200];
Course_struct courses[50];
Lecturer_struct lecturers[50];
assessmets courses_s[MAX_COURSES_studnet];
Grades grades[200];
int studentCount = 0;
int courseCount = 0;
int lecturerCount = 0;
int gradeCount = 0;

void file_format_view(char *format, size_t length) {
    if (format == NULL) return;
    size_t len = strlen(format);
    if (len > 0 && format[len - 1] == '\n') {
        format[len - 1] = '\0';
        len--;
    }
    if (len >= length - 1) {
        format[length - 1] = '\0';
    }
}


void readCourseInfo_opn_reading(assessmets courses[], int* numCourses) {
    FILE* fp = fopen("courseweightage.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp); // Skip the header line

    while (fgets(line, sizeof(line), fp) != NULL && *numCourses < MAX_COURSES_studnet) {
        int courseId;
        float a1, a2, a3;

        if (sscanf(line, "%d | %f | %f | %f", &courseId, &a1, &a2, &a3) == 4) {
            courses[*numCourses].courseId = courseId;
            courses[*numCourses].assessment1 = a1;
            courses[*numCourses].assessment2 = a2;
            courses[*numCourses].assessment3 = a3;
            (*numCourses)++;
        } else {
            printf("Error reading course data from file\n");
            continue;  // Skip to the next line if there's a formatting issue
        }
    }

    fclose(fp);
}

void printCourseReport(assessmets courses[], int numCourses) {
    printf("--------------------------------------------------\n");
    printf("| Course ID | Assessment 1 | Assessment 2 | Assessment 3 |\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < numCourses; i++) {
        printf("| %-9d | %-12.2f | %-12.2f | %-12.2f |\n",
               courses[i].courseId, courses[i].assessment1,
               courses[i].assessment2, courses[i].assessment3);
    }

    printf("--------------------------------------------------\n");
}

/*void student_viewing(Student students[], int *studentCount) {
    FILE* file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        file_format_view(line, sizeof(line));
        sscanf(line, "%d | %15[^|] | %20[^|] | %20[^|] | %5d | %10[^|] | %13[^|] | %25[^|] | %25[^|] | %d",
        &students[*studentCount].Student_Id, students[*studentCount].Password, students[*studentCount].name,
        students[*studentCount].Last_Name, &students[*studentCount].age, students[*studentCount].Gender,
        students[*studentCount].Nationality, students[*studentCount].email, students[*studentCount].address,
        &students[*studentCount].course);

        (*studentCount)++;
    }

    fclose(file);
}
*/
/*void student_viewing(Student students[], int *studentCount) {
    FILE* file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        // Tokenize the line to extract course IDs
        char *token = strtok(line, ", ");
        int courseIndex = 0;
        while (token != NULL && courseIndex < 10) {
            students[*studentCount].course[courseIndex++] = atoi(token);
            token = strtok(NULL, ", "); // Move to the next token
        }

        // Now sscanf the rest of the line to extract other student information
        sscanf(line, "%d | %49[^|] | %49[^|] | %d | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %49[^|] | %d",
               &students[*studentCount].Student_Id, students[*studentCount].name,
               students[*studentCount].Last_Name, &students[*studentCount].age,
               students[*studentCount].Password, students[*studentCount].Gender,
               students[*studentCount].Nationality, students[*studentCount].email,
               students[*studentCount].address, &students[*studentCount].course[0]); // Assuming course ID is the first one in the line

        (*studentCount)++;
    }

    fclose(file);
}*/
void student_viewing(Student students[], int *studentCount) {
    FILE* file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, "|"); // Tokenize the line using pipe symbol as delimiter
        int fieldIndex = 0;
        while (token != NULL && fieldIndex < 10) {
            switch (fieldIndex) {
                case 0:
                    students[*studentCount].Student_Id = atoi(token);
                    break;
                case 1:
                    strcpy(students[*studentCount].Password, token);
                    break;
                case 2:
                    strcpy(students[*studentCount].name, token);
                    break;
                case 3:
                    strcpy(students[*studentCount].Last_Name, token);
                    break;
                case 4:
                    students[*studentCount].age = atoi(token);
                    break;
                case 5:
                    strcpy(students[*studentCount].Gender, token);
                    break;
                case 6:
                    strcpy(students[*studentCount].Nationality, token);
                    break;
                case 7:
                    strcpy(students[*studentCount].email, token);
                    break;
                case 8:
                    strcpy(students[*studentCount].address, token);
                    break;
                case 9: {
                    char *courseToken = strtok(token, ", "); // Tokenize the Course field using commas and spaces
                    int courseIndex = 0;
                    while (courseToken != NULL && courseIndex < 10) {
                        students[*studentCount].course[courseIndex++] = atoi(courseToken); // Store each course ID in the student's course array
                        courseToken = strtok(NULL, ", "); // Move to the next course ID token
                    }
                    break;
                }
                default:
                    break;
            }
            fieldIndex++;
            token = strtok(NULL, "|"); // Move to the next field token
        }

        (*studentCount)++;
    }

    fclose(file);
}

void readCourseInfomation(Course_struct courses[], int *courseCount) {
    FILE* file = fopen("courseInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        file_format_view(line, sizeof(line));
        sscanf(line, "| %d | %99[^|] | %19[^|] | %99[^|] | %f |",
        &courses[*courseCount].courseID, courses[*courseCount].courseName, courses[*courseCount].courseType,
        courses[*courseCount].lecturerName, &courses[*courseCount].duration);

        (*courseCount)++;
    }

    fclose(file);
}

void lecturer_viewing(Lecturer_struct lecturers[], int *lecturerCount) {
    FILE* file = fopen("lecturer_info.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        file_format_view(line, sizeof(line));
        sscanf(line, "| %d | %49[^|] | %d | %99[^|] |",
        &lecturers[*lecturerCount].id, lecturers[*lecturerCount].name,
        &lecturers[*lecturerCount].age, lecturers[*lecturerCount].password);

        (*lecturerCount)++;
    }

    fclose(file);
}

void read_attendance_data(Attendance attendance[], int *attendanceCount) {
    FILE* file = fopen("attendance_record.txt", "r");
    if (file == NULL) {
        perror("Error opening the file");
        return;
    }

    printf("Reading attendance data from file...\n");

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line

    while (fgets(line, sizeof(line), file) && *attendanceCount < MAX_ATTENDANCE) {
        // Tokenize the line based on the '|' delimiter
        char *token = strtok(line, "|");
        if (token == NULL) {
            printf("Error parsing line: %s\n", line);
            continue;
        }

        // Extract and clean course name
        int len = strlen(token);
        if (len > 0 && token[len - 1] == '\n') {
            token[len - 1] = '\0'; // Remove newline character
        }
        strncpy(attendance[*attendanceCount].courseName, token, sizeof(attendance[*attendanceCount].courseName) - 1);
        attendance[*attendanceCount].courseName[sizeof(attendance[*attendanceCount].courseName) - 1] = '\0'; // Ensure null-terminated

        // Extract student ID
        token = strtok(NULL, "|");
        if (token == NULL) {
            printf("Error parsing line: %s\n", line);
            continue;
        }
        sscanf(token, "%d", &attendance[*attendanceCount].studentID);

        // Extract percentage
        token = strtok(NULL, "|");
        if (token == NULL) {
            printf("Error parsing line: %s\n", line);
            continue;
        }
        sscanf(token, "%f", &attendance[*attendanceCount].percentage);

        // Extract total classes and attended classes
        token = strtok(NULL, "|");
        if (token == NULL) {
            printf("Error parsing line: %s\n", line);
            continue;
        }
        sscanf(token, "%d/%d", &attendance[*attendanceCount].attendedClasses, &attendance[*attendanceCount].totalClasses);

        (*attendanceCount)++;
    }

    fclose(file);
}


int readgrades(Grades grades[], int *gradeCount) {
    FILE* file = fopen("grades.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[250];
    fgets(line, sizeof(line), file); // Read and discard the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        file_format_view(line, sizeof(line));
        sscanf(line, "%d | %f | %f | %f | %d | %f | %f",
        &grades[*gradeCount].studentID,
        &grades[*gradeCount].assessment1,
        &grades[*gradeCount].assessment2,
        &grades[*gradeCount].assessment3,
        &grades[*gradeCount].courseID,
        &grades[*gradeCount].total,
        &grades[*gradeCount].GPA);

        (*gradeCount)++;
    }

    fclose(file);
    return 0;
}

/*void ViewEnrolledCourse() {
    // Open StuInfo.txt file for reading
    FILE *stuFile = fopen("StuInfo.txt", "r");
    if (stuFile == NULL) {
        printf("Error opening the StuInfo.txt file\n");
        return;
    }

    // Open courseInfo.txt file for reading
    FILE *courseFile = fopen("courseInfo.txt", "r");
    if (courseFile == NULL) {
        printf("Error opening the courseInfo.txt file\n");
        fclose(stuFile);
        return;
    }

    char line[250];
    int studentID;
    char *courseToken;

    // Read each line from the StuInfo.txt file
    while (fgets(line, sizeof(line), stuFile)) {
        // Extract student ID and course information from the line
        sscanf(line, "%d | %*[^|] | %*[^|] | %*[^|] | %*d | %*[^|] | %*[^|] | %*[^|] | %*[^|] | %[^\n]", &studentID, line);

        // Tokenize the course information to extract individual course IDs
        courseToken = strtok(line, ", ");
        while (courseToken != NULL) {
            int courseId = atoi(courseToken);

            // Search for the course information in courseInfo.txt
            rewind(courseFile); // Reset the file pointer to the beginning
            char courseLine[250];
            while (fgets(courseLine, sizeof(courseLine), courseFile)) {
                int courseIdFromFile;
                if (sscanf(courseLine, "| %d", &courseIdFromFile) == 1 && courseIdFromFile == courseId) {
                    // Print the course information
                    printf("Course ID: %d\n", courseId);
                    printf("%s", courseLine); // Print the entire line from courseInfo.txt
                    break; // Stop searching for this course ID
                }
            }

            courseToken = strtok(NULL, ", "); // Move to the next course ID
        }
    }

    // Close the files
    fclose(stuFile);
    fclose(courseFile);
}*/





/*void viewEnrolledCourses() {
    student_viewing(students, &studentCount);
    readCourseInfomation(courses, &courseCount);
    int studentid;
    printf("Enter Student ID: ");
    scanf("%d", &studentid);
    getchar(); // Clear the input buffer
    int studentFound = 0; // Flag to track if the student is found
    printf("Enrolled Courses for Student ID %d:\n", studentid);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].Student_Id == studentid) {
            studentFound = 1;
            for (int j = 0; j < courseCount; j++) {
                if (*students[i].course == courses[j].courseID) {
                    printf("Course ID: %d\n", courses[j].courseID);
                    printf("Course Name: %s\n", courses[j].courseName);
                    printf("Course Type: %s\n", courses[j].courseType);
                    printf("Lecturer Name: %s\n", courses[j].lecturerName);
                    printf("Duration: %.2f hours\n", courses[j].duration);
                    printf("\n");
                }
            }
            // No break here to display all enrolled courses for the student
        }
    }
    if (!studentFound) {
        printf("Student ID %d not found.\n", studentid);
    } else {
        printf("No enrolled courses found for Student ID %d.\n", studentid);
    }
}
*/
void viewEnrolledCourses() {
    int studentid;
    student_viewing(students, &studentCount);
    readCourseInfomation(courses, &courseCount);
    printf("Enter Student ID: ");
    scanf("%d", &studentid);
    getchar(); // Clear the input buffer
    int studentFound = 0; // Flag to track if the student is found
    printf("Enrolled Courses for Student ID %d:\n", studentid);
    for (int i = 0; i < studentCount; i++) {
        if (students[i].Student_Id == studentid) {
            studentFound = 1;
            for (int courseIndex = 0; courseIndex < 10; courseIndex++) {
                int enrolledCourseID = students[i].course[courseIndex];
                if (enrolledCourseID != 0) { // Assuming 0 is not a valid course ID
                    for (int j = 0; j < courseCount; j++) {
                        if (enrolledCourseID == courses[j].courseID) {
                            printf("Course ID: %d\n", courses[j].courseID);
                            printf("Course Name: %s\n", courses[j].courseName);
                            printf("Course Type: %s\n", courses[j].courseType);
                            printf("Lecturer Name: %s\n", courses[j].lecturerName);
                            printf("Duration: %.2f hours\n", courses[j].duration);
                            printf("\n");
                        }
                    }
                }
            }
            break; // Exit the loop after finding the student
        }
    }
    if (!studentFound) {
        printf("Student ID %d not found.\n", studentid);
    }
}




void viewGrades() {
    int studentID;
    student_viewing(students, &studentCount);
    readCourseInfomation(courses, &courseCount);
    readgrades(grades, &gradeCount);
    printf("Enter the student ID: ");
    scanf("%d", &studentID);
    getchar();
    printf("Grades for Student ID %d:\n", studentID);
    int found = 0; // Flag to track if grades are found for the student ID

    for (int i = 0; i < gradeCount; i++) {
        if (grades[i].studentID == studentID) {
            printf("ID matched");
            found = 1; // Set found flag to true
            printf("\n==============================\n");
            printf("Course ID: %d\n", grades[i].courseID);

            // Search for the course information in the courses array
            for (int j = 0; j < courseCount; j++) {
                if (courses[j].courseID == grades[i].courseID) {
                    printf("Course Name: %s\n", courses[j].courseName);
                    printf("Course Type: %s\n", courses[j].courseType);
                    printf("Lecturer Name: %s\n", courses[j].lecturerName);
                    printf("Duration: %.2f hours\n", courses[j].duration);
                    printf("Assessment 1: %.2f\n", grades[i].assessment1);
                    printf("Assessment 2: %.2f\n", grades[i].assessment2);
                    printf("Assessment 3: %.2f\n", grades[i].assessment3);
                    printf("Total: %.2f\n", grades[i].total);
                    printf("GPA: %.2f\n", grades[i].GPA);
                    printf("==============================\n\n");
                    break; // Stop searching for this course ID
                }
            }
        }
    }

    if (!found) {
        printf("No grades found for Student ID %d\n", studentID);
    }
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

void viewOverallPerformance(const Student students[], int studentCount, const Grades grades[], int gradeCount) {
    readCourseInfomation(courses, &courseCount);
    printf("=== Overall class Performance ===\n");
    for (int i = 0; i < studentCount; i++) {
        float cgpa = 0.0;
        int courseCount = 0;
        for (int j = 0; j < gradeCount; j++) {
            /*if (grades[j].studentID == students[i].Student_Id) {
                cgpa += grades[j].GPA;
                courseCount++;
            }*/
            cgpa += grades[j].GPA;
                courseCount++;
        }
        cgpa /= courseCount;
        for (int j = 0; j < courseCount; j++) {
                if (courses[j].courseID == grades[i].courseID) {
                //printf("\nCourse ID: %d\n", students[i].Student_Id);
                //printf("class Name: %s %s\n", students[i].name, students[i].Last_Name);
                printf("*********************************************************************\n\n");
                printf("Class Name: %s\n", courses[j].courseName);
                printf("Course Type: %s\n", courses[j].courseType);
                printf("Class Grade: %.2f GPA\n", cgpa);
                printf("Overall Performance: %s\n", evaluateOverallPerformance(cgpa));
                printf("*********************************************************************\n\n");
                }
        }
    }
    printf("==========================\n");
}

void viewAllStudentsPerformance(const Student students[], int studentCount, const Course_struct courses[], int courseCount, const Grades grades[], int gradeCount) {
    printf("===== All Students' Performance =====\n");
    for (int i = 0; i < studentCount; i++) {
        float totalGPA = 0.0;
        int totalCourses = 0;

        // Calculate overall GPA for each student
        for (int j = 0; j < gradeCount; j++) {
            if (grades[j].studentID == students[i].Student_Id) {
                totalGPA += grades[j].GPA;
                totalCourses++;
            }
        }
        float avgGPA = totalGPA / totalCourses;

        // Print student's performance
        printf("*********************************************************************\n\n");
        printf("\nStudent ID: %d\n", students[i].Student_Id);
        printf("Name: %s %s\n", students[i].name, students[i].Last_Name);
        printf("Overall GPA: %.2f\n", avgGPA);
        printf("Overall Performance: %s\n", evaluateOverallPerformance(avgGPA));
        printf("*********************************************************************\n\n");
        printf("\n");
    }
    printf("====================================\n");
}




void viewSpecificStudentPerformance(const Student students[], int studentCount, const Course_struct courses[], int courseCount, const Grades grades[], int gradeCount) {
    int studentID;
    printf("Enter student ID: ");
    scanf("%d", &studentID);
    getchar(); // Consume newline character

    // Search for the student by ID
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].Student_Id == studentID) {
            found = 1;
            printf("===== Specific Student's Performance =====\n");
            printf("Student ID: %d\n", students[i].Student_Id);
            printf("Name: %s %s\n", students[i].name, students[i].Last_Name);

            // Calculate and print the student's GPA
            float totalGPA = 0.0;
            int totalCourses = 0;
            for (int j = 0; j < gradeCount; j++) {
                if (grades[j].studentID == studentID) {
                    totalGPA += grades[j].GPA;
                    totalCourses++;
                }
            }
            float avgGPA = totalGPA / totalCourses;
            printf("Overall GPA: %.2f\n", avgGPA);
            printf("Overall Performance: %s\n", evaluateOverallPerformance(avgGPA));

            // Print individual course grades
            printf("\nCourse Grades:\n");
            for (int k = 0; k < gradeCount; k++) {
                if (grades[k].studentID == studentID) {
                    for (int m = 0; m < courseCount; m++) {
                        if (courses[m].courseID == grades[k].courseID) {
                            printf("Course ID: %d\n", courses[m].courseID);
                            printf("Course Name: %s\n", courses[m].courseName);
                            printf("Assessment 1: %.2f \n", grades[k].assessment1);
                            printf("Assessment 2: %.2f\n", grades[k].assessment2);
                            printf("Assessment 3: %.2f\n", grades[k].assessment3);
                            printf("Total: %.2f\n", grades[k].total);
                            printf("GPA: %.2f\n", grades[k].GPA);
                            printf("==============================\n");
                        }
                    }
                }
            }
            printf("\n");
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", studentID);
    }
}




void viewGradesReport(const Grades grades[], int gradeCount) {
    readCourseInfomation(courses, &courseCount);
    if (gradeCount == 0) {
        printf("No grades data available.\n");
        return;
    }

    printf("===== Grades Report =====\n");
    for (int i = 0; i < gradeCount; i++) {
        printf("\n==============================\n");
        printf("Student ID: %d\n", grades[i].studentID);
        printf("Course Name:%s\n",courses[i].courseName);
        printf("Assessment 1: %.2f\n", grades[i].assessment1);
        printf("Assessment 2: %.2f\n", grades[i].assessment2);
        printf("Assessment 3: %.2f\n", grades[i].assessment3);
        printf("Total: %.2f\n", grades[i].total);
        printf("GPA: %.2f\n", grades[i].GPA);
        printf("==============================\n\n");
    }
    printf("Total number of grades: %d\n", gradeCount);
    printf("==========================\n");
}


void viewLecturerPerformance(const Course_struct courses[], int courseCount, const Lecturer_struct lecturers[], int lecturerCount, const Student students[], int studentCount, const Grades grades[], int gradeCount) {
    printf("===== Lecturer Performance =====\n");
    for (int i = 0; i < courseCount; i++) {
        printf("Course Name: %s\n", courses[i].courseName);
        printf("Lecturer Name: %s\n", courses[i].lecturerName);

        // Calculate number of students in the class
        int studentsInClass = 0;
        for (int j = 0; j < studentCount; j++) {
            if (*students[j].course == courses[i].courseID) {
                studentsInClass++;
            }
        }
        printf("Number of Students in Class: %d\n", studentsInClass);

        // Add logic to calculate and print lecturer's performance metrics based on average CGPA of students
        float totalCGPA = 0.0;
        int courseStudentsCount = 0;
        for (int k = 0; k < gradeCount; k++) {
            if (grades[k].courseID == courses[i].courseID) {
                totalCGPA += grades[k].GPA;
                courseStudentsCount++;
            }
        }
        if (courseStudentsCount > 0) {
            float avgCGPA = totalCGPA / courseStudentsCount;
            printf("Average CGPA of Students in Class: %.2f\n", avgCGPA);
            printf("Lecturer Performance: %s\n", evaluateOverallPerformance(avgCGPA));
        } else {
            printf("No students enrolled in this class.\n");
        }
        // Include the date if available


        printf("\n");
    }
    printf("================================\n");
}
void viewAttendanceReport(const Attendance attendance[], int attendanceCount) {
    if (attendanceCount == 0) {
        printf("No attendance data available.\n");
        return;
    }

    printf("===== Attendance Report =====\n");
    for (int i = 0; i < attendanceCount; i++) {
        printf("\n==============================\n");
        printf("Course Name: %s\n", attendance[i].courseName);
        printf("Student ID: %d\n", attendance[i].studentID);
        printf("Percentage: %.2f%%\n", attendance[i].percentage);
        printf("Total Classes: %d\n", attendance[i].totalClasses);
        printf("==============================\n\n");
    }
    printf("Total number of attendance records: %d\n", attendanceCount);
    printf("==========================\n");
}




int generatereports() {
    //Student students[200];
    //Course_struct courses[50];
    //Lecturer_struct lecturers[50];
    //Grades grades[200];
    //int studentCount = 0;
    //int courseCount = 0;
    //int lecturerCount = 0;
    //int gradeCount = 0;
    int choice;
    //int studentID;
    //Attendance attendance[attendace_Duration];
    Attendance attendance[MAX_ATTENDANCE];
    int attendanceCount = 0;
    read_attendance_data(attendance, &attendanceCount);

    //read_attendance_data(attendance, &attendanceCount);
    //int attendanceCount = 0;
    //assessmets courses_s[MAX_COURSES_studnet];
    int numCourses = 0;

    // Read data into arrays
    student_viewing(students, &studentCount);
    readCourseInfomation(courses, &courseCount);
    lecturer_viewing(lecturers, &lecturerCount);
    readgrades(grades, &gradeCount);
    //read_attendance_data(attendance, &attendanceCount);

    do {
        printf("=================================================\n");
        printf("       === Main Menu ===\n");
        //printf("\t1. View Enrolled Courses\n");
        //printf("\t2. View Grades\n");
        printf("\t1. Generate Overall Performance\n");
        printf("\t2. Generate Specific Student Performance\n");
        printf("\t3. Generate Lecturer Performance\n");
        printf("\t4. Generate Attendance Report\n");
        printf("\t5. Generate Grades Report\n");
        printf("\t6. Generate assessment weightage Report\n");
        printf("\t7. Exit\n");
        printf("=================================================\n");
        printf("\tEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left in the input buffer

        switch (choice) {
            case 1:
                viewOverallPerformance(students, studentCount, grades, gradeCount);
                break;
            case 2:
                viewSpecificStudentPerformance(students, studentCount, courses, courseCount, grades, gradeCount);
                break;
            case 3:
                viewLecturerPerformance(courses, courseCount, lecturers, lecturerCount, students, studentCount, grades, gradeCount);
                break;
            case 4:
                viewAttendanceReport(attendance, attendanceCount);
                //viewAttendanceReport();
                break;
            case 5:
                viewGradesReport(grades, gradeCount);
                break;
            case 6:
                readCourseInfo_opn_reading(courses_s, &numCourses); // Load existing course data
                printCourseReport(courses_s, numCourses);
                break;
            case 7:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    } while (choice != 7);

    return 0;
}



