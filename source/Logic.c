#include "Logic.h"

static void printBoard(Cell board[8][8])
{
    system("cls");
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            printf("(%i , %i);", board[i][j].controlledByWhite, board[i][j].controlledByBlack);
        }
        printf("\n");
    }
}

void handleMovement(Board* board, int mousePressedX, int mousePressedY, int mouseReleasedX, int mouseReleasedY)
{
    //printf("pressed at (%i, %i)\nreleased at (%i, %i)\n", mousePressedX/83, mousePressedY/83, mouseReleasedX/83, mouseReleasedY/83);
    int srcRow = mousePressedY / 83;
    int srcCol = mousePressedX / 83;
    int destRow = mouseReleasedY / 83;
    int destCol = mouseReleasedX / 83;

    if(isMoveValid(board, srcCol, srcRow, destCol, destRow))
    {
        Board testBoard = *board;

        uint8_t temp_whiteKingRow = board->whiteKingRow;
        uint8_t temp_whiteKingCol = board->whiteKingCol;
        uint8_t temp_blackKingRow = board->blackKingRow;
        uint8_t temp_blackKingCol = board->blackKingCol;

        uint8_t selectedType = testBoard.board[srcRow][srcCol].type;
        uint8_t selectedTeam = testBoard.board[srcRow][srcCol].team;

        testBoard.board[srcRow][srcCol].type = EMPTY;
        testBoard.board[srcRow][srcCol].team = NONE;

        testBoard.board[destRow][destCol].type = selectedType;
        testBoard.board[destRow][destCol].team = selectedTeam;

        if(selectedType == KING)
        {
            if(selectedTeam == WHITE)
            {
                board->whiteKingRow = destRow;
                board->whiteKingCol = destCol;
            }
            else if(selectedTeam == BLACK)
            {
                board->blackKingRow = destRow;
                board->blackKingCol = destCol;
            }
        }

        setControlledCells(&testBoard);

        if((board->currentTurn == WHITE && testBoard.board[board->whiteKingRow][board->whiteKingCol].controlledByBlack) || (board->currentTurn == BLACK && testBoard.board[board->blackKingRow][board->blackKingCol].controlledByWhite))
        {
            board->whiteKingRow = temp_whiteKingRow;
            board->whiteKingCol = temp_whiteKingCol;
            board->blackKingRow = temp_blackKingRow;
            board->blackKingCol = temp_blackKingCol;
            return;
        }
        
        *board = testBoard;

        int temp = board->currentTurn;
        board->currentTurn = board->nextTurn;
        board->nextTurn = temp;

    }

}

uint8_t isMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{

    //taking a piece with the same color
    if(board->board[destRow][destCol].team == board->board[srcRow][srcCol].team)
        return 0;

    //moving opponent's piece
    if(board->board[srcRow][srcCol].team != board->currentTurn)
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

    //can only move if no piece is right ahead
    if((board->board[srcRow][srcCol].team == WHITE && board->board[srcRow - 1][srcCol].type == EMPTY) ||
       (board->board[srcRow][srcCol].team == BLACK && board->board[srcRow + 1][srcCol].type == EMPTY))
    {
        if((board->board[srcRow][srcCol].team == WHITE && srcRow == 6) || (board->board[srcRow][srcCol].team == BLACK && srcRow == 1))
        {
            if(srcCol == destCol && abs(destRow - srcRow) == 2 && board->board[srcRow + (destRow - srcRow)][srcCol].type == EMPTY)//allow 2 squares at first move
                return 1;
        }
        
        if(srcCol == destCol && abs(destRow - srcRow) == 1)
        {
            if(board->board[srcRow][srcCol].team == WHITE && destRow < srcRow)
                return 1;
            if(board->board[srcRow][srcCol].team == BLACK && destRow > srcRow)
                return 1;
            return 0;
        }

    }

    if(board->board[srcRow][srcCol].team == WHITE)
    {
        if(destCol == srcCol + 1 && destRow == srcRow - 1)
            return board->board[destRow][destCol].team == BLACK;
        else if(destCol == srcCol - 1 && destRow == srcRow - 1)
            return board->board[destRow][destCol].team == BLACK;
    }

    if(board->board[srcRow][srcCol].team == BLACK)
    {
        if(destCol == srcCol + 1 && destRow == srcRow + 1)
            return board->board[destRow][destCol].team == WHITE;
        else if(destCol == srcCol - 1 && destRow == srcRow + 1)
            return board->board[destRow][destCol].team == WHITE;
    }

    return 0;
}

uint8_t kingMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called king\n");
    //can only move one square
    if(abs(destCol - srcCol) <= 1 && abs(destRow - srcRow) <= 1)
        return 1;    

    return 0;

}

