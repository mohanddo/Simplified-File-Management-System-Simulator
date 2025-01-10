#ifndef FICHIER_H
#define FICHIER_H

#include <math.h>
#include "structs.h"

#define ORGANISATION_GLOBAL_CONTIGUE 0
#define ORGANISATION_GLOBAL_CHAINEE 1

#define ORGANISATION_INTERNE_TRIEE 0
#define ORGANISATION_INTERNE_NON_TRIEE 1

void creerFichier(FILE *ms);
void addMetaDonnees(FILE *ms, MetaDonnees *metaDonnees);
void deleteMetaDonnees(FILE *ms, int deletedElementIndex);
void writeFichierToMs(FILE *ms, MetaDonnees metaDonnees);
void renommerFichier(FILE *ms, const char *nomFichier, const char *nouveauNom);
void rechercherEtudiantParId(FILE *ms);
void supprimerFichier(FILE *ms);
void suppressionLogiqueEtudiant(FILE *ms);
void trierBlocEtudiant(FILE *ms, int nombreBloc);
#endif