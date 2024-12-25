typedef struct
{
    int id;
    char name[30];
} Etudiant;

typedef struct
{
    char nomFichier[30];
    int TailleFichierBlocs, TailleFichierEngistrements;
    int adressPremierBloc;
    int modeOrganisationGlobal, modeOrganisationInterne;
} MetaDonnees;
