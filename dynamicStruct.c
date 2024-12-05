#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Struct.h"

void setField(field *field, char type, const char *name, void *value, int arraySize)  {

    field->type = type;
    field->arraySize = arraySize;
    strcpy(field->name, name);

    switch (type) {
        case 'i':
            if (arraySize == 0)
                field->data.intVal = *(int *)value;
            else
                memcpy(field->data.intArray, value, arraySize * sizeof(int));
            break;
        case 'f':
            if (arraySize == 0)
                field->data.floatVal = *(float *)value;
            else
                memcpy(field->data.floatArray, value, arraySize * sizeof(float));
            break;
        case 'c':
            if (arraySize == 0)
                strcpy(field->data.charVal, (char *)value);
            else
                for (int i = 0; i < arraySize; i++) {
                    strcpy(field->data.charArray[i], ((char (*)[20])value)[i]);
                }
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

int createNewStruct(Struct *s, int numberField, char *structureName) {
    
    s->s_truct = (field *)malloc(numberField * sizeof(field));
    strcpy(s->structName, structureName);

    if (s->s_truct == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    
    for (int i = 0; i < numberField; i++) {
        char type;
        char name[20];
        int intVal;
        float floatVal;
        char charVal[20];
        int arraySize = 0;

        printf("Enter Field name: ");
        if (scanf("%s", name) != 1)
        {
            printf("Enter a valid string \n");
            return -1;
        }
        
        printf("Enter type ('i' for int, 'f' for float, 'c' for char, 'I' for int array, 'F' for float array, 'C' for char array): ");
        if (scanf(" %c", &type) != 1)
        {
            printf("Enter a valid character");
            return -1;
        }
        

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

        setField(&s->s_truct[i], type, name, value, arraySize);

        if (type == 'I' || type == 'F' || type == 'C') {
            free(value); 
        }
}

return 0;

}

void testCreateNewStruct() {
    // Define the number of fields for the structure
    int numberField = 3;
    Struct s;

    // Create a new struct with a specified name and number of fields
    createNewStruct(&s, numberField, "Test");

    // Print the struct name
    printf("Struct Name: %s\n", s.structName);

    // Loop through the fields and print their details
    for (int i = 0; i < numberField; i++) {
        printf("\nField %d:\n", i + 1);
        printf("Name: %s\n", s.s_truct[i].name);
        printf("Type: %c\n", s.s_truct[i].type);

        // Print the field data based on its type
        switch (s.s_truct[i].type) {
            case 'i': // Integer value
                printf("Integer value: %d\n", s.s_truct[i].data.intVal);
                break;
            case 'f': // Float value
                printf("Float value: %.2f\n", s.s_truct[i].data.floatVal);
                break;
            case 'c': // Char value
                printf("Char value: %s\n", s.s_truct[i].data.charVal);
                break;
            case 'I': // Integer array
                printf("Integer array: ");
                for (int j = 0; j < s.s_truct[i].arraySize; j++) {
                    printf("%d ", s.s_truct[i].data.intArray[j]);
                }
                printf("\n");
                break;
            case 'F': // Float array
                printf("Float array: ");
                for (int j = 0; j < s.s_truct[i].arraySize; j++) {
                    printf("%.2f ", s.s_truct[i].data.floatArray[j]);
                }
                printf("\n");
                break;
            case 'C': // Char array
                printf("Char array: ");
                for (int j = 0; j < s.s_truct[i].arraySize; j++) {
                    printf("%s ", s.s_truct[i].data.charArray[j]);
                }
                printf("\n");
                break;
            default:
                printf("Unknown type\n");
                break;
        }
    }

    // Free the allocated memory for the structure
    free(s.s_truct);
}

int main() {
    // Call the test function to verify the struct creation
    testCreateNewStruct();

    return 0;
}

