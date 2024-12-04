#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024
#define MAX_STUDENTS 100
#define MAX_LENGTH 50
#define NUM_WEEKS 10
#define AID_WIDTH 10
#define APASS_WIDTH 15
#define ANAME_WIDTH 20
#define ALAST_NAME_WIDTH 20
#define AAGE_WIDTH 5
#define AGENDER_WIDTH 10
#define ANATIONALITY_WIDTH 15
#define AEMAIL_WIDTH 30
#define AADDRESS_WIDTH 40
#define ATTENDANCE_WIDTH 50

typedef struct student1{
  char name[50];
  char Last_Name[50];
  int age;
  int Student_Id;
  int Password;
  char Gender[50];
  char Nationality[50];
  char email[50];
  char address[50];
 } studu;


void ViewInfo(char * file_name){
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

int File_Reading(FILE *file, int *StudentID){
  int found=0;
  studu student1;
  char line[250];
  while(fgets(line, 250, file)){
   sscanf(line, "%d | %d | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^\n]",
      &student1.Student_Id, &student1.Password, student1.name, student1.Last_Name, &student1.age,
      student1.Gender, student1.Nationality, student1.email, student1.address);
  //continuesly reading the file
  //specifies the format for reading the file
  ////%: Indicates a format specifier.
  //49: Specifies the maximum number of characters to read. In this case, it's 49 characters.
  //[^|]: Indicates that the input should read characters until a pipe character | is encountered.
  //The ^ inside the brackets [] is a negation operator, meaning any character except | will be read.
  // useful because it automatically trims any leading spaces from the input string.
   if(* StudentID ==student1.Student_Id){

        printf("Student found......\n\n");
        printf("%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
        AID_WIDTH, "Student ID",APASS_WIDTH ,"Password",  ANAME_WIDTH,"First Name",ALAST_NAME_WIDTH,"Last Name",AAGE_WIDTH, "Age",AGENDER_WIDTH,"Gender",
        ANATIONALITY_WIDTH,"Nationality",AEMAIL_WIDTH,"Email",AADDRESS_WIDTH,"Address");
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("%s",line);
        found=1;
        break;
  }
  }
  return found;
}

int generateStudentIDs(int studentIDs[MAX_STUDENTS]) {

    FILE* file = fopen("StuInfo.txt", "r");
    if (!file) {
        printf("Failed to open file: %s\n", "StuInfo.txt");
        return 0;  // Return 0 to indicate failure to open the file
    }

    char line[250];
    int numStudents = 0; // Counter for the number of student IDs read

    // Skip the header line
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL && numStudents < MAX_STUDENTS) {
        int id = 0;
        // Use sscanf to read the ID from the line
        sscanf(line, "%d", &id);
        // Store the extracted ID in the array
        studentIDs[numStudents ++] = id;
    }
    fclose(file);
    return numStudents; // Return the number of student IDs read
}

int get_student_num(){

    FILE *file=fopen("StuInfo.txt","r");
    if(file ==NULL){
        printf("file not found");
        return -1;
    }
    char line[250];
    int num_student =0;
    fgets(line, 250, file);
    fgets(line, 250, file);
    while (fgets(line, sizeof(line), file) != NULL) {
            num_student ++;
        }
    fclose(file);
    return num_student;

}

