#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

#define L 3
#define C 3

int main(int argc, char **argv){
    if (argc < 2) exit(INVALID_ARGUMENTS_ERROR);

    int width = GetMonitorWidth(MONITOR);
    int height = GetMonitorHeight(MONITOR);

    InitWindow(width, height, "Game Of Life");
    if (!IsWindowReady()) exit(WINDOW_INIT_FAIL);
    SetWindowMonitor(MONITOR);

    int error = 0;
    Board *board = getBoard(argv[1], &error);
    if (!board) exit(error);
    printMatrix(board, 1);

    Board *nextBoard = copyBoard(NULL, board);
    printMatrix(nextBoard, 1);
    int fps = 1;
    
    SetTargetFPS(1);
    // start game loop
    while (!WindowShouldClose()){
        if (IsKeyPressed(KEY_UP)) SetTargetFPS(fps++);
        if (IsKeyPressed(KEY_DOWN) && fps > 1) SetTargetFPS(fps--);

        copyBoard(board, nextBoard);

        ClearBackground(WHITE);
        BeginDrawing();
            DrawMatrix(nextBoard);
            updateBoard(board, nextBoard);
        EndDrawing();
    }
    return 0;
}



