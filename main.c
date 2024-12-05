#include <stdio.h>

int nombreBloc;
int tailleBloc;


int initDisk() {
    printf("Entrer le nombre de blocs: ");
    if(scanf("%d", &nombreBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    printf("Entrer la taille de bloc: ");
    if(scanf("%d", &tailleBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    return 0;
}

int main() {
    if (initDisk() != 0)
    {
        return -1;
    }   
    return 0;
}