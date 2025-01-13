#include "utils.h"

void readMsMetaDonnees(FILE *ms, MsMetaDonnees *msMetaDonnees)
{
    fseek(ms, 0, SEEK_SET);
    fread(msMetaDonnees, sizeof(MsMetaDonnees), 1, ms);
}

void printAllocationTable(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int facteurBlocage = msMetaDonnees.facteurBlocage;
    int nombreBloc = msMetaDonnees.nombreBloc;
    int tailleBloc = msMetaDonnees.tailleBloc;

    printf("Facteur blocage: %d\nNombre bloc: %d\nTaille bloc: %d\n", facteurBlocage, nombreBloc, tailleBloc);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    printf("Table Allocation: ");
    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        printf("%d ", tAllocation[i]);
    }
    printf("\n\n");

    free(tAllocation);
}

void readTAllocation(FILE *ms, tAllocation *tAllocation)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    Buffer buffer;
    buffer.tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));

    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        fread(buffer.tAllocation + i, sizeof(bool), 1, ms);
    }

    *tAllocation = buffer.tAllocation;
}

void printMetaDonneesBloc(FILE *ms)
{
    seekToMetaDonneesBloc(ms);

    MetaDonneesBloc metaDonneesBloc;

    readMetaDonneesBloc(ms, &metaDonneesBloc);
    printf("Meta Donnees Bloc\n\n");

    printf("Nombre fichier: %d\n\n", metaDonneesBloc.nombreFichier);

    for (size_t i = 0; i < metaDonneesBloc.nombreFichier; i++)
    {
        printMetaDonnees(metaDonneesBloc.metaDonnees[i]);
    }
    printf("\n\n");
}

void printMetaDonnees(MetaDonnees meta)
{
    printf("Nom du fichier: %s\n", meta.nomFichier);
    printf("Taille du fichier (blocs): %d\n", meta.tailleFichierBlocs);
    printf("Taille du fichier (enregistrements): %d\n", meta.tailleFichierEngistrements);
    printf("Adresse du premier bloc: %d\n", meta.adressePremierBloc);
    if (meta.modeOrganisationGlobal == ORGANISATION_GLOBAL_CHAINEE)
    {
        printf("Mode d'organisation global: ORGANISATION GLOBAL CHAINEE\n");
    }
    else
    {
        printf("Mode d'organisation global: ORGANISATION GLOBAL CONTIGUE\n");
    }

    if (meta.modeOrganisationGlobal == ORGANISATION_INTERNE_TRIEE)
    {
        printf("Mode d'organisation interne: ORGANISATION INTERNE TRIEE \n");
    }
    else
    {
        printf("Mode d'organisation interne: ORGANISATION INTERNE NON TRIEE\n");
    }

    printf("\n\n");
}

void seekToMetaDonneesBloc(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    // Skip allocation table
    fseek(ms, sizeof(bool) * (msMetaDonnees.nombreBloc - 2), SEEK_CUR);
}

void seekToMainBlocs(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    // Skip allocation table
    fseek(ms, sizeof(bool) * (msMetaDonnees.nombreBloc - 2), SEEK_CUR);

    // Skip meta donnees blocs
    fseek(ms, msMetaDonnees.tailleBloc, SEEK_CUR);
}

void readMetaDonneesBloc(FILE *ms, MetaDonneesBloc *metaDonneesBloc)
{

    Buffer buffer;
    fread(&(metaDonneesBloc->nombreFichier), sizeof(int), 1, ms);

    buffer.metaDonneesBloc.metaDonnees = (MetaDonnees *)malloc(metaDonneesBloc->nombreFichier * sizeof(MetaDonnees));
    for (size_t i = 0; i < metaDonneesBloc->nombreFichier; i++)
    {
        fread(buffer.metaDonneesBloc.metaDonnees + i, sizeof(MetaDonnees), 1, ms);
    }
    metaDonneesBloc->metaDonnees = buffer.metaDonneesBloc.metaDonnees;
}

void printEtudiant(Etudiant e)
{
    printf("ID: %d\n", e.id);
    printf("First Name: %s\n", e.first_name);
    printf("Last Name: %s\n", e.last_name);
    printf("Moyenne: %.2f\n", e.moyenne);
    printf("\n");
}

