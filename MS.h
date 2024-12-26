#ifndef MS_H
#define MS_H

#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

void initDisk(FILE *ms);

void updateTAllocation(FILE *ms, int nombreBloc,
                       MetaDonnees *metaDonnees, bool newValue);

#endif