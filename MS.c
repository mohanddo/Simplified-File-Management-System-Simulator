#include <stdio.h>
#include "MS.h"

void initDisk(int *nombreBloc, int *tailleBloc)
{
    printf("Entrer le nombre de blocs: ");
    scanf("%d", nombreBloc);
    printf("\n");

    printf("Entrer la taille de bloc: ");
    scanf("%d", tailleBloc);
    printf("\n");

    FILE *ms = fopen("ms.bin", "wb");
    fclose(ms);
}