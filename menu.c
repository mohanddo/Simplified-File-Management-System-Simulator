#include "menu.h"

void displayMenu(FILE *ms)
{
    int choice;
    do
    {
        printf("\n====== MENU ======\n");
        printf("1. Display Allocation Table\n");
        printf("2. Display Metadata Blocks\n");
        printf("3. Display Main Blocks\n");
        printf("4. Display File\n");
        printf("5. Clear Disk\n");
        printf("6. Create File\n");
        printf("7. Rename File\n");
        printf("8. Delete File\n");
        printf("9. Search student By Id\n");
        printf("10. Delete Student\n");
        printf("11. Exit\n");
        printf("===================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printAllocationTable(ms);
            break;
        case 2:
            printMetaDonneesBloc(ms);
            break;
        case 3:
            printMainBlocs(ms);
            break;
        case 4:
            printFichier(ms);
            break;
        case 5:
            viderMS(&ms);
            printf("Disk cleared successfully.\n");
            break;
        case 6:
            creerFichier(ms);
            break;

        case 7:
            renommerFichier(ms);
            break;

        case 8:
            supprimerFichier(ms);
            break;

        case 9:
            rechercherEtudiantParId(ms);
            break;

        case 10:
            suppressionLogiqueEtudiant(ms);
            break;

        case 11:
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 11);
}