uint8_t queenMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called queen\n");
    return rookMoveValid(board, srcCol, srcRow, destCol, destRow) || bichopMoveValid(board, srcCol, srcRow, destCol, destRow);
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
    //can only move in straight diagonals
    if(abs(destCol - srcCol) != abs(destRow - srcRow))
        return 0;

    if(destCol > srcCol)
    {
        if(destRow > srcRow)
        {
            int startCol = srcCol + 1, startRow = srcRow + 1;
            while(startCol < destCol && startRow < destRow)
            {
                if(board->board[startRow][startCol].type != EMPTY)
                    return 0;
                startCol++;
                startRow++;
            }
        }
        else if(destRow < srcRow)
        {
            int startCol = srcCol + 1, startRow = srcRow - 1;
            while(startCol < destCol && startRow > destRow)
            {
                if(board->board[startRow][startCol].type != EMPTY)
                    return 0;
                startCol++;
                startRow--;
            }
        }
    }
    else if(destCol < srcCol)
    {
        if(destRow > srcRow)
        {
            int startCol = srcCol - 1, startRow = srcRow + 1;
            while(startCol > destCol && startRow < destRow)
            {
                if(board->board[startRow][startCol].type != EMPTY)
                    return 0;
                startCol--;
                startRow++;
            }
        }else if(destRow < srcRow)
        {
            int startCol = srcCol - 1, startRow = srcRow - 1;
            while(startCol > destCol && startRow > destRow)
            {
                if(board->board[startRow][startCol].type != EMPTY)
                    return 0;
                startCol--;
                startRow--;
            }
        }
    }

    return 1;

}

uint8_t rookMoveValid(Board* board, int srcCol, int srcRow, int destCol, int destRow)
{
    //printf("called rook\n");
    //can't move diagonally 
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
    bichopSetControlledSquares(board, team, pieceCol, pieceRow);
    rookSetControlledSquares(board, team, pieceCol, pieceRow);
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
    uint8_t topRight = 1, topLeft = 1, bottomRight = 1, bottomLeft = 1;
    int i = 1;

    while(topRight || topLeft || bottomRight || bottomLeft)
    {
        if(topRight)
        {
            if(pieceCol + i <= 7 && pieceRow - i >= 0)
            {
                if(team == WHITE)
                    board->board[pieceRow - i][pieceCol + i].controlledByWhite = 1;
                else 
                    board->board[pieceRow - i][pieceCol + i].controlledByBlack = 1;

                if(board->board[pieceRow - i][pieceCol + i].type != EMPTY)
                    topRight = 0;
            } else topRight = 0;
        }
        if(topLeft)
        {
            if(pieceCol - i >= 0 && pieceRow - i >= 0)
            {
                if(team == WHITE)
                    board->board[pieceRow - i][pieceCol - i].controlledByWhite = 1;
                else 
                    board->board[pieceRow - i][pieceCol - i].controlledByBlack = 1;

                if(board->board[pieceRow - i][pieceCol - i].type != EMPTY)
                    topLeft = 0;
            } else topLeft = 0;
        }
        if(bottomRight)
        {
            if(pieceCol + i <= 7 && pieceRow + i <= 7)
            {
                if(team == WHITE)
                    board->board[pieceRow + i][pieceCol + i].controlledByWhite = 1;
                else 
                    board->board[pieceRow + i][pieceCol + i].controlledByBlack = 1;

                if(board->board[pieceRow + i][pieceCol + i].type != EMPTY)
                    bottomRight = 0;
            } else bottomRight = 0;
        }
        if(bottomLeft)
        {
            if(pieceCol - i >= 0 && pieceRow + i <= 7)
            {
                if(team == WHITE)
                    board->board[pieceRow + i][pieceCol - i].controlledByWhite = 1;
                else 
                    board->board[pieceRow + i][pieceCol - i].controlledByBlack = 1;

                if(board->board[pieceRow + i][pieceCol - i].type != EMPTY)
                    bottomLeft = 0;
            } else bottomLeft = 0;
        }
        i++;
    }

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


uint8_t testForCheckMate(Board* board)
{
    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            if(board->board[row][col].type != EMPTY && board->board[row][col].team == board->currentTurn)
            {
                for(int r = 0; r < 8; r++)
                {
                    for(int c = 0; c < 8; c++)
                    { 
                        if(isMoveValid(board, col, row, c, r))
                        {
                            Board testBoard = *board;

                            uint8_t temp_whiteKingRow = board->whiteKingRow;
                            uint8_t temp_whiteKingCol = board->whiteKingCol;
                            uint8_t temp_blackKingRow = board->blackKingRow;
                            uint8_t temp_blackKingCol = board->blackKingCol;

                            uint8_t selectedType = testBoard.board[row][col].type;
                            uint8_t selectedTeam = testBoard.board[row][col].team;

                            testBoard.board[row][col].type = EMPTY;
                            testBoard.board[row][col].team = NONE;

                            testBoard.board[r][c].type = selectedType;
                            testBoard.board[r][c].team = selectedTeam;

                            if(selectedType == KING)
                            {
                                if(selectedTeam == WHITE)
                                {
                                    board->whiteKingRow = r;
                                    board->whiteKingCol = c;
                                }
                                else if(selectedTeam == BLACK)
                                {
                                    board->blackKingRow = r;
                                    board->blackKingCol = c;
                                }
                            }

                            setControlledCells(&testBoard);

                            if((board->currentTurn == WHITE && testBoard.board[board->whiteKingRow][board->whiteKingCol].controlledByBlack) || (board->currentTurn == BLACK && testBoard.board[board->blackKingRow][board->blackKingCol].controlledByWhite))
                            {
                                board->whiteKingRow = temp_whiteKingRow;
                                board->whiteKingCol = temp_whiteKingCol;
                                board->blackKingRow = temp_blackKingRow;
                                board->blackKingCol = temp_blackKingCol;
                                continue;
                            }else return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}