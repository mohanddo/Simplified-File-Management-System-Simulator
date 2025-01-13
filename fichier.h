#ifndef FICHIER_H
#define FICHIER_H

#include <math.h>
#include "structs.h"

void creerFichier(FILE *ms);
void ajouterMetaDonnees(FILE *ms, MetaDonnees *metaDonnees);
void supprimerMetaDonnees(FILE *ms, int deletedElementIndex);
void writeFichierToMs(FILE *ms, MetaDonnees metaDonnees);
void renommerFichier(FILE *ms);
void rechercherEtudiantParId(FILE *ms);
void supprimerFichier(FILE *ms);
void suppressionLogiqueEtudiant(FILE *ms);
void trierBlocsEtudiant(FILE *ms, int adressePremierBloc, int tailleFichierBloc);
#endif