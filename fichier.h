typedef MetaDonnees MetaDonnees;
struct MetaDonnees
{
    char nomFichier[30];
    int tailleFichierBlocs, tailleFichierEngistrements;
    int addressPremierBloc;
    int modeOrganisationGlobal, modeOrganisationInterne;
    char structName[20];
};
