#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

Board *getBoard(char *filename){
    FILE *input = fopen(filename, "r");
    if (!input) exit(FILE_READ_FAIL);

    Board *board = (Board*) malloc (sizeof(*board));

    int read_state;
    read_state = fscanf(input, "%i %i %f %f", &board->L, &board->C, &board->size.x, &board->size.y);
    if (read_state != 4) exit(FILE_READ_FAIL);

    board->matrix = (bool**) malloc (sizeof(bool*));

    int temp; // for bool conversion; bool type size is implementation dependant
    for (uint l = 0; l < board->size.y; l++){
        board->matrix[l] = (bool*)malloc (board->size.x * sizeof(bool));
        for (uint c = 0; c < board->size.x; c++){
            if (c >= board->C || l >= board->L) {
                board->matrix[l][c] = 0;
                continue;
            }
            read_state = fscanf(input, "%d ", &temp);
            if (read_state != 1) exit(FILE_READ_FAIL); // change later; mem leaks WILL happen.
            board->matrix[l][c] = temp;
        }
    }
    return board;
}

void printMatrix(Board *board, bool show_all){
    int L, C;
    L = board->L;
    C = board->C;
    if (show_all) {
        L = board->size.y;
        C = board->size.x;
    }
    for (uint l = 0; l < board->size.y; l++){
        for (uint c = 0; c < board->size.x; c++){
            printf("%i ", board->matrix[l][c]);
        }
        printf("\n");
    }
}
