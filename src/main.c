#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"

#define FPS 15
#define FPS_PAUSE 500

#define CHAR_LIM 20

int main(int argc, char **argv){
    char *filename = NULL;
    if (argc == 2) filename = argv[1];
    else if (argc > 2) exit(INVALID_ARGUMENTS_ERROR);

    int width = GetMonitorWidth(MONITOR);
    int height = GetMonitorHeight(MONITOR);

    InitWindow(width, height, "Game Of Life");
    if (!IsWindowReady()) exit(WINDOW_INIT_FAIL);
    SetWindowMonitor(MONITOR);
    SetExitKey(KEY_RIGHT_CONTROL); // force quit key

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
    char saveName[CHAR_LIM + 1];
    int char_count = 0;
    bool saving = 0;
    int key;

    // start game loop
    while (!WindowShouldClose()){
        save_status = 0;
        if (!saving && IsKeyPressed(KEY_ESCAPE)) break; // close
        if (!saving && IsKeyPressed(KEY_UP)) SetTargetFPS(fps++); // speed up
        if (!saving && IsKeyPressed(KEY_DOWN) && fps > 1) SetTargetFPS(fps--); // speed down
        if (!saving && IsKeyPressed(KEY_R)) { // reload file
            reset_status = resetGameState(board, nextBoard, argv[1], &error);
            if (reset_status) break;
        }
        if (!saving && IsKeyPressed(KEY_SPACE)){ // pause
            game_is_paused = !game_is_paused;
            if (game_is_paused) SetTargetFPS(FPS_PAUSE);
            else SetTargetFPS(fps);
        }
        // saving to file
        if (!saving && IsKeyPressed(KEY_S)) saving = 1;
        if (saving){
            key = GetCharPressed();
            DrawText(saveName, GetRenderWidth()/2, GetRenderHeight()/2, 50, BLACK);
            if (key > 0 && char_count <= CHAR_LIM){;

                saveName[char_count] = (char) key;
                char_count++;
                saveName[char_count] = '\0';

            }
            if (IsKeyPressed(KEY_ENTER)){
                printf("saving to %s\n", saveName);
                save_status = saveBoardToFile(saveName, nextBoard);
                if (save_status) printf("error saving file! (ERROR %i)\n", save_status);

                char_count = 0;
                saveName[0] = '\0';
                saving = 0;
            }
            if (IsKeyPressed(KEY_BACKSPACE)){
                char_count--;
                char_count *= char_count >= 0;
                saveName[char_count] = '\0';
            }
            if (IsKeyPressed(KEY_ESCAPE)){
                char_count = 0;
                saveName[0] = '\0';
                saving = 0;
            }
        }

        // drawing
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) mouseCellForce(nextBoard);

        copyBoard(board, nextBoard);
        if (!board) break;

        // rendering
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



