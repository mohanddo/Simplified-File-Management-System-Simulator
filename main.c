#include <stdio.h>
#include "MS.h"

int main()
{
    int nombreBloc, tailleBloc;

    initDisk(&nombreBloc, &tailleBloc);

    printf("nombreBloc: %d \ntailleBloc: %d \n", nombreBloc, tailleBloc);

    return 0;
}