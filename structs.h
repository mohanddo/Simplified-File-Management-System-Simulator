#ifndef STRUCTS_H
#define STRUCTS_H

#define ORGANISATION_GLOBAL_CONTIGUE 0
#define ORGANISATION_GLOBAL_CHAINEE 1

#define ORGANISATION_INTERNE_TRIEE 0
#define ORGANISATION_INTERNE_NON_TRIEE 1

typedef bool *tAllocation;

typedef struct
{
    int id;
    char first_name[30], last_name[30];
    double moyenne;
} Etudiant;

typedef struct
{
    char nomFichier[30];
    int tailleFichierBlocs, tailleFichierEngistrements;
    int adressePremierBloc;
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
    int tailleBloc;
    int facteurBlocage;
} MsMetaDonnees;

typedef union
{
    MsMetaDonnees msMetaDonnees;
    tAllocation tAllocation;
    MetaDonneesBloc metaDonneesBloc;
    EtudiantBloc etudiantBloc;
} Buffer;

#endif