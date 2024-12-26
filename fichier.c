#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "fichier.h"
#include "MS.h"
#include "utils.h"

void creerFichier(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int facteurBlocage = msMetaDonnees.facteurBlocage;
    int nombreBloc = msMetaDonnees.nombreBloc;

    MetaDonnees metaDonnees;

    printf("Entrer le nom du fichier: ");
    scanf("%s", metaDonnees.nomFichier);

    printf("Entrer le nombre d'etudiants: ");
    scanf("%d", &(metaDonnees.tailleFichierEngistrements));
    metaDonnees.tailleFichierBlocs = (metaDonnees.tailleFichierEngistrements / facteurBlocage) + 1;
    printf("TailleFichierBlocs: %d \n", metaDonnees.tailleFichierBlocs);

    printf("Organiation global contigue : 0, Organiation global chainee : anything else \n");
    char c;
    scanf(" %c", &c);
    if (c == '0')
    {
        metaDonnees.modeOrganisationGlobal = ORGANISATION_GLOBAL_CONTIGUE;
    }
    else
    {
        metaDonnees.modeOrganisationGlobal = ORGANISATION_GLOBAL_CHAINEE;
    }

    printf("Organiation global triee : 0, Organiation global non triee : anything else \n");
    scanf(" %c", &c);
    if (c == '0')
    {
        metaDonnees.modeOrganisationInterne = ORGANISATION_INTERNE_TRIEE;
    }
    else
    {
        metaDonnees.modeOrganisationGlobal = ORGANISATION_INTERNE_NON_TRIEE;
    }

    updateTAllocation(ms, nombreBloc, &metaDonnees, true);
    addMetaDonnees(ms, &metaDonnees);
    writeFichierToMs(ms, metaDonnees, facteurBlocage);
}

void addMetaDonnees(FILE *ms, MetaDonnees *metaDonnees)
{
    seekToMetaDonneesBloc(ms);

    int nombreFichier;
    fread(&nombreFichier, sizeof(int), 1, ms);

    // Add one to the nombre fichier variable
    fseek(ms, -sizeof(int), SEEK_CUR);
    int NewnombreFichier = nombreFichier + 1;
    fwrite(&NewnombreFichier, sizeof(int), 1, ms);

    // Skip all the previous Meta Donnees
    fseek(ms, nombreFichier * sizeof(MetaDonnees), SEEK_CUR);

    fwrite(metaDonnees, sizeof(MetaDonnees), 1, ms);
}

void writeFichierToMs(FILE *ms, MetaDonnees metaDonnees, int facteurBlocage)
{
    seekToFirstBloc(ms);
    fseek(ms, metaDonnees.adressPremierBloc * (facteurBlocage * sizeof(Etudiant) + sizeof(int)), SEEK_CUR);
    int etudiantsLeft = metaDonnees.tailleFichierEngistrements;
    for (size_t i = 0; i < metaDonnees.tailleFichierBlocs; i++)
    {
        int numberEtudiantsToWrite = etudiantsLeft >= facteurBlocage ? facteurBlocage : etudiantsLeft;
        Etudiant etudiants[numberEtudiantsToWrite];
        for (size_t i = 0; i < numberEtudiantsToWrite; i++)
        {
            Etudiant etudiant;
            etudiant.id = 3;
            etudiants[i] = etudiant;
        }

        fwrite(&numberEtudiantsToWrite, sizeof(int), 1, ms);
        fwrite(etudiants,
               sizeof(Etudiant),
               numberEtudiantsToWrite,
               ms);

        etudiantsLeft -= facteurBlocage;
    }
}

void renommerFichier(FILE *ms, const char *nomFichier, const char *nouveauNom)
{
    seekToMetaDonneesBloc(ms);
    MetaDonneesBloc metaDonneesBloc;
    readMetaDonneesBloc(ms, &metaDonneesBloc);

    for (size_t i = 0; i < metaDonneesBloc.nombreFichier; i++)
    {
        MetaDonnees metaDonnees = metaDonneesBloc.metaDonnees[i];
        if (strcmp(nomFichier, metaDonnees.nomFichier) == 0)
        {
            strcpy(metaDonnees.nomFichier, nouveauNom);
            fseek(ms, sizeof(MetaDonnees) * (i - metaDonneesBloc.nombreFichier), SEEK_CUR);
            fwrite(&metaDonnees, sizeof(MetaDonnees), 1, ms);
            printf("Nom du fichier a ete change de %s a %s\n", nomFichier, nouveauNom);
            printf("\n");
            return;
        }
    }

    printf("Le fichier %s n'existe pas\n", nomFichier);
    printf("\n");
}