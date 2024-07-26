#include "Logic.h"

int currentTurn = WHITE; 
int nextTurn = BLACK; 

void handleMovement(Board* board, int mousePressedX, int mousePressedY, int mouseReleasedX, int mouseReleasedY)
{
    //printf("pressed at (%i, %i)\nreleased at (%i, %i)\n", mousePressedX/83, mousePressedY/83, mouseReleasedX/83, mouseReleasedY/83);
    int srcRow = mousePressedX / 83;
    int srcCol = mousePressedY / 83;
    int destRow = mouseReleasedX / 83;
    int destCol = mouseReleasedY / 83;

    if(isMoveValid(board, srcRow, srcCol, destRow, destCol))
    {
        uint8_t selectedType = board->board[srcCol][srcRow].type;
        uint8_t selectedTeam = board->board[srcCol][srcRow].team;

        board->board[srcCol][srcRow].type = EMPTY;
        board->board[srcCol][srcRow].team = NONE;

        board->board[destCol][destRow].type = selectedType;
        board->board[destCol][destRow].team = selectedTeam;

        int temp = currentTurn;
        currentTurn = nextTurn;
        nextTurn = temp;

    }
}

uint8_t isMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{

    //taking a piece with the same color
    if(board->board[destRow][destCol].team == board->board[srcRow][srcCol].team)
        return 0;

    //moving opponent's piece
    if(board->board[srcRow][srcCol].team != currentTurn)
        return 0;

    switch (board->board[srcRow][srcCol].type)
    {
    case KING:
        return kingMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;
    case QUEEN:
        return queenMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;
    case KNIGHT:
        return knightMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;
    case BICHOP:
        return bichopMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;
    case ROOK:
        return rookMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;
    case PAWN:
        return pawnMoveValid(board, srcCol, srcRow, destCol, destRow);
        break;    
    default:
        break;
    }

    return 1;
}

uint8_t pawnMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called pawn\n");

    return 1;
}

uint8_t kingMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called king\n");

    return 1;

}

uint8_t queenMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called queen\n");

    return 1;

}

uint8_t knightMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called knight\n");

    return 1;

}

uint8_t bichopMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called bichop\n");

    return 1;

}

uint8_t rookMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called rook\n");

    return 1;

}

