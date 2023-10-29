#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <stdbool.h>

#define MONITOR 0
#define INVALID_ARGUMENTS_ERROR -1

#define WINDOW_INIT_FAIL -2

#define FILE_READ_FAIL -3
#define INVALID_INPUT_FILE -4
#define INVALID_FILE_HEADER -5

#define MATRIX_ALLOC_FAIL -6

typedef struct _board {
    uint L;         // number of lines
    uint C;         // number of columns
    Vector2 size;   // size to be drawn on screen

    bool **matrix;  // matrix holding the game's state
} Board;

// matrix info
Board *getBoard(char *filename, int *error);          // get a board from a file
void printMatrix(Board *, bool show_all); // print matrix to the terminal, show_all to show the whole matrix or just the scanned area

// rendering
void DrawMatrix(Board *);                                 // render matrix on the screen
float convert(float, Vector2 oldRange, Vector2 newRange); // convert a value from a range to another

// memory
void freeBoard(Board *); // frees all the contents of a Board
