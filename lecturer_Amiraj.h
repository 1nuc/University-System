#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define LECNAME_WIDTH 30
#define LECID_WIDTH 15
#define LECPASS_WIDTH 30
#define LECAGE_WIDTH 15
#define MAX_LECTURERS 100

typedef struct Lecturer22 {
    char name[LECNAME_WIDTH];
    int age;
    int id;
    char password[LECPASS_WIDTH];
} Lecturer22;

void saveLecturerInfo(Lecturer22 lecturer) {
    FILE *file = fopen("lecturer_info.txt", "a");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    if (fileSize == 0) {
        fprintf(file, "| %-*s | %-*s | %-*s | %-*s |\n",
        LECID_WIDTH, "Lecturer ID", LECNAME_WIDTH, "Lecturer Name", LECAGE_WIDTH, "Age", LECPASS_WIDTH, "Password");
        fprintf(file, "+-----------------+--------------------------------+-----------------+--------------------------------+\n");
    }

    fprintf(file, "| %-*d | %-*s | %-*d | %-*s |\n",
                            LECID_WIDTH, lecturer.id, LECNAME_WIDTH, lecturer.name, LECAGE_WIDTH, lecturer.age,
                            LECPASS_WIDTH, lecturer.password);
    fclose(file);
}

void creating_lecturers() {
    Lecturer22 lecturer;
    int choice;

    while(1) {

        printf("Enter lecturer's ID: ");
        scanf("%d", &lecturer.id);
        printf("\n");

        printf("Enter lecturer's name: ");
        getchar();
        fgets(lecturer.name, sizeof(lecturer.name), stdin);
        lecturer.name[strcspn(lecturer.name, "\n")] = '\0';
        printf("\n");

        printf("Enter lecturer's age: ");
        scanf("%d", &lecturer.age);
        printf("\n");

        printf("Enter lecturer's password: ");
        scanf("%s", lecturer.password);
        printf("\n");

        saveLecturerInfo(lecturer);

        printf("Do you want to add another lecturer? Enter 1 to continue or 2 to exit: ");
        scanf("%d", &choice);

        while (choice != 1 && choice != 2) {
            printf("Invalid operation");
        }
        if (choice == 2) {
                break;
        }
    }
}

void ViewInfo23(char * file_name){
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

void file_formats(char * format, size_t length){
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

void lecturer_view(){
    ViewInfo23("lecturer_info.txt");
}

int File_Readings(FILE *file, int *LecturerID){
    int found=0;
    Lecturer22 lecturer;
    char line[250];
    while(fgets(line, 250, file)){
        sscanf(line, "| %d | %99[^|] | %d | %99[^|] |\n",
                        lecturer.id, lecturer.name, lecturer.age, lecturer.password);

        //continuesly reading the file
        //specifies the format for reading the file
        ////%: Indicates a format specifier.
        //49: Specifies the maximum number of characters to read. In this case, it's 49 characters.
        //[^|]: Indicates that the input should read characters until a pipe character | is encountered.
        //The ^ inside the brackets [] is a negation operator, meaning any character except | will be read.
        // useful because it automatically trims any leading spaces from the input string.
        if(*LecturerID == lecturer.id){

            printf("Student found......\n\n");
            fprintf(file, "| %-*s | %-*s | %-*s | %-*s |\n",
                    LECID_WIDTH, "Lecturer ID", LECNAME_WIDTH, "Lecturer Name", LECAGE_WIDTH,
                    "Age", LECPASS_WIDTH, "Password");
            fprintf(file, "+-----------------+--------------------------------+-----------------+--------------------------------+\n");

            printf("%s",line);
            found=1;
            break;
        }
    }

    return found;
}


void delete_lecturer() {
    FILE *file = fopen("lecturer_info.txt", "r");
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

    Lecturer22 lecturer;
    int LecturerID;
    int found = 0;
    char header[256], Lecdelete;
    char line[256];

    lecturer_view();

    fprintf(temp, "| %-*s | %-*s | %-*s | %-*s |\n",
                    LECID_WIDTH, "Lecturer ID", LECNAME_WIDTH, "Lecturer Name", LECAGE_WIDTH,
                    "Age", LECPASS_WIDTH, "Password");

    fgets(header, sizeof(header), file); // Read and discard the header line

    printf("\nEnter the Lecturer ID to be deleted: ");
    scanf("%d", &LecturerID);
    getchar();

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "| %d | %[^|] | %d | %[^|] |\n",
              &lecturer.id, lecturer.name, &lecturer.age,
              lecturer.password);

        if (lecturer.id == LecturerID) {
            printf("\n\nLecturer ID: %d\nLecturer Name: %s\nLecturer Age: %d\nLecturer Password: %s\n\n",
            lecturer.id, lecturer.name, lecturer.age, lecturer.password);

            printf("\nDo you want to remove this Lecturer?(y/n) ");
            scanf(" %c", &Lecdelete);
            getchar();

            while (Lecdelete != 'y' && Lecdelete != 'n') {
                printf("\nInvalid choice! Please enter 'y' or 'n': ");
                scanf("%c", &Lecdelete);
                getchar();
            }

            if (Lecdelete == 'y') {
                found = 1;
            }
        }

        else {
            fprintf(temp, "%s", line); // Write the line to the temporary file
        }
    }

    fclose(file);
    fclose(temp);

    if (found == 1) {
        remove("lecturer_info.txt");
        rename("tempfile.txt", "lecturer_info.txt");
        printf("\nLecturer Removed Successfully!\n");
    }
    else {
        remove("tempfile.txt");
        printf("\nLecturer not Removed!\n");
    }
}



void search_lecturer() {
    FILE *file = fopen("lecturer_info.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }

    char buffer[1000];
    bool found = false;
    int lecturerID;
    printf("Enter lecturer ID to search: ");
    scanf("%d", &lecturerID);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "ID:") != NULL) {
            int current_id;
            sscanf(buffer, "ID: %d", &current_id);
            if (current_id == lecturerID) { // Corrected comparison here
                found = true;
                printf("%s", buffer); // Print ID
                 // Print the lines until a blank line is found
                while (fgets(buffer, sizeof(buffer), file) != NULL && strcmp(buffer, "\n") != 0) {
                    printf("%s", buffer); // Print each line
                }
                break; // No need to continue searching if found
            }
        }
    }

    fclose(file);

    if (!found)
        printf("Lecturer with ID %d not found.\n", lecturerID);
}





int managelecturer() {
    char choice;

    do {
        printf("========================\n");
        printf("\n1. Add a new lecturer\n");
        printf("2. Delete a lecturer\n");
        printf("3. Search for a lecturer\n");
        printf("4. Exit\n");
        printf("========================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': {
                creating_lecturers();
                break;
            }
            case '2': {
                delete_lecturer();
                break;
            }
            case '3': {
                lecturer_view();
                search_lecturer();
                break;
            }
            case '4':
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != '4');

    return 0;
}
