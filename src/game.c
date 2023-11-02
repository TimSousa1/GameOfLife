#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <stdbool.h>

#include "gameoflife.h"

// update a board cycle
void updateBoard(Board *oldBoard, Board *newBoard){
    int surround_count;
    for (uint l = 0; l < oldBoard->size.y; l++){
        for (uint c = 0; c < oldBoard->size.x; c++){
            surround_count = countNeighbours(oldBoard, (Vector2) {c, l});
            if (surround_count == 3) newBoard->matrix[l][c] = 1;
            else if (surround_count != 2) newBoard->matrix[l][c] = 0;
        }
    }
}

// there has to be a better way to do this
int countNeighbours(Board *board, Vector2 pos){
    int count = 0;

    // all possible neighbour positions
    int mvx[] = {-1, 1, 0};
    int mvy[] = {-1, 1, 0};

    int posx, posy;
    int max_i, max_j;

    max_i = 3;
    max_j = 3;

    // running for all possible neighbours
    for (ushort i = 0; i < max_i; i++){
        posx = pos.x + mvx[i];
        if (i == 2) max_j = 2; // avoiding checking for 0, 0
        for (ushort j = 0; j < max_j; j++){

            posy = pos.y + mvy[j];
            if (posx < 0 || posx >= board->size.x 
                    || posy < 0 || posy >= board->size.y) continue;

            count += board->matrix[(int) posy][(int) posx];
        }
    }

    return count;
}

int resetGameState(Board *board, Board *nextBoard, char *filename, int *error){
    board = getBoard(filename, error, board);
    if (!board) return *error;

    nextBoard = copyBoard(nextBoard, board);
    if (!nextBoard) return MATRIX_ALLOC_FAIL;
    return 0;
}
