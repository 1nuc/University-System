#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_COURSES 5
#define ASSESSMENT_WIDTH 15
#define TOTAL_WIDTH 10
#define COURSE_ID_WIDTH 10

typedef struct {
    int studentId;
    float score1;
    float score2;
    float score3;
    float totals;  // Total for each course
    int courseId;
} StudentRecord;

typedef struct {
    int courseId;
    float assessment1;
    float assessment2;
    float assessment3;
} CourseWeightage;

float calculateGPA(float totalScore, float scale) {
    if (totalScore < 0 || scale <= 0) {
        printf("Error: Invalid input for calculating GPA\n");
        return -1.0; // Return a negative value to indicate error
    }

    // Calculate GPA based on the scale
    float gpa = (totalScore / scale) * 4.0;
    return gpa;
}

void SaveGradesInfo(StudentRecord record[], int numCourses, CourseWeightage courseWeightages[]) {
    FILE* file = fopen("grades.txt", "a"); // Open the file in append mode
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Check if file is empty
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        // Print header only if file is empty
        fprintf(file, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s\n",
                COURSE_ID_WIDTH, "Student ID", ASSESSMENT_WIDTH, "Assessment 1",
                ASSESSMENT_WIDTH, "Assessment 2", ASSESSMENT_WIDTH, "Assessment 3",
                COURSE_ID_WIDTH, "Course Id", TOTAL_WIDTH, "Total", TOTAL_WIDTH, "GPA");
        fprintf(file, "--------------------------------------------------------------------------------------------------\n");
    }

    for (int i = 0; i < numCourses; i++) {
        float totalScore = record[i].score1 + record[i].score2 + record[i].score3;
        float weightedTotal = (record[i].score1 * courseWeightages[i].assessment1 +
                               record[i].score2 * courseWeightages[i].assessment2 +
                               record[i].score3 * courseWeightages[i].assessment3) /
                              (courseWeightages[i].assessment1 + courseWeightages[i].assessment2 +
                               courseWeightages[i].assessment3);
        float gpa = calculateGPA(weightedTotal, 100); // Assuming the scale is out of 100
        fprintf(file, "%-*d | %-*.2f | %-*.2f | %-*.2f | %-*d | %-*.2f | %-*.2f\n",
                COURSE_ID_WIDTH, record[i].studentId, ASSESSMENT_WIDTH, record[i].score1,
                ASSESSMENT_WIDTH, record[i].score2, ASSESSMENT_WIDTH, record[i].score3,
                COURSE_ID_WIDTH, record[i].courseId, TOTAL_WIDTH, weightedTotal, TOTAL_WIDTH, gpa);
    }

    fclose(file);
}

bool isUniqueCourseId(int courseId, StudentRecord record[], int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        if (record[i].courseId == courseId) {
            return false;
        }
    }
    return true;
}

void readCourseInfo(StudentRecord record[], int* numCourses) {
    FILE* fp = fopen("courseweightage.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp); // Skip the header line

    int courseId;
    float assessment1, assessment2, assessment3;
    int index = 0;
    while (fgets(line, sizeof(line), fp) != NULL && index < MAX_COURSES) {
        if (sscanf(line, "%d | %f | %f | %f", &courseId, &assessment1, &assessment2, &assessment3) == 4) {
            record[index].courseId = courseId;
            record[index].score1 = 0.0;
            record[index].score2 = 0.0;
            record[index].score3 = 0.0;
            (*numCourses)++;
            index++;
        } else {
            printf("Error reading course data from file\n");
            continue;
        }
    }

    fclose(fp);
}

CourseWeightage courseWeightages[MAX_COURSES];
int numWeightages = 0; // Keep track of the number of course weightages read

void readCourseWeightages() {
    FILE* fp = fopen("courseweightage.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp); // Skip the header line

    while (fgets(line, sizeof(line), fp) != NULL && numWeightages < MAX_COURSES) {
        if (sscanf(line, "%d | %f | %f | %f", &courseWeightages[numWeightages].courseId,
                   &courseWeightages[numWeightages].assessment1, &courseWeightages[numWeightages].assessment2,
                   &courseWeightages[numWeightages].assessment3) == 4) {
            numWeightages++;
        } else {
            printf("Error reading course weightage data from file\n");
            continue;
        }
    }

    fclose(fp);
}

void viewInfos(char * file_name){
    FILE *file=fopen(file_name ,"r");
    if(file==NULL){
    printf("Error opening the file");
    return ;
    }
    char line [250];
    while(fgets(line, 250, file)!=NULL){
      printf("%s",line);
    }
    fclose(file);
}

void student_view(){
    viewInfos("StuInfo.txt");
}

void updateAssessmentInfo(StudentRecord record[], int numCourses) {
    readCourseWeightages(); // Read course weightages data

    int studentId;
    student_view();
    printf("\nEnter student ID: ");
    scanf("%d", &studentId);

    for (int i = 0; i < numCourses; i++) {
        float score1, score2, score3;
        printf("\nEnter assessment percentages for Course ID %d:\n", record[i].courseId);
        printf("\nAssessment 1: ");
        scanf("%f", &score1);
        printf("\nAssessment 2: ");
        scanf("%f", &score2);
        printf("\nAssessment 3: ");
        scanf("%f", &score3);

        if (score1 < 0 || score2 < 0 || score3 < 0 || score1 > 100 || score2 > 100 || score3 > 100) {
            printf("Error: Assessment percentages should be between 0 and 100. Please re-enter.\n");
            i--;
            continue;
        }

        // Find the corresponding course weightage data
        int courseIndex = -1;
        for (int j = 0; j < numWeightages; j++) {
            if (record[i].courseId == courseWeightages[j].courseId) {
                courseIndex = j;
                break;
            }
        }

        if (courseIndex != -1) {
            float totalWeightage = courseWeightages[courseIndex].assessment1 + courseWeightages[courseIndex].assessment2 + courseWeightages[courseIndex].assessment3;
            float weightedTotal = (score1 * courseWeightages[courseIndex].assessment1 + score2 * courseWeightages[courseIndex].assessment2 + score3 * courseWeightages[courseIndex].assessment3) / totalWeightage;
            record[i].studentId = studentId;
            record[i].score1 = score1;
            record[i].score2 = score2;
            record[i].score3 = score3;
            record[i].totals = weightedTotal; // Assuming totals is the weighted sum of scores
        } else {
            printf("Error: Course ID %d not found in course weightage data.\n", record[i].courseId);
        }
    }

    SaveGradesInfo(record, numCourses, courseWeightages); // Pass course weightages to SaveGradesInfo
    printf("Assessment information updated successfully for student ID %d.\n", studentId);
}

int marks() {
    StudentRecord record[MAX_COURSES];
    int numCourses = 0;

    readCourseInfo(record, &numCourses);
    updateAssessmentInfo(record, numCourses);

    return 0;
}
