#ifndef STRUCTS_H
#define STRUCTS_H

typedef bool *tAllocation;

typedef struct
{
    int id;
} Etudiant;

typedef struct
{
    char nomFichier[30];
    int tailleFichierBlocs, tailleFichierEngistrements;
    int adressPremierBloc;
    int modeOrganisationGlobal, modeOrganisationInterne;
} MetaDonnees;

typedef struct
{
    int nombreFichier;
    MetaDonnees *metaDonnees;
} MetaDonneesBloc;

typedef struct
{
    int nombreEtudiant;
    Etudiant *etudiants;
} EtudiantBloc;

typedef struct
{
    int nombreBloc;
    int facteurBlocage;
} MsMetaDonnees;

#endif