#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

#define FPS 15
#define FPS_PAUSE 500

int main(int argc, char **argv){
    char *filename = NULL;
    if (argc == 2) filename = argv[1];
    else if (argc > 2) exit(INVALID_ARGUMENTS_ERROR);

    int width = GetMonitorWidth(MONITOR);
    int height = GetMonitorHeight(MONITOR);

    InitWindow(width, height, "Game Of Life");
    if (!IsWindowReady()) exit(WINDOW_INIT_FAIL);
    SetWindowMonitor(MONITOR);

    int error = 0;
    Board *board = NULL;
    board = getBoard(filename, &error, NULL);
    if (!board) exit(error);

    Board *nextBoard = copyBoard(NULL, board);
    int fps = FPS;
    
    int reset_status;
    int save_status;
    bool game_is_paused = 1;
    SetTargetFPS(FPS);
    if (game_is_paused) SetTargetFPS(FPS_PAUSE);
    // start game loop
    while (!WindowShouldClose()){
        save_status = 0;
        if (IsKeyPressed(KEY_UP)) SetTargetFPS(fps++);
        if (IsKeyPressed(KEY_DOWN) && fps > 1) SetTargetFPS(fps--);
        if (IsKeyPressed(KEY_R)) {
            reset_status = resetGameState(board, nextBoard, argv[1], &error);
            if (reset_status) break;
        }
        if (IsKeyPressed(KEY_SPACE)){
            game_is_paused = !game_is_paused;
            if (game_is_paused) SetTargetFPS(FPS_PAUSE);
            else SetTargetFPS(fps);
        }
        if (IsKeyPressed(KEY_S)) {
            save_status = saveBoardToFile("../saved/test1.golboard", nextBoard);
            if (save_status) printf("error saving file! (STATUS %i)\n", save_status);
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mouseCellForce(nextBoard);

        copyBoard(board, nextBoard);
        if (!board) break;

        ClearBackground(WHITE);
        BeginDrawing();
            DrawMatrix(nextBoard);
            if (!game_is_paused)
            updateBoard(board, nextBoard);
        EndDrawing();
    }
    freeBoard(board);
    freeBoard(nextBoard);

    return 0;
}



