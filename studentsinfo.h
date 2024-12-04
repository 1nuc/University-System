#define ID_WIDTH 10
#define PASS_WIDTH 15
#define NAME_WIDTH 20
#define LAST_NAME_WIDTH 20
#define AGE_WIDTH 5
#define GENDER_WIDTH 10
#define NATIONALITY_WIDTH 13
#define EMAIL_WIDTH 25
#define ADDRESS_WIDTH 25
#define COURSE_WIDTH 15
#define MAX_LINE_LENGTH 1024

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct student7{
    char name[50];
    char Last_Name[50];
    int age;
    int Student_Id;
    char Password [50] ;
    char Gender[50];
    char Nationality[50];
    char email[50];
    char address[50];
    char course[100];
 } studts;

void SaveStudentInfo(studts student7){

    FILE *file=fopen("StuInfo.txt","a");
    if(file==NULL){
      printf("Error opening the file");
      return ;
    }

      fseek(file, 0, SEEK_END);
      long size=ftell(file);
      if(size == 0){
        fprintf(file, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
        ID_WIDTH, "Student ID",PASS_WIDTH ,"Password",  NAME_WIDTH,"First Name",LAST_NAME_WIDTH,"Last Name",AGE_WIDTH, "Age",GENDER_WIDTH,"Gender",
        NATIONALITY_WIDTH,"Nationality",EMAIL_WIDTH,"Email",ADDRESS_WIDTH,"Address",COURSE_WIDTH, "Course");
         fprintf(file,"---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
      }
      //setting the file header of the student information
      fprintf(file, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s \n",
      ID_WIDTH, student7.Student_Id,PASS_WIDTH ,student7.Password,  NAME_WIDTH,student7.name,LAST_NAME_WIDTH,student7.Last_Name, AGE_WIDTH, student7.age,GENDER_WIDTH,student7.Gender,
      NATIONALITY_WIDTH,student7.Nationality,EMAIL_WIDTH,student7.email,ADDRESS_WIDTH,student7.address,COURSE_WIDTH, "0");
    //writing the student details into the file in the correct format
      fclose(file);
}

void Personal_Details(){
    char buffer[25];
    int i;
    studts student7;
    while(1){
      printf("What is your name:\n");
      fgets(student7.name,50,stdin);
      student7.name[strlen(student7.name)-1]='\0';

      printf("What is your last name:\n");
      fgets(student7.Last_Name,50,stdin);
      student7.Last_Name[strlen(student7.Last_Name)-1]='\0';

      printf("How old are you:\n");
      buffer[strlen(buffer)-1]='\0';
      fgets(buffer,50,stdin);
      student7.age=atoi(buffer);

      printf("Write down your ID please:\n");
      fgets(buffer,50,stdin);
      buffer[strlen(buffer)-1]='\0';
      student7.Student_Id=atoi(buffer);

      printf("Please write your password:\n");
      fgets(student7.Password,50,stdin);
      student7.Password[strlen(student7.Password)-1]='\0';

      printf("What is your Gender:\n");
      fgets(student7.Gender,50,stdin);
      student7.Gender[strlen(student7.Gender)-1]='\0';

      printf("What is your nationality:\n");
      fgets(student7.Nationality,50,stdin);
      student7.Nationality[strlen(student7.Nationality)-1]='\0';

      printf("Write your email:\n");
      fgets(student7.email,50,stdin);
      student7.email[strlen(student7.email)-1]='\0';

      printf("Write down your address please:\n");
      fgets(student7.address,50,stdin);
      student7.address[strlen(student7.address)-1]='\0';

      printf("Finish assigning student information.\nClick 1 one if you want to assign another one or click 2 to leave:");
      scanf("%d",&i);
      getchar();
      SaveStudentInfo(student7);

      if(i!=1&&i!=2){
        printf("Unvalid operation\n");
        break;
      }
      else if(i==2){

        break;
      }

    }
}

void ViewInfo12(char * file_name){
    FILE *file=fopen(file_name ,"r");
    if(file==NULL){
    printf("Error opening the file");
    return ;
    }
    char line [350];
    while(fgets(line, 350, file)!=NULL){
      printf("%s",line);
    }
    fclose(file);
}

void student_view12(){
    ViewInfo12("StuInfo.txt");
}

void file_format12(char * format, size_t length){
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

int File_Reading12(FILE *file, int *StudentID){
    int found=0;
    studts student7;
    char line[250];
    while(fgets(line, 250, file)){
    sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
        &student7.Student_Id, student7.Password, student7.name, student7.Last_Name, &student7.age,
        student7.Gender, student7.Nationality, student7.email, student7.address, &student7.course);
    //continuesly reading the file
    //specifies the format for reading the file
    ////%: Indicates a format specifier.
    //49: Specifies the maximum number of characters to read. In this case, it's 49 characters.
    //[^|]: Indicates that the input should read characters until a pipe character | is encountered.
    //The ^ inside the brackets [] is a negation operator, meaning any character except | will be read.
    // useful because it automatically trims any leading spaces from the input string.
    if(* StudentID ==student7.Student_Id){

          printf("Student found......\n\n");
          printf("%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
          ID_WIDTH, "Student ID",PASS_WIDTH ,"Password",  NAME_WIDTH,"First Name",LAST_NAME_WIDTH,"Last Name",AGE_WIDTH, "Age",GENDER_WIDTH,"Gender",
          NATIONALITY_WIDTH,"Nationality",EMAIL_WIDTH,"Email",ADDRESS_WIDTH,"Address", COURSE_WIDTH, "Course");
          printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
          printf("%s",line);
          found=1;
          break;
    }
    }
    return found;
}

void Retrieve_Student_Info(){
    FILE *file=fopen("StuInfo.txt","r");
    if(file==NULL){
    printf("Error opening the file");
    return ;
    }
    studts student7;
    int studentID;
    printf("Kindly Enter the student ID of to retreive information:\n");
    scanf("%d",&studentID);
    int found = File_Reading12(file,&studentID);
    fclose(file);
    if(!found){
      printf("Student not found.\n");
    }
}

void updateStuInfo() {
    FILE *file = fopen("StuInfo.txt", "r+");
    if (file == NULL) {
        printf("Error reading the file\n");
        return;
    }

    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error creating the temporary file\n");
        fclose(file);
        return;
    }

    studts student7;
    int StID;
    int found = 0;
    char line[250];

    // Copy the header to the temporary file
    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
            ID_WIDTH, "Student ID", PASS_WIDTH, "Password", NAME_WIDTH, "First Name", LAST_NAME_WIDTH, "Last Name",
            AGE_WIDTH, "Age", GENDER_WIDTH, "Gender", NATIONALITY_WIDTH, "Nationality", EMAIL_WIDTH, "Email",
            ADDRESS_WIDTH, "Address", COURSE_WIDTH, "Course");
    fprintf(temp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Read the header line from the original file
    fgets(line, 250, file);
    fgets(line, 250, file);

    // Display existing students
    student_view12();

    // Input student ID to update
    //printf("\nEnter the Student ID you want to update: ");
    printf("\nEnter ID=");
    scanf("%d", &StID);
    getchar(); // Consume newline

    // Read and update each student's information
    while (fgets(line, 250, file)) {
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
               &student7.Student_Id, student7.Password, student7.name, student7.Last_Name, &student7.age,
               student7.Gender, student7.Nationality, student7.email, student7.address, student7.course);

        // Check if the current line belongs to the student to be updated
        if (student7.Student_Id == StID) {
            found = 1;
            // Display options for updating student information
            printf("\n1. Name\n2. Last Name\n3. Password\n4. Age\n5. Gender\n6. Nationality\n7. Email\n8. Address\n");
            int choice;
            printf("Enter your choice: ");
            scanf("%d", &choice);
            getchar(); // Consume newline

            switch (choice) {
                case 1:
                    printf("Enter new First Name: ");
                    fgets(student7.name, sizeof(student7.name), stdin);
                    break;
                case 2:
                    printf("Enter new Last Name: ");
                    fgets(student7.Last_Name, sizeof(student7.Last_Name), stdin);
                    break;
                case 3:
                    printf("Enter new Password: ");
                    fgets(student7.Password, sizeof(student7.Password), stdin);
                    break;
                case 4:
                    printf("Enter new Age: ");
                    scanf("%d", &student7.age);
                    getchar(); // Consume newline
                    break;
                case 5:
                    printf("Enter new Gender: ");
                    fgets(student7.Gender, sizeof(student7.Gender), stdin);
                    break;
                case 6:
                    printf("Enter new Nationality: ");
                    fgets(student7.Nationality, sizeof(student7.Nationality), stdin);
                    break;
                case 7:
                    printf("Enter new Email: ");
                    fgets(student7.email, sizeof(student7.email), stdin);
                    break;
                case 8:
                    printf("Enter new Address: ");
                    fgets(student7.address, sizeof(student7.address), stdin);
                    break;
                default:
                    printf("Invalid choice\n");
                    fclose(file);
                    fclose(temp);
                    remove("tempfile.txt");
                    return;
            }
        }

        // Format the student information and write it to the temporary file
        file_format12(student7.name, NAME_WIDTH);
        file_format12(student7.Last_Name, LAST_NAME_WIDTH);
        file_format12(student7.Gender, GENDER_WIDTH);
        file_format12(student7.Nationality, NATIONALITY_WIDTH);
        file_format12(student7.email, EMAIL_WIDTH);
        file_format12(student7.address, ADDRESS_WIDTH);
        file_format12(student7.course, COURSE_WIDTH);
        file_format12(student7.Password, PASS_WIDTH);

        sprintf(line, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s\n",
                ID_WIDTH, student7.Student_Id, PASS_WIDTH, student7.Password, NAME_WIDTH, student7.name,
                LAST_NAME_WIDTH, student7.Last_Name, AGE_WIDTH, student7.age, GENDER_WIDTH, student7.Gender,
                NATIONALITY_WIDTH, student7.Nationality, EMAIL_WIDTH, student7.email, ADDRESS_WIDTH,
                student7.address, COURSE_WIDTH, student7.course);

        fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    // If student not found

    if (!found) {
        remove("tempfile.txt");  // Remove the temporary file if student not found
        printf("Student with ID %d not found.\n", StID);
        return;
    }
    remove("StuInfo.txt");
    rename("tempfile.txt", "StuInfo.txt");
    printf("Student information updated successfully.\n");
}

