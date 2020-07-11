#pragma warning(disable: 4996)

#include <string>
#include <stdlib.h>
#include <time.h>

/*
 * Name: Trevor Benyack
 * Date: 2020-07-11
 * Class: CIT-145-Z01B
 * Assignment 07
 * Notes: This program uses a data file to store a tools inventory. The data stored for each tool
 * is the name of the tool, price, and quantity. The user can choose to add a new tool or update an
 * existing tool to/in the inventory, delete a tool from the inventory, or list all the tools in the
 * inventory.
 */

unsigned int TOTAL_RECORDS = 100;

struct toolData {
    unsigned int toolId;
    char name[50];
    double price;
    unsigned int quantity;
};

void addUpdateTool(FILE *fPtr);

void deleteTool(FILE *fPtr);

void printInventory(FILE *readPtr);

int main(void) {

    FILE *ifPtr; // hardware.dat file pointer

    // initialize hardware.dat if it does not exist
    if ((ifPtr = fopen("hardware.dat", "r")) == NULL) {

        fclose(ifPtr);

        ifPtr = fopen("hardware.dat", "wb");

        for (int i = 0; i < TOTAL_RECORDS; ++i) {
            fseek(ifPtr, (i) * sizeof(struct toolData), SEEK_SET);
            struct toolData emptyRecord = {0, "", 0, 0};
            fwrite(&emptyRecord, sizeof(struct toolData), 1, ifPtr);
        }
        fclose(ifPtr);
    }

    if ((ifPtr = fopen("hardware.dat", "rb+")) == NULL) {
        puts("File could not be opened.");
    } else {
        unsigned int menuSelection;

        do {
            printf("%s", "\nEnter request\n"
                         "1 - Input new tool or update an existing tool\n"
                         "2 - Delete a tool\n"
                         "3 - List all tools\n"
                         "4 - Exit\n"
                         "? ");

            scanf("%u", &menuSelection);

            switch (menuSelection) {
                case 1:
                    addUpdateTool(ifPtr);
                    break;
                case 2:
                    deleteTool(ifPtr);
                    break;
                case 3:
                    printInventory(ifPtr);
                    break;
                case 4:
                    break;
                default:
                    puts("Incorrect selection. Please try again.");
                    break;

            }
        } while ((menuSelection != 4)); // end exit do-while loop

        fclose(ifPtr);

    } // end fopen conditional structure

    // UNCOMMENT THIS BEFORE SUBMITTING
    system("pause");
    return 0;
}

void addUpdateTool(FILE *fPtr) {

    unsigned int toolId;

    do {

        printf("%s", "\nEnter record number (1 to 100, 0 to return to main menu)\n? ");
        scanf("%u", &toolId);
        if (toolId != 0) {
            // moves file pointer to the corresponding record in file
            fseek(fPtr, (toolId - 1) * sizeof(struct toolData), SEEK_SET);

            // create toolData with no information
            struct toolData tool = {0, "", 0, 0};

            printf("%s", "\nEnter tool name, quantity, and cost\n? ");
            tool.toolId = toolId;
            scanf("%s%u%lf", &tool.name, &tool.quantity, &tool.price);

            // write toolData to file
            fwrite(&tool, sizeof(struct toolData), 1, fPtr);
        }

    } while (toolId != 0);

}

void deleteTool(FILE *fPtr) {

    unsigned int toolId;

    do {

        printf("%s", "\nEnter record number to delete (1 to 100, 0 to return to main menu)\n? ");
        scanf("%u", &toolId);
        if (toolId != 0) {

            // This section prints a deletion confirmation to the user

            // moves file pointer to the record to be deleted in file
            fseek(fPtr, (toolId - 1) * sizeof(struct toolData), SEEK_SET);

            // create toolData with no information
            struct toolData tool = {0, "", 0, 0};

            // read tool data
            fread(&tool, sizeof(struct toolData), 1, fPtr);

            printf("%s%s%s", "\nThe tool \"", tool.name, "\" has been deleted.\n");

            // This section deletes the selected tool

            tool = {0, "", 0, 0};

            // moves file pointer to the record to be deleted in file
            fseek(fPtr, (toolId - 1) * sizeof(struct toolData), SEEK_SET);

            // write toolData to file
            fwrite(&tool, sizeof(struct toolData), 1, fPtr);
        }

    } while (toolId != 0);

}

void printInventory(FILE *readPtr) {

    int toolId = 0;

    printf("%s", "\nRecord #:  Tool name:          Quantity:  Cost:\n");
    while (toolId < TOTAL_RECORDS) {

        // moves file pointer to the corresponding record in file
        fseek(readPtr, (toolId) * sizeof(struct toolData), SEEK_SET);

        // create toolData with no information
        struct toolData tool = {0, "", 0, 0};

        // read tool data
        fread(&tool, sizeof(struct toolData), 1, readPtr);

        // print tool data
        if (tool.toolId != 0) {
            printf("%-11d%-20s%-11u%-7.2lf\n", tool.toolId, tool.name, tool.quantity, tool.price);
        }

        toolId++;

    }

}