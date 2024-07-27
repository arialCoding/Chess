#ifndef LOGIC_H
#define LOGIC_H

#include "Game.h"


void handleMovement(Board* board, int mousePressedX, int mousePressedY, int mouseReleasedX, int mouseReleasedY);

uint8_t isMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);

void setControlledCells(Board* board);

uint8_t pawnMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);
uint8_t kingMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);
uint8_t queenMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);
uint8_t knightMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);
uint8_t bichopMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);
uint8_t rookMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow);

void pawnSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);
void kingSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);
void queenSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);
void knightSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);
void bichopSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);
void rookSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow);


#endif //LOGIC_H