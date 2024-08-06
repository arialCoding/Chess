#ifndef BOARD_H
#define BOARD_H

#include "Handler.h"

//pieces
typedef enum {
    EMPTY,
    KING,
    QUEEN,
    BICHOP,
    KNIGHT,
    ROOK,
    PAWN
}pieces;

//teams
typedef enum {
    NONE,
    WHITE,
    BLACK
}teams;

typedef struct
{
    pieces type;
    teams team;
    uint8_t controlledByWhite;
    uint8_t controlledByBlack;
}Cell;

typedef struct
{
    SDL_Texture* BoardTex;

    SDL_Rect boardSrc;

    Cell board[8][8];

    uint8_t whiteKingRow, whiteKingCol;
    uint8_t blackKingRow, blackKingCol;

    int currentTurn;
    int nextTurn;
}Board;

void initBoard(Board* board, Handler* handler);

void resetBoard(Board* board);

void updateBoard(Board* board, Handler* handler);

void drawBoard(Board* board, Handler* handler);

#endif //BOARD_H