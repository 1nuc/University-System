#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//define constants representing the width of various fields in the course structure
#define COURSEID_WIDTH 10
#define COURSENAME_WIDTH 65
#define COURSETYPE_WIDTH 25
#define LECTURERNAME_WIDTH 20
#define DURATION_WIDTH 15


//define constants representing the width of various fields in the student structure
#define COUID_WIDTH 10
#define COUPASS_WIDTH 15
#define COUNAME_WIDTH 20
#define COULAST_NAME_WIDTH 20
#define COUAGE_WIDTH 5
#define COUGENDER_WIDTH 10
#define COUNATIONALITY_WIDTH 15
#define COUEMAIL_WIDTH 30
#define COUADDRESS_WIDTH 40
#define COUCOURSE_WIDTH 30

#define COULECNAME_WIDTH 30
#define COULECPASS_WIDTH 30



typedef struct course{
    int courseID;
    char courseName[100];
    char courseType[20];
    char lecturerName[100];
    float duration;
} Cou;

typedef struct student5{
    char name[50];
    char Last_Name[50];
    int age;
    int Student_Id;
    char Password[50];
    char Gender[50];
    char Nationality[50];
    char email[50];
    char address[50];
    char course[100];
 } studu7;

typedef struct Lecturer10{
    char name[COULECNAME_WIDTH];
    int age;
    int id;
    char password[COULECPASS_WIDTH];
} Lecturer10;


void ViewStuInfo(){
    FILE *file=fopen("StuInfo.txt","r");
    if(file==NULL){
    printf("Error opening the file");
    return ;
    }
    char line [100];
    while(fgets(line, 100, file)!=NULL){
        printf("%s",line);
    }
    fclose(file);
}

