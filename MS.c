#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MS.h"
#include "utils.h"

void initDisk(FILE *ms)
{
    int nombreBloc;
    printf("Entrer le nombre de blocs: ");
    scanf("%d", &nombreBloc);

    int tailleBloc;
    printf("Entrer la taille de bloc on bytes: ");
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
    // We suppose that the second is for meta donnees
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

void updateTAllocationAfterCreation(FILE *ms, MetaDonnees *metaDonnees)
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
            metaDonnees->adressePremierBloc = i;
            for (int j = 0; j < metaDonnees->tailleFichierBlocs; j++)
            {
                tAllocation[metaDonnees->adressePremierBloc + j] = true;
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

void updateTAllocationAfterDeletion(FILE *ms, MetaDonnees metaDonnees)
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