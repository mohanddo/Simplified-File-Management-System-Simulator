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

    MetaDonnees metaDonnees;

    printf("Entrer le nom du fichier: ");
    scanf("%s", metaDonnees.nomFichier);

    printf("Entrer le nombre d'etudiants: ");
    scanf("%d", &(metaDonnees.tailleFichierEngistrements));
    metaDonnees.tailleFichierBlocs = (int)ceil((double)metaDonnees.tailleFichierEngistrements / facteurBlocage);

    metaDonnees.adressePremierBloc = -1;

    printf("Organisation globale contiguë : 0, Organisation globale chaînée : autre valeur \n");
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

    printf("Organiation global triee : 0, Organiation global non triee : autre valeur \n");
    scanf(" %c", &c);
    if (c == '0')
    {
        metaDonnees.modeOrganisationInterne = ORGANISATION_INTERNE_TRIEE;
    }
    else
    {
        metaDonnees.modeOrganisationGlobal = ORGANISATION_INTERNE_NON_TRIEE;
    }

    mettreAJourTallocationAprèsCréation(ms, &metaDonnees);
    if (metaDonnees.adressePremierBloc == -1)
    {
        compactage(ms);
        mettreAJourTallocationAprèsCréation(ms, &metaDonnees);

        if (metaDonnees.adressePremierBloc == -1)
        {
            printf("Pas de bloc libre\n");
        }
        else
        {
            ajouterMetaDonnees(ms, &metaDonnees);
            writeFichierToMs(ms, metaDonnees);
            if (metaDonnees.modeOrganisationInterne == ORGANISATION_INTERNE_TRIEE)
            {
                trierBlocsEtudiant(ms, metaDonnees.adressePremierBloc, metaDonnees.tailleFichierBlocs);
            }
            printf("Le fichier a ete cree\n");
        }
    }
    else
    {
        ajouterMetaDonnees(ms, &metaDonnees);
        writeFichierToMs(ms, metaDonnees);
        if (metaDonnees.modeOrganisationInterne == ORGANISATION_INTERNE_TRIEE)
        {
            trierBlocsEtudiant(ms, metaDonnees.adressePremierBloc, metaDonnees.tailleFichierBlocs);
        }
        printf("Le fichier a ete cree\n");
    }

    printf("\n\n");
}

void ajouterMetaDonnees(FILE *ms, MetaDonnees *metaDonnees)
{
    seekToMetaDonneesBloc(ms);

    int nombreFichier;
    fread(&nombreFichier, sizeof(int), 1, ms);

    int newNombreFichier = nombreFichier + 1;
    // I did change here to long
    fseek(ms, (long)-sizeof(int), SEEK_CUR);
    fwrite(&newNombreFichier, sizeof(int), 1, ms);

    // Skip all the previous Meta Donnees
    fseek(ms, nombreFichier * sizeof(MetaDonnees), SEEK_CUR);

    fwrite(metaDonnees, sizeof(MetaDonnees), 1, ms);
}

void supprimerMetaDonnees(FILE *ms, int deletedElementIndex)
{
    seekToMetaDonneesBloc(ms);

    MetaDonneesBloc metaDonneesBloc;

    readMetaDonneesBloc(ms, &metaDonneesBloc);

    for (size_t i = deletedElementIndex - 1; i < metaDonneesBloc.nombreFichier - 1; i++)
    {
        metaDonneesBloc.metaDonnees[i] = metaDonneesBloc.metaDonnees[i + 1];
    }

    seekToMetaDonneesBloc(ms);

    int newNombreFichier = metaDonneesBloc.nombreFichier - 1;
    fwrite(&(newNombreFichier), sizeof(int), 1, ms);
}

void writeFichierToMs(FILE *ms, MetaDonnees metaDonnees)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int tailleBloc = msMetaDonnees.tailleBloc;
    int facteurBlocage = msMetaDonnees.facteurBlocage;

    seekToMainBlocs(ms);
    fseek(ms, metaDonnees.adressePremierBloc * tailleBloc, SEEK_CUR);
    int etudiantsLeft = metaDonnees.tailleFichierEngistrements;
    for (size_t i = 0; i < metaDonnees.tailleFichierBlocs; i++)
    {
        int numberEtudiantsToWrite = etudiantsLeft >= facteurBlocage ? facteurBlocage : etudiantsLeft;
        Etudiant etudiants[numberEtudiantsToWrite];
        generateRandomEtudiants(etudiants, numberEtudiantsToWrite);

        fwrite(&numberEtudiantsToWrite, sizeof(int), 1, ms);
        for (size_t i = 0; i < numberEtudiantsToWrite; i++)
        {
            fwrite(etudiants + i, sizeof(Etudiant), 1, ms);
        }

        etudiantsLeft -= facteurBlocage;
    }
}

