#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <stdbool.h>
#include "gameoflife.h"

void DrawMatrix(Board *board){
    Vector2 rCoords;
    for (uint l = 0; l < board->L; l++){
        for (uint c = 0; c < board->C; c++){
            if (board->matrix[l][c]) 
                DrawRectangle(c + GetRenderWidth()/2, l + GetRenderHeight()/2, 1, 1, BLACK);
        }
    }
}

