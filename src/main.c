#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include "gameoflife.h"


#define L 3
#define C 3

int main(int argc, char **argv){
    if (argc != 2) exit(INVALID_ARGUMENTS_ERROR);

    InitWindow(1920, 1080, "Game Of Life");
    if (!IsWindowReady()) exit(WINDOW_INIT_FAIL);
    SetWindowMonitor(0);

    Board *board = getBoard(argv[1]);
    if (!board) exit(FILE_READ_FAIL); // change later; mem leaks WILL happen

    // start game rendering
    while (!WindowShouldClose()){
        ClearBackground(WHITE);

        BeginDrawing();
            
        EndDrawing();
    }
    return 0;
}



