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
    bool x0, xmax, y0, ymax;

    x0 = (pos.x -1 > 0);
    y0 = (pos.y -1 > 0);
    xmax = (pos.x +1 < board->size.x);
    ymax = (pos.y +1 < board->size.y);

    if (ymax){
        count += board->matrix[(int) pos.y +1][(int) pos.x];
        if (x0) count += board->matrix[(int) pos.y +1][(int) pos.x -1];
        if (xmax) count += board->matrix[(int) pos.y +1][(int) pos.x +1];
    }
    if (y0){
        count += board->matrix[(int) pos.y -1][(int) pos.x];
        if (x0) count += board->matrix[(int) pos.y -1][(int) pos.x -1];
        if (xmax) count += board->matrix[(int) pos.y -1][(int) pos.x +1];
    }
    if (xmax) count += board->matrix[(int) pos.y][(int) pos.x +1];
    if (x0) count += board->matrix[(int) pos.y][(int) pos.x -1];

    return count;
}

int resetGameState(Board *board, Board *nextBoard, char *filename, int *error){
    board = getBoard(filename, error, board);
    if (!board) return *error;

    nextBoard = copyBoard(nextBoard, board);
    if (!nextBoard) return MATRIX_ALLOC_FAIL;
    return 0;
}
