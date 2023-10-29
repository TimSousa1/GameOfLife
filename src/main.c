#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

#define L 3
#define C 3

int main(int argc, char **argv){
    if (argc != 2) exit(INVALID_ARGUMENTS_ERROR);

    int width = GetMonitorWidth(MONITOR);
    int height = GetMonitorHeight(MONITOR);

    InitWindow(width, height, "Game Of Life");
    if (!IsWindowReady()) exit(WINDOW_INIT_FAIL);
    SetWindowMonitor(MONITOR);

    int error = 0;
    Board *board = getBoard(argv[1], &error);
    if (!board) exit(FILE_READ_FAIL);
    if (error == INVALID_FILE_HEADER){ // invalid header; board was malloc'd
        free(board);
        CloseWindow();
        exit(error);
    } else if (error == FILE_READ_FAIL) {
        freeBoard(board);
        CloseWindow();
        exit(error);
    } else if (error == MATRIX_ALLOC_FAIL){
        free(board->matrix);
        free(board);
        CloseWindow();
        exit(error);
    }

    printMatrix(board, 1);
    
    SetTargetFPS(1);
    // start game rendering
    while (!WindowShouldClose()){
        ClearBackground(WHITE);

        BeginDrawing();
            DrawMatrix(board);
        EndDrawing();
    }
    return 0;
}



