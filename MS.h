#ifndef MS_H
#define MS_H

#include <stdio.h>
#include <stdbool.h>
#include "structs.h"

void initDisk(FILE *ms);

void initTAllocation(FILE *ms, int nombreBloc);

void initMetaDonneesBlocs(FILE *ms, int tailleBloc);

void initMainBlocs(FILE *ms);

void mettreAJourTallocationAprèsCréation(FILE *ms,
                                         MetaDonnees *metaDonnees);

void mettreAJourTallocationAprèsSuppression(FILE *ms, MetaDonnees metaDonnees);

void compactage(FILE *ms);

void viderMS(FILE **ms);

#endif