void renommerFichier(FILE *ms)
{
    char nomFichier[30];
    printf("Entrer le nom du fichier que vous voulez renommer: ");
    scanf("%s", nomFichier);

    char nouveauNom[30];
    printf("Entrer le nom du nouveau fichier: ");
    scanf("%s", nouveauNom);

    MetaDonneesBloc metaDonneesBloc;
    seekToMetaDonneesBloc(ms);

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

void rechercherEtudiantParId(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    int id;
    printf("Entrer l'id de l'etudiant que vous rechercher: ");
    scanf("%d", &id);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    seekToMainBlocs(ms);

    EtudiantBloc etudiantBloc;
    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        if (!tAllocation[i])
            continue;

        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        for (size_t i = 0; i < etudiantBloc.nombreEtudiant; i++)
        {
            if (etudiantBloc.etudiants[i].id == id)
            {
                printf("Étudiant trouvé\n\n");
                printEtudiant(etudiantBloc.etudiants[i]);
                return;
            }
        }
    }

    printf("Aucun etudiant avec ce id\n\n");

    free(tAllocation);
}

void supprimerFichier(FILE *ms)
{

    char nomFichier[30];
    printf("Entrer le nom du fichier que vous voulez supprimer: ");
    scanf("%s", nomFichier);

    MetaDonneesBloc metaDonneesBloc;
    seekToMetaDonneesBloc(ms);

    readMetaDonneesBloc(ms, &metaDonneesBloc);
    for (size_t i = 0; i < metaDonneesBloc.nombreFichier; i++)
    {
        MetaDonnees metaDonnees = metaDonneesBloc.metaDonnees[i];
        if (strcmp(nomFichier, metaDonnees.nomFichier) == 0)
        {
            mettreAJourTallocationAprèsSuppression(ms, metaDonnees);
            supprimerMetaDonnees(ms, i + 1);
            printf("Le fichier %s a ete supprimer\n", nomFichier);
            printf("\n");
            return;
        }
    }

    printf("Le fichier %s n'existe pas\n", nomFichier);
    printf("\n");
}

void suppressionLogiqueEtudiant(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    int id;
    printf("Entrer l'id de l'etudiant que vous voulez supprimer: ");
    scanf("%d", &id);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    seekToMainBlocs(ms);

    EtudiantBloc etudiantBloc;
    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        for (size_t i = 0; i < etudiantBloc.nombreEtudiant; i++)
        {
            if (etudiantBloc.etudiants[i].id == id)
            {
                printEtudiant(etudiantBloc.etudiants[i]);
                etudiantBloc.etudiants[i].id = -1;

                fseek(ms, (i - msMetaDonnees.facteurBlocage) * sizeof(Etudiant), SEEK_CUR);

                fwrite(etudiantBloc.etudiants + i, sizeof(Etudiant), 1, ms);

                printf("Étudiant supprimer\n\n");
                return;
            }
        }
    }

    printf("Aucun etudiant avec ce id\n\n");
}

void trierBlocsEtudiant(FILE *ms, int adressePremierBloc, int tailleFichierBloc)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    seekToMainBlocs(ms);
    fseek(ms, msMetaDonnees.tailleBloc * (adressePremierBloc - 1), SEEK_CUR);

    for (size_t i = 0; i < tailleFichierBloc; i++)
    {
        EtudiantBloc etudiantBloc;
        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        for (int i = 0; i < etudiantBloc.nombreEtudiant - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < etudiantBloc.nombreEtudiant; j++)
            {
                if (etudiantBloc.etudiants[j].id < etudiantBloc.etudiants[minIndex].id)
                {
                    minIndex = j;
                }
            }

            if (minIndex != i)
            {
                Etudiant temp = etudiantBloc.etudiants[i];
                etudiantBloc.etudiants[i] = etudiantBloc.etudiants[minIndex];
                etudiantBloc.etudiants[minIndex] = temp;
            }
        }

        fseek(ms, sizeof(int) - msMetaDonnees.tailleBloc, SEEK_CUR);
        for (size_t i = 0; i < etudiantBloc.nombreEtudiant; i++)
        {
            fwrite(etudiantBloc.etudiants + i, sizeof(Etudiant), 1, ms);
        }
        fseek(ms, msMetaDonnees.tailleBloc * (msMetaDonnees.facteurBlocage - etudiantBloc.nombreEtudiant), SEEK_CUR);
    }
}