#include "menu.h"

void displayMenu(FILE *ms)
{
    int choice;
    do
    {
        printf("\n====== MENU ======\n");
        printf("1. Initialize Disk\n");
        printf("2. Display Allocation Table\n");
        printf("3. Display Metadata Blocks\n");
        printf("4. Display Main Blocks\n");
        printf("5. Clear Disk\n");
        printf("6. Generate Random Students\n");
        printf("7. Exit\n");
        printf("===================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            initDisk(ms);
            printf("Disk initialized successfully.\n");
            break;
        case 2:
            printAllocationTable(ms);
            break;
        case 3:
            printMetaDonneesBloc(ms);
            break;
        case 4:
            printMainBlocs(ms);
            break;
        case 5:
            viderMS(&ms);
            printf("Disk cleared successfully.\n");
            break;
        case 6:
        {
            int numStudents;
            printf("Enter the number of random students to generate: ");
            scanf("%d", &numStudents);

            Etudiant *students = (Etudiant *)malloc(sizeof(Etudiant) * numStudents);
            generateRandomEtudiants(students, numStudents);

            printf("\nGenerated Students:\n");
            for (int i = 0; i < numStudents; i++)
            {
                printEtudiant(students[i]);
            }

            free(students);
            break;
        }
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
}