void readEtudiantBloc(FILE *ms, EtudiantBloc *etudiantBloc, int facteurBlocage)
{
    Buffer buffer;

    fread(&(etudiantBloc->nombreEtudiant), sizeof(int), 1, ms);

    buffer.etudiantBloc.etudiants = (Etudiant *)malloc(sizeof(Etudiant) * etudiantBloc->nombreEtudiant);
    for (size_t i = 0; i < etudiantBloc->nombreEtudiant; i++)
    {
        fread(buffer.etudiantBloc.etudiants + i, sizeof(Etudiant), 1, ms);
    }

    fseek(ms, sizeof(Etudiant) * (facteurBlocage - etudiantBloc->nombreEtudiant), SEEK_CUR);
    etudiantBloc->etudiants = buffer.etudiantBloc.etudiants;
}

void printMainBlocs(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    seekToMainBlocs(ms);

    for (int i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        EtudiantBloc etudiantBloc;
        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        printf("Bloc %d\n", i + 1);

        if (!tAllocation[i])
        {
            printf("Nombre Etudiant: 0\n\n");
            continue;
        }

        printf("Nombre Etudiant: %d\n\n", etudiantBloc.nombreEtudiant);

        for (size_t j = 0; j < etudiantBloc.nombreEtudiant; j++)
        {
            if (etudiantBloc.etudiants[j].id != -1)
            {
                printEtudiant(etudiantBloc.etudiants[j]);
            }
        }
        printf("\n\n");
    }

    free(tAllocation);
}

void printFichier(FILE *ms)
{

    char nomFichier[30];
    printf("Entrer le nom du fichier: ");
    scanf("%s", nomFichier);

    seekToMetaDonneesBloc(ms);
    MetaDonneesBloc metaDonneesBloc;
    readMetaDonneesBloc(ms, &metaDonneesBloc);

    int adressePremierBloc = -1;
    int tailleFichierBlocs = -1;
    for (size_t i = 0; i < metaDonneesBloc.nombreFichier; i++)
    {
        if (strcmp(metaDonneesBloc.metaDonnees[i].nomFichier, nomFichier) == 0)
        {
            printMetaDonnees(metaDonneesBloc.metaDonnees[i]);
            adressePremierBloc = metaDonneesBloc.metaDonnees[i].adressePremierBloc;
            tailleFichierBlocs = metaDonneesBloc.metaDonnees[i].tailleFichierBlocs;
        }
    }

    if (adressePremierBloc == -1)
    {
        printf("Le fichier %s n'existe pas\n", nomFichier);
        printf("\n");
    }

    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    seekToMainBlocs(ms);
    fseek(ms, adressePremierBloc * msMetaDonnees.tailleBloc, SEEK_CUR);

    for (int i = adressePremierBloc; i < tailleFichierBlocs; i++)
    {
        EtudiantBloc etudiantBloc;
        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        printf("Bloc %d\n", i + 1);

        printf("Nombre Etudiant: %d\n\n", etudiantBloc.nombreEtudiant);

        for (size_t j = 0; j < etudiantBloc.nombreEtudiant; j++)
        {
            if (etudiantBloc.etudiants[j].id != -1)
            {
                printEtudiant(etudiantBloc.etudiants[j]);
            }
        }
        printf("\n\n");
    }

    free(tAllocation);
}

const char firstNames[][20] = {"Mohand", "Akli", "Youcef", "Idris", "Ayoub", "Rachid", "Mohamed",
                               "Zakaria", "Samy", "Saleh", "Yacin", "Walid", "Akram", "Hakim", "Arezki", "Kamel", "Nadia",
                               "Hadjer", "Serine"};

const char lastNames[][20] = {"Meghaoui", "Mahfouf", "Abdelhakim", "Taleb", "Setti", "Salhin",
                              "Bouzidi", "Delloumi", "Lallali"};

Etudiant generateRandomEtudiant()
{
    Etudiant etudiant;

    // We suppose that the function rand can't generate duplicate numbers
    etudiant.id = (rand() % 1000);
    strcpy(etudiant.first_name, firstNames[rand() % 15]);
    strcpy(etudiant.last_name, lastNames[rand() % 9]);
    etudiant.moyenne = ((double)rand() / RAND_MAX) * 20;

    return etudiant;
}

void generateRandomEtudiants(Etudiant *etudiant, int lenght)
{
    for (size_t i = 0; i < lenght; i++)
    {
        etudiant[i] = generateRandomEtudiant();
    }
}
