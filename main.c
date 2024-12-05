#include <stdio.h>

int nombreBloc;
int tailleBloc;

typedef struct {
    int intVal;
    float floatVal;
    char charVal[20];
} Data;

typedef struct {
    char type;
    Data data;
    char name[20];
} Var;

typedef struct {
    Var *s_truct;
} Struct;

void setVariable(Var *var, char type, const char *name, void *value) {
    var->type = type;
    strcpy(var->name, name);
    switch (type) {
        case 'i':
            var->data.intVal = *(int *)value;
            break;
        case 'f':
            var->data.floatVal = *(float *)value;
            break;
        case 'c':
            strcpy(var->data.charVal, (char *)value);
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
        char charVal[20];
        int intVal;
        float floatVal;

        printf("Enter variable name: ");
        scanf("%s", name);
        
        printf("Enter type ('i' for int, 'f' for float, 'c' for char array): ");
        scanf(" %c", &type);
        
        void *value;
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
                printf("Enter char array value: ");
                scanf("%s", charVal);
                value = charVal;
                break;
            default:
                printf("Unknown type\n");
                exit(1);
        }
        
        setVariable(&s->s_truct[i], type, name, value);
    }
}

void printStruct(Struct s, int numberVar)
 {
     for (int i = 0; i < numberVar; i++)
      { printf("Name: %s, Type: %c, Value: ", s.s_truct[i].name, s.s_truct[i].type); 
      switch (s.s_truct[i].type) 
      { case 'i': 
      printf("%d\n", s.s_truct[i].data.intVal);
       break;
        case 'f':
         printf("%.2f\n", s.s_truct[i].data.floatVal);
          break; 
          case 'c': 
          printf("%s\n", s.s_truct[i].data.charVal);
           break;
            default:
             printf("Unknown\n"); break; 
             } }};


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
    if (initDisk() != 0)
    {
        return -1;
    }   
    return 0;
}