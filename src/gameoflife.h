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
    Vector2 size;   // size to be drawn on screen

    bool **matrix;  // matrix holding the game's state
} Board;

// game 
int countNeighbours(Board *board, Vector2 pos);                                 // count alive neighbours arround a cell
void updateBoard(Board *original, Board* newBoard);                             // iterate the board through one cycle
int resetGameState(Board *board, Board *nextBoard, char *filename, int *error); // resets the game, rereads the input file
void mouseCellForce(Board *);                                                   // sets a cell to 1 at mouse position

// matrix info
Board *getBoard(char *filename, int *error, Board*); // get a board from a file, if a board is specified, then that pointer will be used to store the info, if filename is NULL a default board will be created
void printMatrix(Board*);                            // print matrix to the terminal

// rendering
void DrawMatrix(Board*);                                  // render matrix on the screen
float convert(float, Vector2 oldRange, Vector2 newRange); // convert a value from a range to another

// memory
Board *copyBoard(Board *copy, Board *toCopy); // returns an exact copy of the board, if a copy is specified, then toCopy's values will be copied to the copy board without allocation
void freeBoard(Board*);                       // frees all the contents of a Board
