#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

Board *getBoard(char *filename, int *error, Board *board){
    FILE *input = NULL;
    *error = 0;

    if (filename){
        input = fopen(filename, "r");
        if (!input) {
            *error = FILE_READ_FAIL;
            return NULL;
        };
    }

    uint L, C;

    if (!board){
        board = (Board*) malloc (sizeof(*board));
        if (!board) {
            *error = MATRIX_ALLOC_FAIL;
            freeBoard(board);
            return NULL;
        }
    }

    int read_state;
    if (filename){
        read_state = fscanf(input, "%i %i %f %f", &C, &L, &board->size.x, &board->size.y);
        if (read_state != 4) {
            *error = INVALID_FILE_HEADER;
            freeBoard(board);
            return NULL;
        }
    } else {
        C = 0;
        L = 0;
        board->size.x = 160;
        board->size.y = 90;
    }

    if (!board->matrix){
        board->matrix = (bool**) calloc (board->size.y, sizeof(bool*));
        if (!board->matrix) {
            *error = MATRIX_ALLOC_FAIL;
            freeBoard(board);
            return NULL;
        }
    }
    int temp; // for bool conversion; bool type size is implementation dependant
    for (uint l = 0; l < board->size.y && !*error; l++){
        if (!board->matrix[l]){
            board->matrix[l] = (bool*) calloc (board->size.x, sizeof(bool));
            if (!board->matrix[l]){
                *error = MATRIX_ALLOC_FAIL;
            }
        }
        for (uint c = 0; c < board->size.x && !*error; c++){
            if (c >= C || l >= L) {
                board->matrix[l][c] = 0;
                continue;
            }
            read_state = fscanf(input, "%d ", &temp);
            if (read_state != 1) {
                *error = FILE_READ_FAIL;
                break;
            }
            board->matrix[l][c] = temp;
        }
    }
    if (*error){ // invalid header; board was malloc'd
        freeBoard(board);
        return NULL;
    }
    return board;
}

Board *copyBoard(Board *copy, Board *toCopy){
    if (!copy) {
        copy = (Board*) malloc (sizeof(*copy));
        if (!copy) {
            free(copy);
            return NULL;
        }
        copy->matrix = (bool**) calloc (toCopy->size.y, sizeof(bool*));
        if (!copy->matrix) {
            free(copy->matrix);
            free(copy);
            return NULL;
        }
    }

    copy->size = toCopy->size;

    for (uint l = 0; l < copy->size.y; l++){
        if (!copy->matrix[l]) {
            copy->matrix[l] = (bool*) calloc (copy->size.x, sizeof(bool));
            if (!copy->matrix[l]){
                freeBoard(copy);
                return NULL;
            }
        }
        for (uint c = 0; c < copy->size.x; c++){
            copy->matrix[l][c] = toCopy->matrix[l][c];
        }
    }

    return copy;
}

void printMatrix(Board *board){
    uint L, C;
    L = board->size.y;
    C = board->size.x;

    for (uint l = 0; l < L; l++){
        for (uint c = 0; c < C; c++){
            printf("%i ", board->matrix[l][c]);
        }
        printf("\n");
    }
}

void freeBoard(Board *board){
    for (uint l = 0; l < board->size.y; l++)
        free(board->matrix[l]);
    free(board->matrix);
    free(board);
}
