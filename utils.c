#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TAllocation.h"

void printAllocationTable(int nombreBloc)
{
    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * nombreBloc);
    FILE *ms = fopen("ms.bin", "rb");
    fread(tAllocation, sizeof(bool), nombreBloc, ms);

    for (size_t i = 0; i < nombreBloc; i++)
    {
        printf("%d ", tAllocation[i]);
    }
}