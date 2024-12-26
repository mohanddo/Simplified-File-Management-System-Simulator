#include <stdio.h>
#include "MS.h"
#include "utils.h"
#include "fichier.h"

int main()
{
    FILE *ms = fopen("ms.bin", "wb+");
    initDisk(ms);

    // printAllocationTable(ms);
    creerFichier(ms);
    // printAllocationTable(ms);
    printMetaDonneesBloc(ms);
    renommerFichier(ms, "SectionA.txt", "SectionB.txt");
    printMetaDonneesBloc(ms);
    // printMainBlocs(ms);
    fclose(ms);

    return 0;
}