void remvoing_students(){
    FILE *file=fopen("StuInfo.txt","r+");
    if (file==NULL){
      printf("error opening the file");
      return;
    }
    FILE *temp=fopen("tempfile.txt","w");
    if(temp==NULL){
        printf("error opening the file");
        fclose(file);
        return;

    }
    studts student7;
    int Id_delete;
    int found= 0;
    char line[250];
    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
    ID_WIDTH, "Student ID",PASS_WIDTH ,"Password",  NAME_WIDTH,"First Name",LAST_NAME_WIDTH,"Last Name",AGE_WIDTH, "Age",GENDER_WIDTH,"Gender",
    NATIONALITY_WIDTH,"Nationality",EMAIL_WIDTH,"Email",ADDRESS_WIDTH,"Address", COURSE_WIDTH, "Course");
    fprintf(temp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    //skip reading the header file to avoid reading empty space
    fgets(line, 250, file);
    fgets(line, 250, file);
    student_view12();
    printf("Enter the student ID of which you want to delete:\n");
    scanf("%d",& Id_delete);
    getchar();

    while(fgets(line, 250, file)){
    sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
        &student7.Student_Id, student7.Password, student7.name, student7.Last_Name, &student7.age,
        student7.Gender, student7.Nationality, student7.email, student7.address, student7.course);
    if (student7.Student_Id == Id_delete) {
        found=1;
      }else{
        fprintf(temp,"%s",line);
      }
    }
    fclose(file);
    fclose(temp);


    if(!found){
      printf("Student not found");
    }
    else{
      printf("........student information deleted successfully.......\n");
    }

    remove("StuInfo.txt");
    rename("tempfile.txt","StuInfo.txt");

}


