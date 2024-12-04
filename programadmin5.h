#define PA_ID_WIDTH 20
#define PA_PASS_WIDTH 15
#define PA_NAME_WIDTH 20
#define PA_LAST_NAME_WIDTH 20
#define PA_AGE_WIDTH 5
#define PA_GENDER_WIDTH 10
#define PA_NATIONALITY_WIDTH 15
#define PA_EMAIL_WIDTH 30
#define PA_ADDRESS_WIDTH 40

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
} Padmin3;

void SavePadminInfo(Padmin3 padmin) {
    FILE *file = fopen("PadminInfo.txt", "a");
    if (file == NULL) {
        printf("Error opening the file");
        return;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    if (size == 0) {
        fprintf(file, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
                PA_ID_WIDTH, "Program Admin ID", PA_PASS_WIDTH, "Password", PA_NAME_WIDTH, "Name", PA_LAST_NAME_WIDTH, "Last Name",
                PA_AGE_WIDTH, "Age", PA_GENDER_WIDTH, "Gender", PA_NATIONALITY_WIDTH, "Nationality",
                PA_EMAIL_WIDTH, "Email", PA_ADDRESS_WIDTH, "Address");
        fprintf(file, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
    fprintf(file, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s \n",
            PA_ID_WIDTH, padmin.padmin_Id, PA_PASS_WIDTH, padmin.password, PA_NAME_WIDTH, padmin.name, PA_LAST_NAME_WIDTH, padmin.last_name,
            PA_AGE_WIDTH, padmin.age, PA_GENDER_WIDTH, padmin.gender, PA_NATIONALITY_WIDTH, padmin.nationality,
            PA_EMAIL_WIDTH, padmin.email, PA_ADDRESS_WIDTH, padmin.address);
    fclose(file);
}

void Personal_Details1() {
    char buffer[255];
    Padmin3 padmin;
    while (1) {
        printf("What is your name:\n");
        fgets(padmin.name, 50, stdin);
        padmin.name[strlen(padmin.name) - 1] = '\0';

        printf("What is your last name:\n");
        fgets(padmin.last_name, 50, stdin);
        padmin.last_name[strlen(padmin.last_name) - 1] = '\0';

        printf("How old are you:\n");
        fgets(buffer, 50, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        padmin.age = atoi(buffer);

        printf("Write down your ID please:\n");
        fgets(buffer, 50, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        padmin.padmin_Id = atoi(buffer);

        printf("Please write your password:\n");
        fgets(padmin.password, 50, stdin);
        padmin.password[strlen(padmin.password) - 1] = '\0';

        printf("What is your Gender:\n");
        fgets(padmin.gender, 50, stdin);
        padmin.gender[strlen(padmin.gender) - 1] = '\0';

        printf("What is your nationality:\n");
        fgets(padmin.nationality, 50, stdin);
        padmin.nationality[strlen(padmin.nationality) - 1] = '\0';

        printf("Write your email:\n");
        fgets(padmin.email, 50, stdin);
        padmin.email[strlen(padmin.email) - 1] = '\0';

        printf("Write down your address please:\n");
        fgets(padmin.address, 50, stdin);
        padmin.address[strlen(padmin.address) - 1] = '\0';

        SavePadminInfo(padmin);

        printf("Finish assigning admin information. Enter 1 to assign another or 2 to exit:");
        int choice;
        scanf("%d", &choice);
        getchar();

        if (choice != 1) {
            break;
        }
    }
}

void ViewInfo9() {
    FILE *file = fopen("PadminInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}


void file_format9(char * format, size_t length){
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

void UpdatePadminInfo() {
    FILE *file = fopen("Padmininfo.txt", "r+");
    if (file == NULL) {
        printf("Error reading the file");
        return;
    }
    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error reading the temporary file");
        fclose(file);
        return;
    }

    Padmin3 padmin;
    int PaID;
    int choice;
    int found = 0;
    char line[250];
    fprintf(temp, "%-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s \n",
            PA_ID_WIDTH, "Program Admin ID", PA_PASS_WIDTH, "Password", PA_NAME_WIDTH, "First Name", PA_LAST_NAME_WIDTH, "Last Name",
            PA_AGE_WIDTH, "Age", PA_GENDER_WIDTH, "Gender", PA_NATIONALITY_WIDTH, "Nationality", PA_EMAIL_WIDTH, "Email",
            PA_ADDRESS_WIDTH, "Address");
    fprintf(temp, "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Skip reading the header file to avoid reading empty space
    fgets(line, 250, file);
    fgets(line, 250, file);
    ViewInfo9();

    printf("\nEnter the Program Admin ID of which you want to update:\n");
    scanf("%d", &PaID);
    getchar();

    while (fgets(line, 250, file)) {
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %9[^|] | %19[^|] | %49[^|] | %49[^\n]",
               &padmin.padmin_Id, padmin.password, padmin.name, padmin.last_name, &padmin.age,
               padmin.gender, padmin.nationality, padmin.email, padmin.address);

        if (padmin.padmin_Id == PaID) {
            found = 1;
            printf("1. Name\n2. Last Name\n3. Password\n4. Age\n5. Gender\n6. Nationality\n7. Email\n8. Address\n");
            if (scanf("%d", &choice) != 1) {
                printf("Invalid input\n");
                fclose(file);
                fclose(temp);
                remove("tempfile.txt");
                return;
            }
            getchar(); // Consume newline to avoid jumping specific lines

            switch (choice) {

                case 1:
                    printf("Enter new First Name: ");
                    fgets(padmin.name, sizeof(padmin.name), stdin);
                    break;

                case 2:
                    printf("Enter new Last Name: ");
                    fgets(padmin.last_name, sizeof(padmin.last_name), stdin);
                    break;

                case 3:
                    printf("Enter new Password: ");
                    fgets(padmin.password, sizeof(padmin.password), stdin);
                    break;

                case 4:
                    printf("Enter new Age: ");
                    if (scanf("%d", &padmin.age) != 1) {
                        printf("Invalid input\n");
                        fclose(file);
                        fclose(temp);
                        remove("tempfile.txt");
                        return;
                    }
                    getchar(); // Consume newline
                    break;

                case 5:
                    printf("Enter new Gender: ");
                    fgets(padmin.gender, sizeof(padmin.gender), stdin);
                    break;

                case 6:
                    printf("Enter new Nationality: ");
                    fgets(padmin.nationality, sizeof(padmin.nationality), stdin);
                    break;
                case 7:
                    printf("Enter new Email: ");
                    fgets(padmin.email, sizeof(padmin.email), stdin);
                    break;
                case 8:
                    printf("Enter new Address: ");
                    fgets(padmin.address, sizeof(padmin.address), stdin);
                    break;
                default:
                    printf("Invalid choice\n");
                    fclose(file);
                    fclose(temp);
                    remove("tempfile.txt");
                    return;
            }
        }


    file_format9(padmin.name, PA_NAME_WIDTH);
    file_format9(padmin.password, PA_PASS_WIDTH);
    file_format9(padmin.last_name, PA_LAST_NAME_WIDTH);
    file_format9(padmin.gender, PA_GENDER_WIDTH);
    file_format9(padmin.nationality, PA_NATIONALITY_WIDTH);
    file_format9(padmin.email, PA_EMAIL_WIDTH);
    file_format9(padmin.address, PA_ADDRESS_WIDTH);

    sprintf(line, "%-*d | %-*s | %-*s | %-*s | %-*d | %-*s | %-*s | %-*s | %-*s\n",
            PA_ID_WIDTH, padmin.padmin_Id, PA_PASS_WIDTH, padmin.password, PA_NAME_WIDTH, padmin.name, PA_LAST_NAME_WIDTH, padmin.last_name,
            PA_AGE_WIDTH, padmin.age, PA_GENDER_WIDTH, padmin.gender, PA_NATIONALITY_WIDTH, padmin.nationality, PA_EMAIL_WIDTH, padmin.email, PA_ADDRESS_WIDTH, padmin.address);
            fprintf(temp, "%s", line);
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        remove("tempfile.txt");
        printf("Program admin with ID %d not found.\n", PaID);
    } else {
        remove("PadminInfo.txt");
        rename("tempfile.txt", "PadminInfo.txt");
        printf("Program admin information updated successfully.\n");
    }
}





void RemovePadmin() {
    FILE *file = fopen("PadminInfo.txt", "r");
    if (file == NULL) {
        printf("Error opening the file\n");
        return;
    }
    FILE *temp = fopen("tempfile.txt", "w");
    if (temp == NULL) {
        printf("Error opening the temporary file\n");
        fclose(file);
        return;
    }

    ViewInfo9();
    printf("Enter the Admin ID you want to delete:\n");
    int id;
    scanf("%d", &id);
    getchar();

    Padmin3 padmin;
    int found = 0;
    char line[500];
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d | %49[^|] | %49[^|] | %49[^|] | %d | %49[^|] | %49[^|] | %49[^|] | %49[^\n]",
               &padmin.padmin_Id, padmin.password, padmin.name, padmin.last_name,
               &padmin.age, padmin.gender, padmin.nationality, padmin.email, padmin.address);

        if (padmin.padmin_Id != id) {
            fprintf(temp, "%s", line);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp);

    if (!found) {
        remove("tempfile.txt");
        printf("Admin with ID %d not found.\n", id);
    } else {
        remove("PadminInfo.txt");
        rename("tempfile.txt", "PadminInfo.txt");
        printf("Admin information deleted successfully.\n");
    }
}

int manageprogrameadmin() {
    int choice;
    do {
        printf("====================\n");
        printf("1- Add Admin\n2- Remove Admin\n3- Update Admin Info\n4- View All Admins\n5- Exit\nEnter your choice: ");
        printf("====================\n");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                Personal_Details1();
                break;
            case 2:
                RemovePadmin();
                break;
            case 3:
                UpdatePadminInfo();
                break;
            case 4:
                ViewInfo9();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice, please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

