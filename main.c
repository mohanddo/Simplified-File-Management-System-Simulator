#include <stdio.h>
#include "bloc.h"


int main() {
    int x, y;
    initDisk(&x, &y);
    printf("%d %d", x, y);
    return 0;
}