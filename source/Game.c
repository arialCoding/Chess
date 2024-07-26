#include "Game.h"
#include "Logic.h"

#define PIECE_SIZE 83

SDL_Texture* piecesTextureSheet;

/*
static void printBoard(Cell board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            printf("(%i , %i);", board[i][j].type, board[i][j].team);
        }
        printf("\n");
    }
}
*/

void initBoard(Board* board, Handler* handler)
{

    board->BoardTex = HL_LoadTexture("resource/board.png", handler);

    board->boardSrc.x = 0;
    board->boardSrc.y = 0;
    board->boardSrc.w = 8;
    board->boardSrc.h = 8;

    resetBoard(board);

    piecesTextureSheet = HL_LoadTexture("resource/pieces.png", handler);

    //printBoard(board->board);

}

void resetBoard(Board* board)
{
    memset(board->board, 0, sizeof(board->board));

    //setting up pieces in the board matrix
    board->board[0][0].type = ROOK;
    board->board[0][7].type = ROOK;
    board->board[7][0].type = ROOK;
    board->board[7][7].type = ROOK;
    board->board[0][2].type = BICHOP;
    board->board[0][5].type = BICHOP;
    board->board[7][2].type = BICHOP;
    board->board[7][5].type = BICHOP;
    board->board[0][1].type = KNIGHT;
    board->board[0][6].type = KNIGHT;
    board->board[7][1].type = KNIGHT;
    board->board[7][6].type = KNIGHT;
    board->board[0][4].type = KING;
    board->board[7][4].type = KING;
    board->board[0][3].type = QUEEN;
    board->board[7][3].type = QUEEN;

    for(int i = 0; i < 8; i++)
    {
        board->board[1][i].type = PAWN;
        board->board[6][i].type = PAWN;

        board->board[0][i].team = BLACK;
        board->board[1][i].team = BLACK;

        board->board[6][i].team = WHITE;
        board->board[7][i].team = WHITE;
    }
}

static int mousePressedX;
static int mousePressedY;
static uint8_t gotMousePressingPos = 0;

static int mouseReleasedX;
static int mouseReleasedY;
static uint8_t gotMouseReleasingPos = 0;

void updateBoard(Board* board, Handler* handler)
{


    if(handler->LMBpressed)
    {
        mousePressedX = handler->mouseX;
        mousePressedY = handler->mouseY;
        gotMousePressingPos = 1;
    }
    if(handler->LMBreleased)
    {
        mouseReleasedX = handler->mouseX;
        mouseReleasedY = handler->mouseY;
        gotMouseReleasingPos = 1;
    }

    if(gotMousePressingPos && gotMouseReleasingPos)
    {
        gotMousePressingPos = 0;
        gotMouseReleasingPos = 0;
        handleMovement(board, mousePressedX, mousePressedY, mouseReleasedX, mouseReleasedY);
    }

}

static SDL_Rect src, dest;

void drawBoard(Board* board, Handler* handler)
{
    SDL_RenderCopy(handler->renderer, board->BoardTex, &board->boardSrc, NULL);
    
    Uint8 row = 0, col = 0;

    for(int i = 0; i < 64; i++)
    {
        row = i/8;
        col = i%8;

        if(board->board[row][col].type)
        {
            src.x = (board->board[row][col].type - 1)*PIECE_SIZE;
            src.y = (board->board[row][col].team - 1)*PIECE_SIZE;
            src.w = PIECE_SIZE;
            src.h = PIECE_SIZE;

            dest.x = col*PIECE_SIZE;
            dest.y = row*PIECE_SIZE;
            dest.w = PIECE_SIZE;
            dest.h = PIECE_SIZE;

            SDL_RenderCopy(handler->renderer, piecesTextureSheet, &src, &dest);

        }

    }

}