void calcu_All_Students_Attendance( const char *courseName) {
    int num_student = get_student_num();
    if (num_student < 0) {
        printf("Failed to get the number of students.\n");
        return;
    }

    int studentIDs[num_student];
    // This should be filled with actual IDs
    generateStudentIDs(studentIDs);
    // Ensure num_students does not exceed MAX_STUDENTS to prevent out-of-bounds access
    num_student = num_student > MAX_STUDENTS ? MAX_STUDENTS : num_student;
    float percentages[num_student];

    FILE *file = fopen("attendance_record.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int week_num;
    printf("Week Number:\n");
    if(scanf("%d",&week_num) !=1){
        printf("Invalid input");
        fclose(file);
        return;
    }
    int choice;
    printf("1- Mark the attendance for this lecture only ______:\n2- Mark the attendance for all lectures until week(%d) _____:\nEnter choice(1, 2):",week_num);
    if(scanf("%d",&choice) !=1){
        printf("Invalid input");
        fclose(file);
        return;
    }
    float totalClasses = week_num * 2;
    float attendedClasses;
    switch(choice){
        case 1:
            attendedClasses = 1;
            break;
        case 2:
            attendedClasses = totalClasses;
            break;
        default:
            printf("Invalid choice.\n");
            fclose(file); // Close the file before returning
            return;
    }

    int attend, class;
    fseek(file, 0, SEEK_END);
    long size=ftell(file);
    if(size == 0){ fprintf(file, " %-*s | %-*s | %-*s |%s\n",ATTENDANCE_WIDTH, "Course",ATTENDANCE_WIDTH, "Student ID",AEMAIL_WIDTH,"Percentage","Classes");
     }

    for (int i = 0; i < num_student; i++) {
        percentages[i] = (attendedClasses / totalClasses) * 100.00;
    }
    for (int i = 0; i < num_student; i++) {
        fprintf(file, " %-*s | %-*d | %-*.2f%%|%d/%d\n", ATTENDANCE_WIDTH, courseName, ATTENDANCE_WIDTH, studentIDs[i] ,AEMAIL_WIDTH, percentages[i],(int) attendedClasses,(int) totalClasses);
    }

    fclose(file);
    printf("Attendance records saved to attendance_record.txt.\n");
}

// Function to trim leading and trailing spaces from a string
void trim(char *str) {
    char *start, *end;
    // Trim leading space
    for (start = str; *start; ++start) {
        if (!isspace((unsigned char)start[0])) {
            break;
        }
    }
    // Trim trailing space
    for (end = start + strlen(start); end > start; --end) {
        if (!isspace((unsigned char)end[-1])) {
            break;
        }
    }
    *end = 0; // Null terminate the trimmed string
    if (start > str) {
        memmove(str, start, end - start + 1); // Shift the trimmed string to the start of the buffer
    }
}

void calcul_individal_Attendance(const char *courseName, int StudentID, float present){
    bool idFound;
    int num = get_student_num();
    if (num < 0) {
        printf("Failed to get the number of students.\n");
        return;
    }
    int studentIDs[num];
    // This should be filled with actual IDs
    int num_students=generateStudentIDs(studentIDs);
    // Ensure num_students does not exceed MAX_STUDENTS to prevent out-of-bounds access
    num = num > MAX_STUDENTS ? MAX_STUDENTS : num;
    FILE *file = fopen("attendance_record.txt", "r+");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    int ID=-1;
    for (int i=0; i< num ;i++){
            if(studentIDs[i] == StudentID){
            ID=studentIDs[i];
            idFound = true;
            break; // Exit the loop early since we found the matching ID
            }

    }

    if (!idFound) {
        printf("Attendance not available for Student ID %d.\n", StudentID);
        return;
    }
    int week_num;
    printf("Week Number:\n");
    if(scanf("%d",&week_num) !=1){
        printf("Invalid input");
        fclose(file);
        return;
    }
    fseek(file, 0, SEEK_END);
    long size=ftell(file);
    if(size == 0){ fprintf(file, " %-*s | %-*s | %-*s |%s\n",ATTENDANCE_WIDTH, "Course",ATTENDANCE_WIDTH, "Student ID",AEMAIL_WIDTH,"Percentage","Classes");
     }
    int choice;
    printf("1- Mark the attendance for this lecture only ______:\n2- Mark the attendance for all lectures until week(%d) _____:\nEnter choice(1, 2):",week_num);
    if(scanf("%d",&choice) !=1){
        printf("Invalid input");
        fclose(file);
        return;
    }
    float attend_pre;
    float percentage;
    float totalClasses = week_num * 2;
    float attendedClasses;
    switch(choice){
        case 1:
            attendedClasses = 1;
            break;
        case 2:
            attendedClasses = totalClasses;
            break;
        default:
            printf("Invalid choice.\n");
            fclose(file); // Close the file before returning
            return;
    }
    char line[MAX_LINE_LENGTH];
    bool found = false;
    rewind(file);

    fgets(line, sizeof(line), file);
    line[strcspn(line, "\n")] = 0; // Remove newline character from 'line' after fgets


    while (fgets(line, sizeof(line), file) != NULL) {
        int currentID, attended, total;
        char course[MAX_LINE_LENGTH];
        float percentage;

        // Adjust sscanf to match the provided file format with extra whitespace
        if (sscanf(line, "%[^|]| %d | %f %%|%d/%d", course, &currentID, &percentage, &attended, &total) == 5) {
            trim(course);
            if (currentID == StudentID && strcmp(course, courseName) ==0) {
                if (week_num  < (total / 2)){
                    found = true;
                    printf("Attedance record already exists");
                    return;
                }
            }
        }
    }
    if(!found){
        attend_pre= attendedClasses * present;
        percentage = ( attend_pre/ totalClasses) * 100.00;
        fprintf(file, " %-*s | %-*d | %-*.2f%%|%d/%d\n", ATTENDANCE_WIDTH, courseName, ATTENDANCE_WIDTH, ID ,AEMAIL_WIDTH, percentage,(int) attend_pre,(int) totalClasses);
        fclose(file);
        printf("Attendance records saved to attendance_record.txt.\n");
    }
}

void markAllAttendance(const char *courseName) {
    float attendance;
    int present;
    printf("Attendance marked for all students.\n");
    calcu_All_Students_Attendance(courseName);
}

void markIndividualAttendance(const char *courseName) {
    FILE *file=fopen("StuInfo.txt","r");
    if(file==NULL){
    printf("Error opening the file");
    return ;
    }
    int present;
    int studentID;
    printf("Enter the Student ID to mark attendance for: \n");
    scanf("%d", &studentID);
    getchar();

    int found = File_Reading(file,&studentID);
    if (found){
                printf("Enter attendance for student with ( %d) ID (1 for present, 0 for absent): ", studentID);
                scanf("%d", &present);
                switch (present){
                    case 1 :
                        calcul_individal_Attendance(courseName, studentID, (float)present);
                        return;
                        break;
                    case 0 :
                        calcul_individal_Attendance(courseName, studentID, (float)present);
                        return;
                    default:
                        printf("Enter a valid number");
                return;
                }

    }
    else if(!found){
     ("Student ID %d not found.\n", studentID);
   }
    fclose(file);
}
void file_format(char * format, size_t length){
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

void updateSingleClassAttendance() {
    // Correcting the mode to "r" for reading
    FILE *file = fopen("attendance_record.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    FILE *tempFile = fopen("temp_attendance.txt", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(file); // Make sure to close the file before returning
        return;
    }

    int studentID, presence;
    printf("\nEnter the Student ID to update attendance for: ");
    scanf("%d", &studentID);
    printf("Enter attendance for the class (1 for present, 0 for absent): ");
    scanf("%d", &presence);

    char line[MAX_LINE_LENGTH];
    bool found = false;

    // Read and write the header line to maintain file structure
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);
    // Read and write the second header line (dashes) to maintain file structure
    fgets(line, sizeof(line), file);
    fputs(line, tempFile);

    while (fgets(line, sizeof(line), file) != NULL) {
        int currentID, attended, total;
        char course[MAX_LINE_LENGTH] = {0};
        float percentage;

        // Adjust sscanf to match the provided file format with extra whitespace
        if (sscanf(line, "%[^|]| %d | %f %%|%d/%d", course, &currentID, &percentage, &attended, &total) == 5) {
            if (currentID == studentID) {
                found = true;
                total += 1; // Increment total classes by one
                if (presence == 1) {
                    attended += 1; // Increment attended classes by one if present
                }
                // Calculate new percentage
                percentage = ((float)attended / total) * 100;

                // Rewrite the updated line to temp file
                fprintf(tempFile, "%-50s| %-51d| %-30.2f%%|%d/%d\n", course, currentID, percentage, attended, total);
            } else {
                // Copy line to temp file as is
                fputs(line, tempFile);
            }
        } else {
            // If the line doesn't match the expected format, just copy it as is
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        // Replace old file with updated temp file
        remove("attendance_record.txt");
        rename("temp_attendance.txt", "attendance_record.txt");
        printf("Attendance updated successfully for Student ID %d.\n", studentID);
    } else {
        remove("temp_attendance.txt");
        printf("Student ID %d not found in the attendance record.\n", studentID);
    }
}

void retrieveAttendanceInfo(const char *fileName) {
    int studentID;
    printf("Enter the student ID to retrieve attendance info for: ");
    scanf("%d", &studentID);

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening the file: %s\n", fileName);
        return;
    }

    char line[MAX_LINE_LENGTH];
    bool found = false;
    // Read and ignore the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        int currentID = 0;
        float percentage = 0.0;
        int attended = 0, total = 0;
        char course[MAX_LINE_LENGTH] = {0};

        // Parsing with adjusted format to handle spaces
        if (sscanf(line, "%[^|]| %d | %f %%|%d/%d", course, &currentID, &percentage, &attended, &total) == 5) {
            if (currentID == studentID) {
                found = true;
                printf("Attendance Info for Student ID %d:\n", studentID);
                printf("Course: %s\n", course);
                printf("Percentage: %.2f%%\n", percentage);
                printf("Classes: %d/%d\n", attended, total);
                break; // Since we found the student, no need to continue
            }
        }
    }


    fclose(file);

    if (!found) {
        printf("No attendance info found for Student ID %d.\n", studentID);
    }
}

