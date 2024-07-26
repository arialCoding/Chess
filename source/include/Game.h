#ifndef BOARD_H
#define BOARD_H

#include "Handler.h"

//pieces
enum {
    EMPTY,
    KING,
    QUEEN,
    BICHOP,
    KNIGHT,
    ROOK,
    PAWN
};

//teams
enum {
    NONE,
    WHITE,
    BLACK
};

typedef struct
{
    uint8_t type;
    uint8_t team;

}Cell;

typedef struct
{
    SDL_Texture* BoardTex;

    SDL_Rect boardSrc;

    Cell board[8][8];
}Board;

void initBoard(Board* board, Handler* handler);

void resetBoard(Board* board);

void updateBoard(Board* board, Handler* handler);

void drawBoard(Board* board, Handler* handler);

#endif //BOARD_H