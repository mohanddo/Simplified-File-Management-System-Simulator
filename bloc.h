#include <stdbool.h>
#include "Struct.h"

typedef struct
{
    bool *tAllocated;
} TableAllocation;

typedef struct 
{
    int nombreEngristrements;
    Struct *engistrements;
} Bloc;

int initDisk(int* nombreBloc, int* tailleBloc);
void viderMS(TableAllocation *tableAllocation, int nombreBloc);


