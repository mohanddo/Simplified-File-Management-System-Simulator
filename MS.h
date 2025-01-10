#ifndef MS_H
#define MS_H

#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

void initDisk(FILE *ms);

void initTAllocation(FILE *ms, int nombreBloc);

void initMetaDonneesBlocs(FILE *ms, int tailleBloc);

void initMainBlocs(FILE *ms);

void updateTAllocationAfterCreation(FILE *ms,
                                    MetaDonnees *metaDonnees);

void updateTAllocationAfterDeletion(FILE *ms, MetaDonnees metaDonnees);

void viderMS(FILE **ms);

#endif