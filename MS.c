#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MS.h"

void initDisk(FILE *ms)
{
    int nombreBloc;
    printf("Entrer le nombre de blocs: ");
    scanf("%d", &nombreBloc);

    int tailleBloc;
    printf("Entrer la taille de bloc: ");
    scanf("%d", &tailleBloc);
    printf("\n");

    int facteurBlocage = tailleBloc / sizeof(Etudiant);
    MsMetaDonnees msMetaDonnees;
    msMetaDonnees.facteurBlocage = facteurBlocage;
    msMetaDonnees.nombreBloc = nombreBloc;

    fwrite(&msMetaDonnees, sizeof(MsMetaDonnees), 1, ms);

    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * nombreBloc);
    for (size_t i = 0; i < nombreBloc; i++)
    {
        tAllocation[i] = false;
    }

    fwrite(tAllocation, sizeof(bool), nombreBloc, ms);

    // Skip all the blocs
    fseek(ms, nombreBloc * (facteurBlocage * sizeof(Etudiant) + sizeof(int)), SEEK_CUR);
    // Write the number of MetaDonnees structures witch is zero in the beginning as there is no files
    int zero = 0;
    fwrite(&zero, sizeof(int), 1, ms);
}

void updateTAllocation(FILE *ms, int nombreBloc, MetaDonnees *metaDonnees, bool newValue)
{
    fseek(ms, sizeof(MsMetaDonnees), SEEK_SET);
    tAllocation tAllocation = (bool *)malloc(sizeof(bool) * nombreBloc);
    fread(tAllocation, sizeof(bool), nombreBloc, ms);

    for (size_t i = 0; i < nombreBloc; i++)
    {
        if (!tAllocation[i])
        {
            metaDonnees->adressPremierBloc = i;
            for (int j = 0; j < metaDonnees->tailleFichierBlocs; j++)
            {
                tAllocation[metaDonnees->adressPremierBloc + j] = newValue;
            }
            break;
        }
    }
    fseek(ms, sizeof(MsMetaDonnees), SEEK_SET);
    fwrite(tAllocation,
           sizeof(bool),
           nombreBloc,
           ms);
}
