#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MS.h"
#include "utils.h"

void initDisk(FILE *ms)
{
    int nombreBloc;
    printf("Entrez le nombre de blocs (recommandé 20): ");
    scanf("%d", &nombreBloc);

    int tailleBloc;
    printf("Entrez la taille du bloc en octets (recommandé 220): ");
    scanf("%d", &tailleBloc);
    printf("\n");

    int facteurBlocage = (tailleBloc - sizeof(int)) / sizeof(Etudiant);
    MsMetaDonnees msMetaDonnees;
    msMetaDonnees.facteurBlocage = facteurBlocage;
    msMetaDonnees.nombreBloc = nombreBloc;
    msMetaDonnees.tailleBloc = tailleBloc;

    Buffer buffer;
    buffer.msMetaDonnees = msMetaDonnees;

    fwrite(&(buffer.msMetaDonnees), sizeof(MsMetaDonnees), 1, ms);

    initTAllocation(ms, nombreBloc);

    initMetaDonneesBlocs(ms, tailleBloc);

    initMainBlocs(ms);
}

void initTAllocation(FILE *ms, int nombreBloc)
{
    // We suppose that the first block is for allocation table

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (nombreBloc - 2));

    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        tAllocation[i] = false;
        fwrite(tAllocation + i, sizeof(bool), 1, ms);
    }

    free(tAllocation);
}

void initMetaDonneesBlocs(FILE *ms, int tailleBloc)
{
    // We suppose that the second bloc is for meta donnees
    // Write the number of MetaDonnees structures witch is zero in the beginning as there is no files
    int zero = 0;
    fwrite(&zero, sizeof(int), 1, ms);
}

void initMainBlocs(FILE *ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    seekToMainBlocs(ms);

    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        int zero = 0;
        fwrite(&zero, sizeof(int), 1, ms);
        fseek(ms, msMetaDonnees.tailleBloc - sizeof(int), SEEK_CUR);
    }
}

void mettreAJourTallocationAprèsCréation(FILE *ms, MetaDonnees *metaDonnees)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int nombreBloc = msMetaDonnees.nombreBloc;

    Buffer buffer;
    buffer.tAllocation = (bool *)malloc(sizeof(bool) * (nombreBloc - 2));
    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        fread(buffer.tAllocation + i, sizeof(bool), 1, ms);
    }
    tAllocation tAllocation = buffer.tAllocation;

    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        if (!tAllocation[i])
        {
            if (i + metaDonnees->tailleFichierBlocs <= nombreBloc - 2)
            {
                metaDonnees->adressePremierBloc = i;
                for (int j = 0; j < metaDonnees->tailleFichierBlocs; j++)
                {
                    tAllocation[metaDonnees->adressePremierBloc + j] = true;
                }
            }

            break;
        }
    }
    fseek(ms, sizeof(MsMetaDonnees), SEEK_SET);
    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        fwrite(tAllocation + i, sizeof(bool), 1, ms);
    }

    free(tAllocation);
}

void mettreAJourTallocationAprèsSuppression(FILE *ms, MetaDonnees metaDonnees)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);
    int nombreBloc = msMetaDonnees.nombreBloc;

    Buffer buffer;
    buffer.tAllocation = (bool *)malloc(sizeof(bool) * (nombreBloc - 2));
    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        fread(buffer.tAllocation + i, sizeof(bool), 1, ms);
    }
    tAllocation tAllocation = buffer.tAllocation;

    for (int j = 0; j < metaDonnees.tailleFichierBlocs; j++)
    {
        tAllocation[metaDonnees.adressePremierBloc + j] = false;
    }

    fseek(ms, sizeof(MsMetaDonnees), SEEK_SET);
    for (size_t i = 0; i < nombreBloc - 2; i++)
    {
        fwrite(tAllocation + i, sizeof(bool), 1, ms);
    }

    free(tAllocation);
}

void compactage(FILE *ms)
{
    printf("Compactage...\n");

    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(ms, &msMetaDonnees);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * (msMetaDonnees.nombreBloc - 2));
    readTAllocation(ms, &tAllocation);

    seekToMainBlocs(ms);

    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        EtudiantBloc etudiantBloc;
        readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);

        if (!tAllocation[i])
        {
            for (size_t j = i + 1; j < msMetaDonnees.nombreBloc - 2; j++)
            {
                readEtudiantBloc(ms, &etudiantBloc, msMetaDonnees.facteurBlocage);
                if (tAllocation[j])
                {
                    tAllocation[j] = false;
                    tAllocation[i] = true;
                    fseek(ms, -(j - i + 1) * msMetaDonnees.tailleBloc, SEEK_CUR);
                    fwrite(&(etudiantBloc.nombreEtudiant), sizeof(int), 1, ms);
                    for (size_t i = 0; i < etudiantBloc.nombreEtudiant; i++)
                    {
                        fwrite(etudiantBloc.etudiants + i, sizeof(Etudiant), 1, ms);
                    }
                    fseek(ms, (msMetaDonnees.facteurBlocage - etudiantBloc.nombreEtudiant) * sizeof(Etudiant), SEEK_CUR);
                    break;
                }
            }
        }
    }

    readMsMetaDonnees(ms, &msMetaDonnees);
    for (size_t i = 0; i < msMetaDonnees.nombreBloc - 2; i++)
    {
        fwrite(tAllocation + i, sizeof(bool), 1, ms);
    }
}

void viderMS(FILE **ms)
{
    MsMetaDonnees msMetaDonnees;
    readMsMetaDonnees(*ms, &msMetaDonnees);
    fclose(*ms);
    *ms = fopen("ms.bin", "wb+");
    fwrite(&msMetaDonnees, sizeof(MsMetaDonnees), 1, *ms);
    initTAllocation(*ms, msMetaDonnees.nombreBloc);
    initMetaDonneesBlocs(*ms, msMetaDonnees.tailleBloc);
}
