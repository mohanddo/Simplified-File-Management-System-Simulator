#include<stdio.h>
#include<string.h>
 void getInputString(char *name) {
         while (scanf("%s", name) != 1 || strlen(name) == 0) {
         printf("Enter a valid string \n");
         int ch; 
        while ((ch = getchar()) != '\n' && ch != EOF);
         printf("Enter : ");
                   }
                   }

void getInputInt(int *num) {
     while (scanf("%d", num) != 1) { 
        printf("Enter a valid integer\n");
         int ch;
          while ((ch = getchar()) != '\n' && ch != EOF);
           printf("Enter an integer: ");
            }
}

void getInputFloat(float *num) {
      while (scanf("%f", num) != 1) { 
        printf("Enter a valid float\n"); 
         int ch;
          while ((ch = getchar()) != '\n' && ch != EOF);
           printf("Enter a float: "); } 
           }

void getInputChar(char *ch) { 
     while (scanf(" %c", ch) != 1) { 
         printf("Enter a valid character\n"); 
          int temp; 
          while ((temp = getchar()) != '\n' && temp != EOF);
           printf("Enter a character: "); }
}