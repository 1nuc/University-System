#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COURSE_ID_WIDTH 10
#define ASSESSMENT_WIDTH 15
#define MAX_COURSES 5

typedef struct {
    int courseId;
    float assessment1;
    float assessment2;
    float assessment3;
} Course;

void SaveCourseInfo(Course courses[], int numCourses) {
    // Check if the file exists and read the data
    FILE* file = fopen("courseweightage.txt", "r");
    bool fileExists = (file != NULL);
    fclose(file); // Close the file if it was opened

    // Write or overwrite the file with the updated content
    file = fopen("courseweightage_temp.txt", "w");
    if (!file) {
        printf("Error opening file\n");
        return;
    }

    // Write the header
    fprintf(file, "%-*s | %-*s | %-*s | %-*s\n",
            COURSE_ID_WIDTH, "Course ID", ASSESSMENT_WIDTH, "Assessment 1",
            ASSESSMENT_WIDTH, "Assessment 2", ASSESSMENT_WIDTH, "Assessment 3");
    fprintf(file, "--------------------------------------------------------------------------------\n");

    // Write all course data
    for (int i = 0; i < numCourses; i++) {
        fprintf(file, "%-*d | %-*.2f | %-*.2f | %-*.2f\n",
                COURSE_ID_WIDTH, courses[i].courseId, ASSESSMENT_WIDTH, courses[i].assessment1,
                ASSESSMENT_WIDTH, courses[i].assessment2, ASSESSMENT_WIDTH, courses[i].assessment3);
    }

    fclose(file);

    // If the original file exists, remove it
    if (fileExists) {
        remove("courseweightage.txt");
    }

    // Rename the temporary file to the original file name
    rename("courseweightage_temp.txt", "courseweightage.txt");
}




bool isUniqueCourseId1(int courseId, Course courses[], int numCourses) {
    for (int i = 0; i < numCourses; i++) {
        if (courses[i].courseId == courseId) {
            return false;
        }
    }
    return true;
}

void readCourseInfo8(Course courses[], int* numCourses) {
    FILE* fp = fopen("courseInfo.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), fp); // Skip the header line

    while (fgets(line, sizeof(line), fp) != NULL && *numCourses < MAX_COURSES) {
        int courseId;
        // Use sscanf to read the courseId, skipping initial characters and stopping at the vertical bar
        if (sscanf(line, "| %d |", &courseId) == 1) {
            if (isUniqueCourseId1(courseId, courses, *numCourses)) {
                courses[*numCourses].courseId = courseId;
                // Initialize assessments to zero or a default value
                courses[*numCourses].assessment1 = 0.0;
                courses[*numCourses].assessment2 = 0.0;
                courses[*numCourses].assessment3 = 0.0;
                (*numCourses)++;
            }
        } else {
            //printf("Error reading course data from file\n");
            continue;  // Skip to the next line if there's a formatting issue
        }
    }

    fclose(fp);
}

void updateAssessmentInfo1(Course courses[], int numCourses) {
    char continueInput;
    printf("Do you want to update course assessments? (Y/N): ");
    scanf(" %c", &continueInput);

    if (continueInput == 'N' || continueInput == 'n') {
        return;
    }

    for (int i = 0; i < numCourses; i++) {
        printf("Updating assessments for course ID %d\n", courses[i].courseId);
        float ass1, ass2, ass3;
        printf("Enter assessment percentages (total should be 100%%):\n");
        printf("Assessment 1: ");
        scanf("%f", &ass1);
        printf("Assessment 2: ");
        scanf("%f", &ass2);
        printf("Assessment 3: ");
        scanf("%f", &ass3);

        // Check if the total percentage exceeds 100%
        if (ass1 + ass2 + ass3 > 100.0) {
            printf("Error: Total percentage exceeds 100%%.\n");
            i--; // Decrement i to stay on the same course
            continue;
        }

        // Update the assessments

        courses[i].assessment1 = ass1;
        courses[i].assessment2 = ass2;
        courses[i].assessment3 = ass3;
        SaveCourseInfo(courses, numCourses);
    }

    // Update the file
    printf("Assessment information updated successfully for all courses.\n");
}


int managegrading() {
    Course courses[MAX_COURSES];
    int numCourses = 0;
    int choice;

    readCourseInfo8(courses, &numCourses); // Load existing course data

    // Menu for user interaction
    printf("=================================\n\n");
    printf("Choose an option:\n");
    printf("1. Update Assessment Information\n");
    printf("2. Exit\n");
    printf("=================================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            updateAssessmentInfo1(courses, numCourses);
             // Save updated data back to file
             printf("press enter to continue.....\n");
             getchar();
            break;
        case 2:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice. Exiting program.\n");
            break;
    }


    return 0;
}