void AssignCourse12() {
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

    student_view12();

    studts student7;
    char line[250];
    int studentID, found = 0;
    char *courseID, tempcourse[10];

    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
    ID_WIDTH, "Student ID",PASS_WIDTH ,"Password",  NAME_WIDTH,"First Name",LAST_NAME_WIDTH,"Last Name",AGE_WIDTH, "Age",GENDER_WIDTH,"Gender",
    NATIONALITY_WIDTH,"Nationality",EMAIL_WIDTH,"Email",ADDRESS_WIDTH,"Address", COURSE_WIDTH, "Course");
    fprintf(temp, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


    fgets(line, 250, file);
    fgets(line, 250, file);

    printf("Enter Student ID: ");
    scanf("%d", &studentID);
    getchar(); // Consume newline


    while(fgets(line, 250, file)){
    sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
        &student7.Student_Id, student7.Password, student7.name, student7.Last_Name, &student7.age,
        student7.Gender, student7.Nationality, student7.email, student7.address, student7.course);


        student7.course[strcspn(student7.course, "\n")] = '\0';
        student7.course[strcspn(student7.course, " ")] = '\0';


        if (student7.Student_Id == studentID) {
          printf("Enter Course ID to assign: ");
          fgets(tempcourse,65,stdin);
          tempcourse[strcspn(tempcourse, "\n")]='\0';

          if (strcmp(student7.course, "0") == 0) {
            printf("\nx\n");
            strcpy(student7.course, tempcourse);
            found = 1;
          }
          else {
            strcat(student7.course, ", ");
            strcat(student7.course, tempcourse);
            found = 1;
            printf("%s", student7.course);
          }

        }


    file_format12(student7.name, NAME_WIDTH);
    file_format12(student7.Last_Name, LAST_NAME_WIDTH);
    file_format12(student7.Gender, GENDER_WIDTH);
    file_format12(student7.Nationality, NATIONALITY_WIDTH);
    file_format12(student7.email, EMAIL_WIDTH);
    file_format12(student7.address,  ADDRESS_WIDTH);
    file_format12(student7.course, COURSE_WIDTH);
    file_format12(student7.Password, PASS_WIDTH);

          sprintf(line, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s | %-*s\n",
              ID_WIDTH, student7.Student_Id, PASS_WIDTH, student7.Password, NAME_WIDTH, student7.name, LAST_NAME_WIDTH, student7.Last_Name,
              AGE_WIDTH, student7.age, GENDER_WIDTH, student7.Gender, NATIONALITY_WIDTH, student7.Nationality,
              EMAIL_WIDTH, student7.email, ADDRESS_WIDTH, student7.address, COURSE_WIDTH, student7.course);
              fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        remove("tempfile.txt");
        printf("Student not found.\n");
        return;
    }

    remove("StuInfo.txt");
    rename("tempfile.txt", "StuInfo.txt");

    printf("Course assigned successfully.\n");
}