void ViewInfo66(char * file_name){
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

void file_format1(char * format, size_t length){
    //checking if its not Null
    if (format == NULL)return;
    size_t len= strlen(format);
    //Trim the new line character
    if(len > 0 && format[len - 1]=='\n'){
      format[len - 1]='\0';
      len--;
      //adjusting the length after the formating
    }
    //ensure string does not exceed the maximum length
    if(len >= length - 1){
      format[length -1]='\0';
    }
}

void student_view1(){
    ViewInfo66("StuInfo.txt");
}

void readCourseInfo1(){
    ViewInfo66("courseInfo.txt");
}

int File_Reading1(FILE *file, int *CourseID){
    int found=0;
    Cou course;
    char line[250];
    while(fgets(line, 250, file)){
    sscanf(line, "| %d | %99[^|] | %19[^|] | %99[^|] | %f |\n",
                  &course.courseID, course.courseName, course.courseType,
                  course.lecturerName, &course.duration);
    //continuesly reading the file
    //specifies the format for reading the file
    ////%: Indicates a format specifier.
    //49: Specifies the maximum number of characters to read. In this case, it's 49 characters.
    //[^|]: Indicates that the input should read characters until a pipe character | is encountered.
    //The ^ inside the brackets [] is a negation operator, meaning any character except | will be read.
    // useful because it automatically trims any leading spaces from the input string.
    if(*CourseID == course.courseID){

          printf("Student found......\n\n");
          printf("| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
                COURSEID_WIDTH, "Course ID", COURSENAME_WIDTH, "Course Name", COURSETYPE_WIDTH, "Course Type", LECTURERNAME_WIDTH, "Lecturer Name",
                DURATION_WIDTH, "Duration(hours)");
          printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
          printf("%s",line);
          found=1;
          break;
    }
    }
    return found;
}

void View_Lecturers() {
    FILE *file = fopen("lecturer_info.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    char buffer[1000];
    printf("---------------------------\n");
    printf("Lecturer Information:\n");
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    printf("---------------------------\n");

    fclose(file);
}

void trimWhitespace(char *str) {
    int start = 0, end = strlen(str) - 1;

    // Find the first non-whitespace character from the start
    while (isspace(str[start])) {
        start++;
    }

    // Find the last non-whitespace character from the end
    while (end > start && isspace(str[end])) {
        end--;
    }

    // Shift the string to remove leading whitespace
    memmove(str, str + start, end - start + 1);

    // Null-terminate the string
    str[end - start + 1] = '\0';
}

void saveCourseInfo(Cou course){
    FILE *file=fopen("courseInfo.txt","a");
    if(file==NULL){
        printf("Error opening the file");
        return ;
    }


    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    if (fileSize == 0) {

    fprintf(file, "| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
        COURSEID_WIDTH, "Course ID", COURSENAME_WIDTH, "Course Name", COURSETYPE_WIDTH, "Course Type", LECTURERNAME_WIDTH, "Lecturer Name",
        DURATION_WIDTH, "Duration(hours)");
    fprintf(file, "+------------+-------------------------------------------------------------------+---------------------------+----------------------+-----------------+\n");
    }

    fprintf(file, "| %-*d | %-*s | %-*s | %-*s | %-*.2f |\n",
                            COURSEID_WIDTH, course.courseID, COURSENAME_WIDTH, course.courseName, COURSETYPE_WIDTH, course.courseType,
                            LECTURERNAME_WIDTH, course.lecturerName, DURATION_WIDTH, course.duration);

    fclose(file);
}

void addCourseDetails(){
    char buffer[100];
    int i;
    Cou course;
    #define COUMAX_LENGTH 100

    while(1){
        printf("Enter the Course ID:\n");
        fgets(buffer,10,stdin);
        buffer[strlen(buffer)-1]='\0';
        course.courseID = atoi(buffer);

        printf("Enter the Course Name:\n");
        fgets(course.courseName,65,stdin);
        course.courseName[strlen(course.courseName)-1]='\0';

        while (1) {
        printf("Enter the type of Course (Lecture/Lab): ");
        fgets(course.courseType, 20, stdin);
        course.courseType[strlen(course.courseType) - 1] = '\0'; // Remove newline character

        // Convert input to lowercase for case-insensitive comparison
        for (int i = 0; course.courseType[i]; i++) {
            course.courseType[i] = tolower(course.courseType[i]);
        }

        // Check if the input is valid
        if (strcmp(course.courseType, "lecture") == 0 || strcmp(course.courseType, "lab") == 0) {
            break; // Valid input, exit the loop
        } else {
            printf("Invalid input! Please enter either 'Lecture' or 'Lab'.\n");
        }
        }

        while (1) {
            FILE *lecturerFile = fopen("lecturer_info.txt", "r");
            if (lecturerFile == NULL) {
                printf("Error opening the lecturer file\n");
                return;
            }

            View_Lecturers();

            char lecturerName[COUMAX_LENGTH];
            Lecturer10 lecturer;
            //Cou course;

            printf("Enter lecturer name: ");
            fgets(lecturerName, sizeof(lecturerName), stdin);
            lecturerName[strcspn(lecturerName, "\n")] = '\0';

            char line[256];
            int found = 0;

            while (fgets(line, sizeof(line), lecturerFile)) {
                sscanf(line, "| %d | %64[^|] | %d | %19[^|] |", &lecturer.id, lecturer.name, &lecturer.age, lecturer.password);
                
                lecturer.name[strcspn(lecturer.name, "\n")] = '\0';
                trimWhitespace(lecturer.name);

                if (strcmp(lecturer.name, lecturerName) == 0) {
                    strcpy(course.lecturerName, lecturerName);
                    found = 1;
                    break; // Exit the loop once lecturer is found
                }
            }
            fclose(lecturerFile);

            if (found) {
                printf("Lecturer Exist: %s\n", course.lecturerName);
                break;
            } else {
                printf("Lecturer not found\n");
            }
        }

        printf("Enter the Duration of the Course:\n");
        fgets(buffer,15,stdin);
        buffer[strlen(buffer)-1]='\0';
        course.duration=atof(buffer);

        printf("Course Information has been assigned!\nClick 1 one if you want to assign another one or click 2 to leave:");
        scanf("%d",&i);
        getchar();
        saveCourseInfo(course);

        if(i!=1 && i!=2){
            printf("Unvalid operation\n");
            break;
        }
        else if(i==2){
            break;
        }
    }
}

void deleteCourseInfo() {
    FILE *file = fopen("courseInfo.txt", "r");
    if (file == NULL) {
        printf("Error reading the file");
        return;   
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error creating the temporary file");
        fclose(file);
        return;
    }

    readCourseInfo1();

    Cou course;
    int courseID;
    int found = 0;
    char course_type[20]; // Should be an array to store the course type
    char header[256], delete;
    char line[256];

    fprintf(temp, "| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
            COURSEID_WIDTH, "Course ID", COURSENAME_WIDTH, "Course Name", COURSETYPE_WIDTH, "Course Type", LECTURERNAME_WIDTH, "Lecturer Name",
            DURATION_WIDTH, "Duration(hours)");

    printf("\nEnter the Course ID to be deleted: ");
    scanf("%d", &courseID);
    getchar();
    
    printf("\nEnter the Course Type to be deleted (Lab/Lecture): ");
    scanf("%s", course_type); // Read course type as a string
    getchar();

    fgets(header, sizeof(header), file); // Read and discard the header line

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "| %d | %99[^|] | %19[^|] | %99[^|] | %f |\n",
               &course.courseID, course.courseName, course.courseType,
               course.lecturerName, &course.duration);

        course.courseType[strcspn(course.courseType, "\n")] = '\0';
        course.courseType[strcspn(course.courseType, " ")] = '\0';       

        if (course.courseID == courseID && strcmp(course.courseType, course_type) == 0) {
            printf("\n\nCourse ID: %d\nCourse Name: %s\nCourse Type: %s\nLecturer Name: %s\nDuration: %.2f\n\n", 
                   course.courseID, course.courseName, course.courseType, course.lecturerName, course.duration);

            printf("\nDo you want to delete this course?(y/n) ");
            scanf("%c", &delete);
            getchar();

            while (delete != 'y' && delete != 'n') {
                printf("\nInvalid choice! Please enter 'y' or 'n': ");
                scanf("%c", &delete);
                getchar();
            }

            if (delete == 'y') {
                found = 1;
                continue; // Skip writing this line to the temporary file
            } 
        }
        fprintf(temp, "%s", line); // Write the line to the temporary file
    }

    fclose(file);
    fclose(temp);

    if (found) {
        remove("courseInfo.txt");
        rename("tempfile.txt", "courseInfo.txt");
        printf("\nCourse Deleted Successfully!\n");
    } 
    else {
        remove("tempfile.txt");
        printf("\nCourse Not Deleted!\n");
    }
}

