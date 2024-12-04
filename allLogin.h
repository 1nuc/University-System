#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define MAX_ID_LENGTH 20//student
#define MAX_PASSWORD_LENGTH 20

#define LECNAME_WIDTH 30//lec
#define LECID_WIDTH 15
#define LOGPASS_WIDTH 30
#define LECAGE_WIDTH 15

#define LOGID_WIDTH 20 //admin program
#define LOGNAME_WIDTH 20
#define LOGLAST_NAME_WIDTH 20
#define LOGAGE_WIDTH 5
#define LOGGENDER_WIDTH 10
#define LOGNATIONALITY_WIDTH 15
#define LOGEMAIL_WIDTH 30
#define LOGADDRESS_WIDTH 40

typedef struct Lecturer {
    int id;
    char name[LECNAME_WIDTH];
    int age;
    char password[LOGPASS_WIDTH];
} Lecturer;

typedef struct {
    char id[20];
    char password[20];
} SystemAdmin;

typedef struct student{
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
 } Stu;

typedef struct {
    int padmin_Id;
    char password[50];
    char name[50];
    char last_name[50];
    int age;
    char gender[50];
    char nationality[50];
    char email[50];
    char address[50];
} Padmin;

bool LoginPadmin() {
    int enteredId;
    char enteredPassword[50];

    printf("Enter your Program Admin ID:\n");
    scanf("%d", &enteredId);
    getchar();  // Consume newline

    printf("Enter your Password:\n");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strlen(enteredPassword) - 1] = '\0';  // Remove newline

    FILE *file = fopen("PadminInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return false;
    }

    Padmin padmin;
    char line[500];
    // Skip the header lines
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^|] | %49[^|] | %49[^\n]",
               &padmin.padmin_Id, padmin.password, padmin.name, padmin.last_name,
               &padmin.age, padmin.gender, padmin.nationality, padmin.email, padmin.address);

        // Trim trailing whitespace or newline characters in password
        size_t len = strlen(padmin.password);
        while (len > 0 && (padmin.password[len - 1] == '\n' || padmin.password[len - 1] == ' ')) {
            padmin.password[--len] = '\0';
        }

        // Debugging output
        //printf("Read ID: %d, Password: '%s'\n", padmin.padmin_Id, padmin.password);

        if (padmin.padmin_Id == enteredId && strcmp(padmin.password, enteredPassword) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

//need to change once pass changed to char
bool LoginStudent() {
    int enteredId;
    char enteredPassword[50];

    printf("Enter your Student ID:\n");
    scanf("%d", &enteredId);
    getchar();  // Consume newline

    printf("Enter your Password:\n");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strlen(enteredPassword) - 1] = '\0';  // Remove newline

    FILE *file = fopen("StuInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return false;
    }

    Stu student;
    char line[500];
    // Skip the header lines
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %99[^|] | %99[^\n]",
        &student.Student_Id, student.Password, student.name, student.Last_Name, &student.age,
        student.Gender, student.Nationality, student.email, student.address, student.course);

        // Trim trailing whitespace or newline characters in password
        size_t len = strlen(student.Password);
        while (len > 0 && (student.Password[len - 1] == '\n' || student.Password[len - 1] == ' ')) {
            student.Password[len - 1] = '\0';
            len--;
        }

        if (student.Student_Id == enteredId && strcmp(student.Password, enteredPassword) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}

bool LoginSystemAdmin() {
    SystemAdmin admin = {"systemadmin1", "systemadmin123"};
    char enteredId[20];
    char enteredPassword[20];

    printf("Enter your System Admin ID:\n");
    scanf("%s", enteredId);

    printf("Enter your Password:\n");
    scanf("%s", enteredPassword);

    if (strcmp(admin.id, enteredId) == 0 && strcmp(admin.password, enteredPassword) == 0) {
        return true;
    }

    return false;
}

bool LoginLecturer() {
    int enteredId;
    char enteredPassword[LOGPASS_WIDTH];

    printf("Enter your Lecturer ID:\n");
    scanf("%d", &enteredId);
    getchar();  // Consume newline

    printf("Enter your Password:\n");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strlen(enteredPassword) - 1] = '\0';  // Remove newline

    FILE *file = fopen("lecturer_info.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return false;
    }

    Lecturer lecturer;
    char line[256];
    // Skip the header line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "| %d | %[^|] | %d | %[^|] |", &lecturer.id, lecturer.name, &lecturer.age, lecturer.password);

        // Trim trailing whitespace or newline characters in password
        size_t len = strlen(lecturer.password);
        while (len > 0 && (lecturer.password[len - 1] == '\n' || lecturer.password[len - 1] == ' ')) {
            lecturer.password[--len] = '\0';
        }

        if (lecturer.id == enteredId && strcmp(lecturer.password, enteredPassword) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
