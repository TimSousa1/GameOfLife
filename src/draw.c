#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <stdbool.h>
#include "gameoflife.h"

void DrawMatrix(Board *board){
    int screenW = GetRenderWidth();
    int screenH = GetRenderHeight();

    int posx, posy, w, h;
    w = screenW / board->size.x;
    h = screenH / board->size.y;

    for (uint l = 0; l < board->size.y; l++){
        for (uint c = 0; c < board->size.x; c++){
            if (board->matrix[l][c]) {
                posx = (int) convert(c, (Vector2) {0, board->size.x}, (Vector2) {0, screenW});
                posy = (int) convert(l, (Vector2) {0, board->size.y}, (Vector2) {0, screenH});
                DrawRectangle(posx, posy, w, h, BLACK);
            }
        }
    }
}

float convert(float conv, Vector2 init, Vector2 final){
    float idelta, fdelta, ret;
    idelta = init.y - init.x;
    fdelta = final.y - final.x;
    ret = (((conv - init.x) * fdelta) / idelta) + final.x;
    return ret;
}

