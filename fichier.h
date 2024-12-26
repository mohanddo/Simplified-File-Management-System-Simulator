#ifndef FICHIER_H
#define FICHIER_H

#include "structs.h"

#define ORGANISATION_GLOBAL_CONTIGUE 0
#define ORGANISATION_GLOBAL_CHAINEE 1

#define ORGANISATION_INTERNE_TRIEE 0
#define ORGANISATION_INTERNE_NON_TRIEE 1

void creerFichier(FILE *ms);
void addMetaDonnees(FILE *ms, MetaDonnees *metaDonnees);
void writeFichierToMs(FILE *ms, MetaDonnees metaDonnees, int facteurBlocage);
void renommerFichier(FILE *ms, const char *nomFichier, const char *nouveauNom);
#endif