void updateCourseInfo(){

    FILE *file = fopen("courseInfo.txt", "r+");
    if(file == NULL){
        printf("Error reading the file");
        return;
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if(temp == NULL){
        printf("Error creating the temporary file");
        fclose(file);
        return;
    }

    Cou course;
    int courseID;
    char course_type[25];
    int found = 0;
    int updateChoice;
    char newCourseName[65], newLecturerName[25];
    float newDuration;
    char line[256];

    printf("**************Update Course Information**************\n\n");

    printf("Enter the Course ID you want to update: ");
    scanf("%d", &courseID);
    getchar();

    printf("Enter the Course Type (lab/lecture): ");
    scanf("%s", course_type);
    getchar();


    fprintf(temp, "| %-*s | %-*s | %-*s | %-*s | %-*s |\n",
            COURSEID_WIDTH, "Course ID", COURSENAME_WIDTH, "Course Name", COURSETYPE_WIDTH, "Course Type", LECTURERNAME_WIDTH, "Lecturer Name",
            DURATION_WIDTH, "Duration(hours)");
    fprintf(temp, "+------------+-------------------------------------------------------------------+---------------------------+----------------------+-----------------+\n");

    char header[256];
    fgets(header, sizeof(header), file);
    fgets(line, sizeof(line), file);

    while (fscanf(file, "| %d | %99[^|] | %19[^|] | %99[^|] | %f |\n",
                  &course.courseID, course.courseName, course.courseType,
                  course.lecturerName, &course.duration) == 5) {

        course.courseType[strcspn(course.courseType, "\n")] = '\0';
        course.courseType[strcspn(course.courseType, " ")] = '\0';

        if(course.courseID == courseID && strcmp(course.courseType, course_type) == 0) {
            found = 1;

            printf("\n\nCourse ID: %d\nCourse Name: %s\nCourse Type: %s\nLecturer Name: %s\nDuration: %.2f\n\n", course.courseID, course.courseName, course.courseType, course.lecturerName, course.duration);

            printf("\n1. Update Course Name\n2. Update Lecturer Name\n3. Update Duration of Course\n4. Exit\nPlease Enter Your Choice: ");
            scanf("%d", &updateChoice);
            getchar();



            if (updateChoice == 1) {
                printf("\nEnter new Course Name: ");
                fgets(newCourseName, sizeof(newCourseName), stdin);
                newCourseName[strcspn(newCourseName, "\n")] = '\0';
                strcpy(course.courseName, newCourseName);
                found = 1;
            }

            else if (updateChoice == 2) {

                FILE *lecturerFile = fopen("lecturer_info.txt", "r");
                    if (lecturerFile == NULL) {
                        printf("Error opening the lecturer file\n");
                        return;
                    }

                    View_Lecturers();

                    char lecturerName[MAX_LENGTH];
                    Lecturer10 lecturer;
                    //Cou course;

                    printf("Enter lecturer name: ");
                    fgets(lecturerName, sizeof(lecturerName), stdin);
                    lecturerName[strcspn(lecturerName, "\n")] = '\0';

                    char line[256];
                    int found = 0;

                    while (fgets(line, sizeof(line), lecturerFile)) {
                        sscanf(line, "| %d | %64[^|] | %d | %19[^|] |", &lecturer.id, lecturer.name, &lecturer.age, lecturer.password);
                        
                        lecturer.name[strcspn(lecturer.name, "\n")] = '\0';
                        trimWhitespace(lecturer.name);

                        if (strcmp(lecturer.name, lecturerName) == 0) {
                            strcpy(course.lecturerName, lecturerName);
                            found = 1;
                            break; // Exit the loop once lecturer is found
                        }
                    }
                    fclose(lecturerFile);

                    if (found) {
                        printf("Lecturer Exist: %s\n", course.lecturerName);
                        break;  
                    } 
                    else {
                        printf("Lecturer not found\n");
                    }
                found = 1;
            } 

            else if (updateChoice == 3) {
                printf("\nEnter new duration: ");
                scanf("%f", &newDuration);
                getchar();
                course.duration = newDuration;
                found = 1;
            }

            else if (updateChoice == 4) {
                found = 1;
                return;
            }

            else {
                printf("\nError! Invalid choice.\n\n");
            }

            file_format1(course.courseName, COURSENAME_WIDTH);
            file_format1(course.courseType, COURSETYPE_WIDTH);
            file_format1(course.lecturerName, LECTURERNAME_WIDTH);

                sprintf(line, "| %-*d | %-*s | %-*s | %-*s | %-*.2f |\n",
                    COURSEID_WIDTH, course.courseID, COURSENAME_WIDTH, course.courseName, COURSETYPE_WIDTH, course.courseType,
                    LECTURERNAME_WIDTH, course.lecturerName, DURATION_WIDTH, course.duration);
                    fprintf(temp, "%s", line);

            printf("\nCourse information updated successfully!\n\n");
        }

        else {

            file_format1(course.courseName, COURSENAME_WIDTH);
            file_format1(course.courseType, COURSETYPE_WIDTH);
            file_format1(course.lecturerName, LECTURERNAME_WIDTH);

                sprintf(line, "| %-*d | %-*s | %-*s | %-*s | %-*.2f |\n",
                    COURSEID_WIDTH, course.courseID, COURSENAME_WIDTH, course.courseName, COURSETYPE_WIDTH, course.courseType,
                    LECTURERNAME_WIDTH, course.lecturerName, DURATION_WIDTH, course.duration);
                    fprintf(temp, "%s", line);
        }

    }

    if(!found){
        printf("\nCourse not found\n\n");
    } else {
        printf("\n***Returning to Menu***\n\n");
    }

    fclose(file);
    fclose(temp);
    remove("courseInfo.txt");
    rename("tempfile.txt", "courseInfo.txt");
}

void remove_trailing_whitespace(char *str) {
    int len = strlen(str);
    int i = len - 1;

    // Find the first non-space character from the end
    while (i >= 0 && str[i] == ' ')
        i--;

    // If the last non-space character is a digit, remove trailing whitespace
    if (i >= 0 && (str[i] >= '0' && str[i] <= '9')) {
        // Move back over whitespace
        while (i >= 0 && str[i] == ' ')
            i--;
        str[i + 1] = '\0'; // Replace the first whitespace after the last digit with null terminator
    }
}

void AssignCourse() {
    // Open StuInfo.txt file for reading
    FILE *file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    // Open a temporary file for writing
    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error creating the temporary file\n");
        fclose(file);
        return;
    }

    // Open courseInfo.txt file for reading
    FILE *Cfile = fopen("courseInfo.txt", "r");
    if(Cfile == NULL){
        printf("Error reading the file");
        return;
    }

    student_view1();

    // Define variables
    studu7 student5;
    Cou course;
    char line[250];
    int studentID, found = 0;
    char tempcourse[10];
    int courseID;
    char header[256];
    int find = 0;

    // Write header to the temporary file
    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
    COUID_WIDTH, "Student ID",COUPASS_WIDTH ,"Password",  COUNAME_WIDTH,"First Name",COULAST_NAME_WIDTH,"Last Name",COUAGE_WIDTH, "Age",COUGENDER_WIDTH,"Gender",
    COUNATIONALITY_WIDTH,"Nationality",COUEMAIL_WIDTH,"Email",COUADDRESS_WIDTH,"Address", COUCOURSE_WIDTH, "Course");
    fprintf(temp, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


    fgets(line, 250, file);
    fgets(line, 250, file);


    printf("\nEnter Student ID: ");
    scanf("%d", &studentID);
    getchar(); // Consume newline
    printf("\n");


    while(fgets(line, 250, file)) {
        // Parse student information from the line
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
            &student5.Student_Id, &student5.Password, student5.name, student5.Last_Name, &student5.age,
            student5.Gender, student5.Nationality, student5.email, student5.address, student5.course);

        //printf("student: %d %s\n", student.Student_Id, student.course);

        //memset(&tempcourse, 0, sizeof(tempcourse));


        student5.course[strcspn(student5.course, "\n")] = '\0';
        remove_trailing_whitespace(student5.course);

        if (student5.Student_Id == studentID) {
            found = 1;
            // Found the student, now process the assignment of the course

            fgets(header, sizeof(header), Cfile);
            fgets(header, sizeof(header), Cfile);

            // Prompt user to enter Course ID to assign
            readCourseInfo1();
            printf("\n\nEnter Course ID to assign: ");
            fgets(tempcourse,65,stdin);
            tempcourse[strcspn(tempcourse, "\n")]='\0';
            //printf("%s", tempcourse);

            // Check if the entered Course ID exists in courseInfo.txt
            while (fscanf(Cfile, "| %d | %99[^|] | %19[^|] | %99[^|] | %f |\n",
                  &course.courseID, course.courseName, course.courseType,
                  course.lecturerName, &course.duration) == 5) {

                if (course.courseID == atoi(tempcourse)) {
                    //printf("course: %d, %s\n", student.Student_Id, student.course);
                    if (strcmp(student5.course, "0") == 0) {
                        strcpy(student5.course, tempcourse); // Assign the course directly
                        found = 1;
                        find = 1;
                        break;
                    }
                    else {
                        // Check if the course is already in the student's course list
                        if (strstr(student5.course, tempcourse) == NULL) {
                            if (strlen(student5.course) > 0) {
                                strcat(student5.course, ", ");
                            }
                            strcat(student5.course, tempcourse); // Append the course to existing ones
                            found = 1;
                            find = 1;
                        } else {
                            printf("Course already exists for the student.\n");
                            find = 1;
                            found = 2;
                        }
                    }
                    break;
                }
            }
            if(!find) {
                    printf("Course not found\n");
                }
        }

        // Format and write the student information to the temporary file
        file_format1(student5.name, COUNAME_WIDTH);
        file_format1(student5.Last_Name, COULAST_NAME_WIDTH);
        file_format1(student5.Gender, COUGENDER_WIDTH);
        file_format1(student5.Nationality, COUNATIONALITY_WIDTH);
        file_format1(student5.email, COUEMAIL_WIDTH);
        file_format1(student5.address,  COUADDRESS_WIDTH);
        file_format1(student5.course, COUCOURSE_WIDTH);
        file_format1(student5.Password, COUPASS_WIDTH);

        sprintf(line, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s\n",
            COUID_WIDTH, student5.Student_Id, COUPASS_WIDTH, student5.Password, COUNAME_WIDTH, student5.name, COULAST_NAME_WIDTH, student5.Last_Name,
            COUAGE_WIDTH, student5.age, COUGENDER_WIDTH, student5.Gender, COUNATIONALITY_WIDTH, student5.Nationality,
            COUEMAIL_WIDTH, student5.email, COUADDRESS_WIDTH, student5.address, COUCOURSE_WIDTH, student5.course);
        fprintf(temp, "%s", line);
    }

    // Close the files
    fclose(file);
    fclose(temp);
    fclose(Cfile);

    // Check if the student was found and course assigned successfully
    if (!found) {
        remove("tempfile.txt");
        printf("Student not found.\n");
        return;
    }
    else if (found == 2) {

    }
    else {
        printf("Course has been assigned!\n");
    }

    // Replace StuInfo.txt with the temporary file
    remove("StuInfo.txt");
    rename("tempfile.txt", "StuInfo.txt");
}


