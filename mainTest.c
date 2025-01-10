#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>
#include "MS.h"
#include "utils.h"
#include "fichier.h"
#include "menu.h"

int main()
{
    srand(time(NULL));
    

    FILE *ms = fopen("ms.bin", "wb+");
    if (!ms)
    {
        printf("Error: Could not open the file.\n");
        return 1;
    }

    displayMenu(ms);

    fclose(ms);
    return 0;
}