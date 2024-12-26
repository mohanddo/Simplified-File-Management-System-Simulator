#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MS.h"

void readMsMetaDonnees(FILE *ms, MsMetaDonnees *msMetaDonnees)
{
    fseek(ms, 0, SEEK_SET);
    fread(msMetaDonnees, sizeof(MsMetaDonnees), 1, ms);
}

int seekToFirstBloc(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    // Skip allocation table
    fseek(ms, sizeof(bool) * msMetaDonnees.nombreBloc, SEEK_CUR);
    return msMetaDonnees.nombreBloc;
}

void seekToMetaDonneesBloc(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    // Skip allocation table
    fseek(ms, sizeof(bool) * msMetaDonnees.nombreBloc, SEEK_SET);

    // Skip all the blocs
    fseek(ms, msMetaDonnees.nombreBloc * (msMetaDonnees.facteurBlocage * sizeof(Etudiant) + sizeof(int)), SEEK_CUR);
}

void printAllocationTable(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int facteurBlocage = msMetaDonnees.facteurBlocage;
    int nombreBloc = msMetaDonnees.nombreBloc;

    printf("Facteur blocage: %d\nNombre bloc: %d\n", facteurBlocage, nombreBloc);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * nombreBloc);
    fread(tAllocation, sizeof(bool), nombreBloc, ms);

    for (size_t i = 0; i < nombreBloc; i++)
    {
        printf("%d ", tAllocation[i]);
    }
    printf("\n");
}

void printMetaDonnees(MetaDonnees meta)
{
    printf("Nom du fichier: %s\n", meta.nomFichier);
    printf("Taille du fichier (blocs): %d\n", meta.tailleFichierBlocs);
    printf("Taille du fichier (enregistrements): %d\n", meta.tailleFichierEngistrements);
    printf("Adresse du premier bloc: %d\n", meta.adressPremierBloc);
    printf("Mode d'organisation global: %d\n", meta.modeOrganisationGlobal);
    printf("Mode d'organisation interne: %d\n", meta.modeOrganisationInterne);
}

void readMetaDonneesBloc(FILE *ms, MetaDonneesBloc *metaDonneesBloc)
{
    fread(&(metaDonneesBloc->nombreFichier), sizeof(int), 1, ms);
    metaDonneesBloc->metaDonnees = (MetaDonnees *)malloc(metaDonneesBloc->nombreFichier * sizeof(MetaDonnees));
    fread(metaDonneesBloc->metaDonnees, sizeof(MetaDonnees), metaDonneesBloc->nombreFichier, ms);
}

void printMetaDonneesBloc(FILE *ms)
{
    seekToMetaDonneesBloc(ms);

    MetaDonneesBloc metaDonneesBloc;
    readMetaDonneesBloc(ms, &metaDonneesBloc);

    printf("Nombre fichier: %d\n", metaDonneesBloc.nombreFichier);

    for (size_t i = 0; i < metaDonneesBloc.nombreFichier; i++)
    {
        printMetaDonnees(metaDonneesBloc.metaDonnees[i]);
    }
    printf("\n");
}

void printMainBlocs(FILE *ms)
{
    int nombreBloc = seekToFirstBloc(ms);
    for (int i = 0; i < nombreBloc; i++)
    {
        EtudiantBloc etudiantBloc;
        fread(&(etudiantBloc.nombreEtudiant), sizeof(int), 1, ms);
        printf("Bloc %d\n", i);
        printf("Nombre Etudiant: %d\n", etudiantBloc.nombreEtudiant);
        etudiantBloc.etudiants = (Etudiant *)malloc(sizeof(Etudiant) * etudiantBloc.nombreEtudiant);
        fread(etudiantBloc.etudiants, sizeof(Etudiant), etudiantBloc.nombreEtudiant, ms);
        for (size_t j = 0; j < etudiantBloc.nombreEtudiant; j++)
        {
            printf("id: %d\n", etudiantBloc.etudiants[j].id);
        }
    }
}