void RemoveCourse() {
    FILE *file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error creating the temporary file\n");
        fclose(file);
        return;
    }

    student_view1();

    studu7 student5;
    char line[250];
    int studentID, found = 0, numCourses;
    char courseToRemove[10];

    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
    COUID_WIDTH, "Student ID",COUPASS_WIDTH ,"Password",  COUNAME_WIDTH,"First Name",COULAST_NAME_WIDTH,"Last Name",COUAGE_WIDTH, "Age",COUGENDER_WIDTH,"Gender",
    COUNATIONALITY_WIDTH,"Nationality",COUEMAIL_WIDTH,"Email",COUADDRESS_WIDTH,"Address", COUCOURSE_WIDTH, "Course");
    fprintf(temp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    printf("Enter Student ID: ");
    scanf("%d", &studentID);
    getchar(); // Consume newline

    while(fgets(line, 250, file)) {
        memset(&student5, 0, sizeof(studu7)); // Initialize student structure to zero
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
            &student5.Student_Id, &student5.Password, student5.name, student5.Last_Name, &student5.age,
            student5.Gender, student5.Nationality, student5.email, student5.address, student5.course);

        student5.course[strcspn(student5.course, "\n")] = '\0'; // Remove newline character
        remove_trailing_whitespace(student5.course);

        if (student5.Student_Id == studentID) {
            printf("Enter Course ID to remove: ");
            fgets(courseToRemove, sizeof(courseToRemove), stdin);
            courseToRemove[strcspn(courseToRemove, "\n")] = '\0'; // Remove newline character

            if (strlen(student5.course) > 0) {
                char *pos = strstr(student5.course, courseToRemove);
                if (pos != NULL) {
                    // Adjust the student's course string
                    if (strcmp(student5.course, courseToRemove) == 0) {
                        strcpy(student5.course, "0"); // Set course to "0" if it's the only course
                    }
                    else {
                        if (pos == student5.course) {
                            // If the course to remove is at the beginning of the string
                            memmove(pos, pos + strlen(courseToRemove) + 2, strlen(pos + strlen(courseToRemove) + 2) + 1);
                        }
                        else {
                            // If the course to remove is not at the beginning
                            memmove(pos - 2, pos + strlen(courseToRemove), strlen(pos + strlen(courseToRemove)) + 1);
                        }
                    }
                    found = 1;
                    printf("Course removed successfully.\n");
                }
                else {
                    printf("Course not found for the specified student.\n");
                }
            }
            else {
                printf("No courses to remove for the student.\n");
                strcpy(student5.course, "0"); // Set course to "0" if there are no courses left
            }

        }

        // Write the student information to the temporary file
        if (student5.Student_Id != 0) {
            file_format1(student5.name, COUNAME_WIDTH);
            file_format1(student5.Last_Name, COULAST_NAME_WIDTH);
            file_format1(student5.Gender, COUGENDER_WIDTH);
            file_format1(student5.Nationality, COUNATIONALITY_WIDTH);
            file_format1(student5.email, COUEMAIL_WIDTH);
            file_format1(student5.address,  COUADDRESS_WIDTH);
            file_format1(student5.course, COUCOURSE_WIDTH);
            file_format1(student5.Password, COUPASS_WIDTH);

            sprintf(line, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s\n",
                    COUID_WIDTH, student5.Student_Id, COUPASS_WIDTH, student5.Password, COUNAME_WIDTH, student5.name, COULAST_NAME_WIDTH, student5.Last_Name,
                    COUAGE_WIDTH, student5.age, COUGENDER_WIDTH, student5.Gender, COUNATIONALITY_WIDTH, student5.Nationality, COUEMAIL_WIDTH, student5.email,
                    COUADDRESS_WIDTH, student5.address, COUCOURSE_WIDTH, student5.course);
            fprintf(temp, "%s", line);
        }
    }

    fclose(file);
    fclose(temp);

    remove("StuInfo.txt");
    rename("tempfile.txt", "StuInfo.txt");
}

