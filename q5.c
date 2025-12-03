#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main() {
    int Choice;
    int numOfLines = 0;

    char **buffer = NULL;     
    char Temp[5000];
    char fileName[50];
    int index;

    do {
        printf("SELECT AN OPTION:\n");
        printf("1) Add a new Line (at the End)\n");
        printf("2) Insert a Line at Index\n");
        printf("3) Delete a Line\n");
        printf("4) Show all lines\n");
        printf("5) Save to file\n");
        printf("6)Load from file(Clear Previous)\n");
        printf("7) Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &Choice);

        switch (Choice) {

        // ---------------------------------------------------------------------
        case 1: {
            printf("Enter the line to add: ");
            scanf(" %[^\n]", Temp);

            char **newBuffer = realloc(buffer, (numOfLines + 1) * sizeof(char *));
            if (!newBuffer) {
                printf("REALLOC ERROR: %s\n", strerror(errno));
                break;
            }
            buffer = newBuffer;

            buffer[numOfLines] = malloc(strlen(Temp) + 1);
            strcpy(buffer[numOfLines], Temp);

            numOfLines++;

            printf("LINE ADDED.\n\n");
            break;
        }

        // ---------------------------------------------------------------------
        case 2:
            if (numOfLines == 0)
                printf("BUFFER EMPTY, INSERT WILL ADD FIRST LINE.\n");

            printf("ENTER INDEX (1..%d): ", numOfLines + 1);
            scanf("%d", &index);

            if (index < 1 || index > numOfLines + 1) {
                printf("INDEX OUT OF RANGE!\n\n");
                break;
            }

            printf("ENTER THE LINE TO INSERT: ");
            scanf(" %[^\n]", Temp);

            buffer = realloc(buffer, (numOfLines + 1) * sizeof(char *));
            if (!buffer) {
                printf("REALLOC ERROR!\n");
                return 0;
            }

            // shift forward
            memmove(&buffer[index], &buffer[index - 1],
                    (numOfLines - (index - 1)) * sizeof(char *));

            buffer[index - 1] = malloc(strlen(Temp) + 1);
            strcpy(buffer[index - 1], Temp);

            numOfLines++;
            printf("LINE INSERTED.\n\n");
            break;

        // ---------------------------------------------------------------------
        case 3:
            if (numOfLines == 0) {
                printf("BUFFER IS EMPTY!\n\n");
                break;
            }

            printf("ENTER INDEX TO DELETE (1..%d): ", numOfLines);
            scanf("%d", &index);

            if (index < 1 || index > numOfLines) {
                printf("INVALID INDEX!\n\n");
                break;
            }

            free(buffer[index - 1]);

            memmove(&buffer[index - 1], &buffer[index],
                    (numOfLines - index) * sizeof(char *));

            numOfLines--;
            buffer = realloc(buffer, numOfLines * sizeof(char *));

            printf("LINE DELETED.\n\n");
            break;

        // ---------------------------------------------------------------------
        case 4:
            if (numOfLines == 0) {
                printf("NO LINES TO DISPLAY!\n\n");
                break;
            }
            for (int i = 0; i < numOfLines; i++)
                printf("%d: %s\n", i + 1, buffer[i]);
            printf("\n");
            break;

        // ---------------------------------------------------------------------
        case 5: {
            printf("ENTER FILE NAME: ");
            scanf("%s", fileName);

            FILE *fp = fopen(fileName, "w");
            if (!fp) {
                printf("FILE ERROR: %s\n", strerror(errno));
                break;
            }

            for (int i = 0; i < numOfLines; i++)
                fprintf(fp, "%s\n", buffer[i]);

            fclose(fp);
            printf("SAVED.\n\n");
            break;
        }

        // ---------------------------------------------------------------------
        case 6: {
            printf("ENTER FILE NAME: ");
            scanf("%s", fileName);

            FILE *fp = fopen(fileName, "r");
            if (!fp) {
                printf("FILE ERROR: %s\n", strerror(errno));
                break;
            }

            
            for (int i = 0; i < numOfLines; i++)
                free(buffer[i]);
            free(buffer);

            buffer = NULL;
            numOfLines = 0;

            while (fgets(Temp, sizeof(Temp), fp)) {
                Temp[strcspn(Temp, "\n")] = 0;

                buffer = realloc(buffer, (numOfLines + 1) * sizeof(char *));
                buffer[numOfLines] = malloc(strlen(Temp) + 1);
                strcpy(buffer[numOfLines], Temp);

                numOfLines++;
            }

            fclose(fp);
            printf("LOADED %d LINES.\n\n", numOfLines);
            break;
        }

        // ---------------------------------------------------------------------
        case 7:
            printf("EXITING...\n");
            break;

        default:
            printf("Invalid Option!\n");
        }

    } while (Choice != 7);


    for (int i = 0; i < numOfLines; i++)
        free(buffer[i]);
    free(buffer);

    return 0;
}