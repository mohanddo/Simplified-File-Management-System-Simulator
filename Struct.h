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
} field;

typedef struct {
    field *s_truct;
    char structName[20];
} Struct;