void Attendance_view(){

 ViewInfo("attendance_record.txt");
}

int attendace() {

    ViewInfo("StuInfo.txt");
    // Choose course
    int chosenCourse;

    printf("\nChoose the course:\n");
    printf("1. AI\n");
    printf("2. Database\n");
    printf("3. System Analysis and Design\n");
    printf("4. C Programming\n");
    printf("5. Mathematics\n");
    printf("Enter your choice: ");
    scanf("%d", &chosenCourse);

    const char *courseNames[] = {"AI", "Database", "System Analysis and Design", "C Programming", "Mathematics"};
    const char *courseName = courseNames[chosenCourse - 1];

    // Loop for marking attendance
    int choice;
    do {
        printf("\n1. Mark all students as present\n");
        printf("2. Mark attendance for individual students \n");
        printf("3. View all student's attendance \n");
        printf("4. Retrieve student's attendance\n");
        printf("5. Update student's attendance\n");
        printf("6. Exit\n");
        printf("Enter your choice:_________ ");
        scanf("%d", &choice);


        switch (choice) {
            case 1:
                markAllAttendance(courseName); // Mark all students as present
                break;
            case 2:
                markIndividualAttendance(courseName); // Mark attendance for individual student
                break;
            case 3:
                Attendance_view();
                break;
            case 4:
                retrieveAttendanceInfo("attendance_record.txt");
                break;
            case 5:
                Attendance_view();
                updateSingleClassAttendance();
                getchar();
                break;
            case 6:
                break;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
