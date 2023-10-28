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
    read_state = fscanf(input, "%i %i", &board->L, &board->C);
    if (read_state != 2) exit(FILE_READ_FAIL);

    board->matrix = (bool**) malloc (sizeof(bool*));

    int temp; // for bool conversion; bool type size is implementation dependant
    for (uint l = 0; l < board->L; l++){
        board->matrix[l] = (bool*)malloc (board->C * sizeof(bool));
        for (uint c = 0; c < board->C; c++){
            read_state = fscanf(input, "%d ", &temp);
            if (read_state != 1) exit(FILE_READ_FAIL); // change later; mem leaks WILL happen.
            board->matrix[l][c] = temp;
        }
    }

    return board;
}
