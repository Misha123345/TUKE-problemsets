#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minesweeper.h"

int main (int argc, char * argv[]) {
    srand(time(NULL));
    int rows, cols;
    if (argc != 3) {
        printf("You must enter 2 arguments (./minesweeper [rows] [columns])\n");
        return 1;
    }
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    if (rows < 8 || cols < 8 || rows > 20 || cols > 30) {
        printf("Arguments must be numbers between 8 and 20 [rows], 8 and 30 [columns]\n");
        return 1;
    }

    minesweeper(rows, cols);
    return 0;
}            
