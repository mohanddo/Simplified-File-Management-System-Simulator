#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nombreBloc;
int tailleBloc;

#define MAX_ARRAY_SIZE 20

typedef struct {
    int intVal;
    float floatVal;
    char charVal[2];
    int intArray[MAX_ARRAY_SIZE];
    float floatArray[MAX_ARRAY_SIZE];
    char charArray[MAX_ARRAY_SIZE][20];
} Data;

typedef struct {
    char type;
    Data data;
    char name[20];
    int arraySize;
} Var;

typedef struct {
    Var *s_truct;
} Struct;

void setVariable(Var *var, char type, const char *name, void *value, int arraySize) {
    var->type = type;
    var->arraySize = arraySize;
    strcpy(var->name, name);
    switch (type) {
        case 'i':
            if (arraySize == 0)
                var->data.intVal = *(int *)value;
            else
                memcpy(var->data.intArray, value, arraySize * sizeof(int));
            break;
        case 'f':
            if (arraySize == 0)
                var->data.floatVal = *(float *)value;
            else
                memcpy(var->data.floatArray, value, arraySize * sizeof(float));
            break;
        case 'c':
            if (arraySize == 0)
                strcpy(var->data.charVal, (char *)value);
            else
                for (int i = 0; i < arraySize; i++) {
                    strcpy(var->data.charArray[i], ((char (*)[20])value)[i]);
                }
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

void setStruct(Struct *s, int numberVar) {
    s->s_truct = (Var *)malloc(numberVar * sizeof(Var));
    if (s->s_truct == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    for (int i = 0; i < numberVar; i++) {
        char type;
        char name[20];
        int intVal;
        float floatVal;
        char charVal[20];
        int arraySize = 0;

        printf("Enter variable name: ");
        scanf("%s", name);
        
        printf("Enter type ('i' for int, 'f' for float, 'c' for char, 'I' for int array, 'F' for float array, 'C' for char array): ");
        scanf(" %c", &type);

        void *value;
        if (type == 'I' || type == 'F' || type == 'C') {
            printf("Enter array size: ");
            scanf("%d", &arraySize);
        }

        switch (type) {
            case 'i':
                printf("Enter integer value: ");
                scanf("%d", &intVal);
                value = &intVal;
                break;
            case 'f':
                printf("Enter float value: ");
                scanf("%f", &floatVal);
                value = &floatVal;
                break;
            case 'c':
                printf("Enter char value: ");
                scanf("%s", charVal);
                value = charVal;
                break;
            case 'I': {
                printf("Enter integer values for the array: ");
                int *intArray = malloc(arraySize * sizeof(int));
                for (int j = 0; j < arraySize; j++) {
                    scanf("%d", &intArray[j]);
                }
                value = intArray;
                break;
            }
            case 'F': {
                printf("Enter float values for the array: ");
                float *floatArray = malloc(arraySize * sizeof(float));
                for (int j = 0; j < arraySize; j++) {
                    scanf("%f", &floatArray[j]);
                }
                value = floatArray;
                break;
            }
            case 'C': {
                printf("Enter char values for the array: ");
                char (*charArray)[20] = malloc(arraySize * sizeof(char[20]));
                for (int j = 0; j < arraySize; j++) {
                    scanf("%s", charArray[j]);
                }
                value = charArray;
                break;
            }
            default:
                printf("Unknown type\n");
                exit(1);
        }

        setVariable(&s->s_truct[i], type, name, value, arraySize);

        if (type == 'I' || type == 'F' || type == 'C') {
            free(value); 
    }
}

}

int initDisk() {
    printf("Entrer le nombre de blocs: ");
    if(scanf("%d", &nombreBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    printf("Entrer la taille de bloc: ");
    if(scanf("%d", &tailleBloc) != 1) {
        printf("Error, please enter a valid integer \n");
        return -1;
    }

    return 0;
}

int main() {
    
    return 0;
}