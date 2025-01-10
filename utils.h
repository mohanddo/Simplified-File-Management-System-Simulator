#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MS.h"
#include "structs.h"

void printAllocationTable(FILE *ms);
void printMetaDonnees(MetaDonnees meta);
void printMetaDonneesBloc(FILE *ms);
void printMainBlocs(FILE *ms);
void printEtudiant(Etudiant e);

void seekToMainBlocs(FILE *ms);
void seekToMetaDonneesBloc(FILE *ms);

void readMsMetaDonnees(FILE *ms, MsMetaDonnees *msMetaDonnees);
void readMetaDonneesBloc(FILE *ms, MetaDonneesBloc *metaDonneesBloc);
void readEtudiantBloc(FILE *ms, EtudiantBloc *etudiantBloc, int facteurBlocage);
void readTAllocation(FILE *ms, tAllocation *tAllocation);

Etudiant generateRandomEtudiant();
void generateRandomEtudiants(Etudiant *etudiant, int lenght);

#endif