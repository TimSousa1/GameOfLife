#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <stdbool.h>

#define INVALID_ARGUMENTS_ERROR -1
#define WINDOW_INIT_FAIL -2
#define FILE_READ_FAIL -3

typedef struct _board {
    uint L;         // number of lines
    uint C;         // number of columns
    bool **matrix; // matrix holding the game's state
} Board;

Board *getBoard(char *filename); // get a board from a file
