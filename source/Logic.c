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

void setControlledCells(Board* board)
{
     for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {
            board->board[r][c].controlledByWhite = 0;
            board->board[r][c].controlledByBlack = 0;
        }
    }

    for(int r = 0; r < 8; r++)
    {
        for(int c = 0; c < 8; c++)
        {

            switch(board->board[r][c].type)
            {
                case KING:
                    kingSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                case QUEEN:
                    queenSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                case BICHOP:
                    bichopSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                case KNIGHT:
                    knightSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                case ROOK:
                    rookSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                case PAWN:
                    pawnSetControlledSquares(board, board->board[r][c].team, c, r);
                    break;
                default:
                    break;
            }

        }
    }
}

  //////////////////////////////////////////////////////////////////////////////////
 /////                 checking moves validity                               //////
//////////////////////////////////////////////////////////////////////////////////

uint8_t pawnMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called pawn\n");

    return 1;
}

uint8_t kingMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called king\n");
    if( (board->board[destRow][destCol].controlledByWhite && board->board[srcRow][srcCol].team == BLACK) ||
        (board->board[destRow][destCol].controlledByBlack && board->board[srcRow][srcCol].team == WHITE))
        return 0;

    if(abs(destCol - srcCol) == 1 || abs(destRow - srcRow) == 1)
        return 1;    

    return 0;

}

uint8_t queenMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called queen\n");

    return 1;

}

static const int8_t knightMoves[8][2] = {
        { 2,  1},//bottom right
        { 1,  2},//corners

        { 2, -1},//top right
        { 1, -2},//corners

        {-2,  1},//bottom left
        {-1,  2},//corners

        {-2, -1},//top left
        {-1, -2}//corners
};

uint8_t knightMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{

    for(int i = 0; i < 8; i++)
    {
        if(destCol == srcCol + knightMoves[i][0] && destRow == srcRow + knightMoves[i][1])
            return 1;
    }


    return 0;

}

uint8_t bichopMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called bichop\n");

    return 1;

}

uint8_t rookMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called rook\n");
    if(srcRow != destRow && srcCol != destCol)
        return 0;

    if(srcRow == destRow)
    {
        int i = (srcCol < destCol) ? srcCol + 1 : destCol + 1;
        int end = (srcCol > destCol) ? srcCol : destCol;
        for(i = i; i < end; i++)
        {
            if(board->board[srcRow][i].type != EMPTY)
                return 0;
        }
    }
   if(srcCol == destCol)
    {
        int i = (srcRow < destRow) ? srcRow + 1 : destRow + 1;
        int end = (srcRow > destRow) ? srcRow : destRow;
        for(i = i; i < end; i++)
        {
            if(board->board[i][srcCol].type != EMPTY)
                return 0;
        }
    }

    return 1;
}

  /////////////////////////////////////////////////////////////////////////////////////
 /////                 setting controlled squares                               //////
/////////////////////////////////////////////////////////////////////////////////////
void pawnSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{
    if(team == WHITE)
    {
        if(pieceRow - 1 >= 0)
        {
            if(pieceCol + 1 <= 7)
                board->board[pieceRow - 1][pieceCol + 1].controlledByWhite = 1;//top right
            if(pieceCol - 1 >= 0)
                board->board[pieceRow - 1][pieceCol - 1].controlledByWhite = 1;//top left
        }
    }
    else if(team == BLACK)
    {
        if(pieceRow + 1 <= 7)
        {
            if(pieceCol + 1 <= 7)
                board->board[pieceRow + 1][pieceCol + 1].controlledByBlack = 1;//top right
            if(pieceCol - 1 >= 0)
                board->board[pieceRow + 1][pieceCol - 1].controlledByBlack = 1;//top left
        }

    }
}

void kingSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{
    if(team == WHITE)
    {
        if(pieceRow + 1 <= 7)
        {
            board->board[pieceRow + 1][pieceCol].controlledByWhite = 1;//under the king
            if(pieceCol - 1 >= 0) board->board[pieceRow + 1][pieceCol - 1].controlledByWhite = 1;//down left
            if(pieceCol + 1 <= 7) board->board[pieceRow + 1][pieceCol + 1].controlledByWhite = 1;//down right
        }

        if(pieceCol - 1 >= 0) board->board[pieceRow][pieceCol - 1].controlledByWhite = 1;//left
        if(pieceCol + 1 <= 7) board->board[pieceRow][pieceCol + 1].controlledByWhite = 1;//right

        if(pieceRow - 1 >= 0)
        {
            board->board[pieceRow - 1][pieceCol].controlledByWhite = 1;//above the king
            if(pieceCol - 1 >= 0) board->board[pieceRow - 1][pieceCol - 1].controlledByWhite = 1;//top left
            if(pieceCol + 1 <= 7) board->board[pieceRow - 1][pieceCol + 1].controlledByWhite = 1;//top right
        }
    }
    else if(team == BLACK)
    {
        if(pieceRow + 1 <= 7)
        {
            board->board[pieceRow + 1][pieceCol].controlledByBlack = 1;//under the king
            if(pieceCol - 1 >= 0) board->board[pieceRow + 1][pieceCol - 1].controlledByBlack = 1;//down left
            if(pieceCol + 1 <= 7) board->board[pieceRow + 1][pieceCol + 1].controlledByBlack = 1;//down right
        }

        if(pieceCol - 1 >= 0) board->board[pieceRow][pieceCol - 1].controlledByBlack = 1;//left
        if(pieceCol + 1 <= 7) board->board[pieceRow][pieceCol + 1].controlledByBlack = 1;//right

        if(pieceRow - 1 >= 0)
        {
            board->board[pieceRow - 1][pieceCol].controlledByBlack = 1;//above the king
            if(pieceCol - 1 >= 0) board->board[pieceRow - 1][pieceCol - 1].controlledByBlack = 1;//top left
            if(pieceCol + 1 <= 7) board->board[pieceRow - 1][pieceCol + 1].controlledByBlack = 1;//top right
        }
    }
}

void queenSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{

}

void knightSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{
    for(int i = 0; i < 8; i++)
    {
        if(pieceRow + knightMoves[i][0] <= 7 && pieceRow + knightMoves[i][0] >= 0)
            if(pieceCol + knightMoves[i][1] <= 7 && pieceCol + knightMoves[i][1] >= 0)
                if(team == WHITE)
                    board->board[pieceRow + knightMoves[i][0]][pieceCol + knightMoves[i][1]].controlledByWhite = 1;
                else
                    board->board[pieceRow + knightMoves[i][0]][pieceCol + knightMoves[i][1]].controlledByBlack = 1;
    }
}

void bichopSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{
   
}
void rookSetControlledSquares(Board* board, teams team, int pieceCol, int pieceRow)
{
    uint8_t left = 1, right = 1, top = 1, bottom = 1;
    int i = 1;

    while(left || right || top || bottom)
    {
        if(right)
        {
            if(pieceCol + i < 8)
            {
                if(board->board[pieceRow][pieceCol + i].type != EMPTY)
                {
                    if(team == WHITE)
                        board->board[pieceRow][pieceCol + i].controlledByWhite = 1;
                    else
                        board->board[pieceRow][pieceCol + i].controlledByBlack = 1;
                    right = 0;
                }
                else
                    if(team == WHITE)
                        board->board[pieceRow][pieceCol + i].controlledByWhite = 1;
                    else
                        board->board[pieceRow][pieceCol + i].controlledByBlack = 1;
            }else right = 0;
        }
        if(left)
        {
            if(pieceCol - i >= 0)
            {
                if(board->board[pieceRow][pieceCol - i].type != EMPTY)
                {
                    if(team == WHITE)
                        board->board[pieceRow][pieceCol - i].controlledByWhite = 1;
                    else
                        board->board[pieceRow][pieceCol - i].controlledByBlack = 1;
                    left = 0;
                }
                else
                    if(team == WHITE)
                        board->board[pieceRow][pieceCol - i].controlledByWhite = 1;
                    else
                        board->board[pieceRow][pieceCol - i].controlledByBlack = 1;
            }else left = 0;
        }
        if(top)
        {
            if(pieceRow - i >= 0)
            {
                if(board->board[pieceRow - i][pieceCol].type != EMPTY)
                {
                    if(team == WHITE)
                        board->board[pieceRow - i][pieceCol].controlledByWhite = 1;
                    else
                        board->board[pieceRow - i][pieceCol].controlledByBlack = 1;
                    top = 0;
                }
                else
                    if(team == WHITE)
                        board->board[pieceRow - i][pieceCol].controlledByWhite = 1;
                    else
                        board->board[pieceRow - i][pieceCol].controlledByBlack = 1;
            }else top = 0;
        }
        if(bottom)
        {
            if(pieceRow + i < 8)
            {
                if(board->board[pieceRow + i][pieceCol].type != EMPTY)
                {
                    if(team == WHITE)
                        board->board[pieceRow + i][pieceCol].controlledByWhite = 1;
                    else
                        board->board[pieceRow + i][pieceCol].controlledByBlack = 1;
                    bottom = 0;
                }
                else
                    if(team == WHITE)
                        board->board[pieceRow + i][pieceCol].controlledByWhite = 1;
                    else
                        board->board[pieceRow + i][pieceCol].controlledByBlack = 1;
            }else bottom = 0;
        }
        i++;
    }

}

/*static const int8_t knightMoves[8][2] = {
        { 2,  1},//bottom right
        { 1,  2},//corners

        { 2, -1},//top right
        { 1, -2},//corners

        {-2,  1},//bottom left
        {-1,  2},//corners

        {-2, -1},//top left
        {-1, -2}//corners
};*/