int managestudents(){
    int exist=1;
    int width = 50; // Adjust the width as needed
    int choice;

    while (exist == 1){
        // Print the top border of the box
        printf("+");
        for (int i = 0; i < width; ++i) printf("-");
        printf("+\n");

        // Print the menu options, left-justified within the border
        printf("| %-49s |\n", "1- Adding Students:");
        printf("| %-49s |\n", "2- Removing Students:");
        printf("| %-49s |\n", "3 - Assign Course:");
        printf("| %-49s |\n", "4 - update studentinfo:");
        printf("| %-49s |\n", "5- Exit:");

        // Print the bottom border of the box
        printf("+");
        for (int i = 0; i < width; ++i) printf("-");
        printf("+\n");
        printf("\n\n Enter your choice:\n");
        scanf("%d",&choice);
        getchar();
        if(choice ==1){
          Personal_Details();
        }else if (choice ==2){
          remvoing_students();
        }else if(choice ==3){
           AssignCourse12();
        }
        else if(choice == 4) {
          printf("*********************************************\n");
          printf("Enter the Student ID you want to update:\n");
          printf("*********************************************\n");
          updateStuInfo();

        }else if (choice == 5)
        {
          printf("Exiting.......");
          exist = 0;
        }
        else {
          printf("Incorrect number entered\n");
        }
    }



    return 0;
}
void retrieveAttendanceInfoforstudent(const char *fileName) {
    int studentID;
    printf("Enter your student ID to retrieve attendance: ");
    scanf("%d", &studentID);
    getchar();

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
