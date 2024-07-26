#ifndef BOARD_H
#define BOARD_H

#include "Handler.h"

enum {
    EMPTY,
    KING,
    QUEEN,
    BICHOP,
    KNIGHT,
    ROOK,
    PAWN
};

enum {
    NONE,
    WHITE,
    BLACK
};

typedef struct
{
    SDL_Texture* PiecesTex;

    uint8_t type;
    uint8_t team;

    SDL_Rect src;
    SDL_Rect dest;

}Cell;

typedef struct
{
    SDL_Texture* BoardTex;

    SDL_Rect boardSrc;

    uint8_t board[8][8];
    Cell cells[64];
}Board;

void initBoard(Board* board, Handler* handler);

void updateBoard(Board* board, Handler* handler);

void drawBoard(Board* board, Handler* handler);

#endif //BOARD_H