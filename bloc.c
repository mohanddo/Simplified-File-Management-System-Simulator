#include <stdio.h>
#include "bloc.h"

#define MAX_NOMBRE_BLOC 1000
#define MAX_TAILLE_BLOC 1000

int initDisk(int* nombreBloc, int* tailleBloc) {
    printf("Entrer le nombre de blocs: ");
    if(scanf("%d", nombreBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    if (*nombreBloc > MAX_NOMBRE_BLOC)
    {
        printf("Max bloc number is: %d, please enter a smaller number \n", MAX_NOMBRE_BLOC);
        return -1;
    }
    
    printf("Entrer la taille de bloc: ");
    if(scanf("%d", tailleBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    if (*tailleBloc > MAX_TAILLE_BLOC)
    {
        printf("Max taille bloc is: %d, please enter a smaller number \n", MAX_TAILLE_BLOC);
        return -1;
    }

    return 0;
}

void viderMS(TableAllocation *tableAllocation, int nombreBloc) {
    for(size_t i = 1; i < nombreBloc; i++) {
        tableAllocation->tAllocated[i] = false;
    }
}