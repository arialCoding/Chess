#include "Board.h"

#define PIECE_SIZE 83

SDL_Texture* piecesTextureSheet;

/*
void printBoard(uint8_t board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            printf("%i , ", board[i][j]);
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

    board->board[0][0] = ROOK;
    board->board[0][7] = ROOK;
    board->board[7][0] = ROOK;
    board->board[7][7] = ROOK;

    board->board[0][2] = BICHOP;
    board->board[0][5] = BICHOP;
    board->board[7][2] = BICHOP;
    board->board[7][5] = BICHOP;

    board->board[0][1] = KNIGHT;
    board->board[0][6] = KNIGHT;
    board->board[7][1] = KNIGHT;
    board->board[7][6] = KNIGHT;

    board->board[0][4] = KING;
    board->board[7][4] = KING;

    board->board[0][3] = QUEEN;
    board->board[7][3] = QUEEN;

    for(int i = 0; i < 8; i++)
    {
        board->board[1][i] = PAWN;
        board->board[6][i] = PAWN;
    }

    piecesTextureSheet = HL_LoadTexture("resource/pieces.png", handler);

    for(int i = 0; i < 64; i++)
    {
        int row = (int)i/8;
        int col = i%8;

        board->cells[i].PiecesTex = piecesTextureSheet;
        board->cells[i].type = board->board[row][col];
        board->cells[i].team = (row <= 1) ? BLACK : (row >= 6) ? WHITE : NONE;

        board->cells[i].src.x = (board->cells[i].type - 1) * PIECE_SIZE;
        board->cells[i].src.y = (board->cells[i].team - 1) * PIECE_SIZE;
        board->cells[i].src.w = PIECE_SIZE;
        board->cells[i].src.h = PIECE_SIZE;


        board->cells[i].dest.x = col * PIECE_SIZE;
        board->cells[i].dest.y = row * PIECE_SIZE;
        board->cells[i].dest.w = PIECE_SIZE;
        board->cells[i].dest.h = PIECE_SIZE;

    }


}

void refreshBoard(Board* board)
{
     for(int i = 0; i < 64; i++)
    {
        int row = (int)i/8;
        int col = i%8;

        board->cells[i].type = board->board[row][col];
        board->cells[i].team = (row <= 1) ? BLACK : (row >= 6) ? WHITE : NONE;

        board->cells[i].src.x = (board->cells[i].type - 1) * PIECE_SIZE;
        board->cells[i].src.y = (board->cells[i].team - 1) * PIECE_SIZE;
        board->cells[i].src.w = PIECE_SIZE;
        board->cells[i].src.h = PIECE_SIZE;


        board->cells[i].dest.x = col * PIECE_SIZE;
        board->cells[i].dest.y = row * PIECE_SIZE;
        board->cells[i].dest.w = PIECE_SIZE;
        board->cells[i].dest.h = PIECE_SIZE;

    }
}

int mouseStartingX = 0;
int mouseStartingY = 0;
uint8_t selectedPiece = 0;

void updateBoard(Board* board, Handler* handler)
{
    if(handler->mouse[0])
    {
        SDL_GetMouseState(&mouseStartingX, &mouseStartingY);
        mouseStartingX /= PIECE_SIZE;
        mouseStartingY /= PIECE_SIZE;
        selectedPiece = board->board[mouseStartingY][mouseStartingX];
        if(selectedPiece != EMPTY)
        {  
            //calculate possible moves;
        }

    }else if(selectedPiece != EMPTY)
    {
        int mouseCurrentX, mouseCurrentY;
        SDL_GetMouseState(&mouseCurrentX, &mouseCurrentY);

        mouseCurrentX /= PIECE_SIZE;
        mouseCurrentY /= PIECE_SIZE;

        board->board[mouseStartingY][mouseStartingX] = EMPTY;
        board->board[mouseCurrentY][mouseCurrentX] = selectedPiece;

    }

   refreshBoard(board);
}

void drawBoard(Board* board, Handler* handler)
{
    SDL_RenderCopy(handler->renderer, board->BoardTex, &board->boardSrc, NULL);

    for(int i = 0; i < 64; i++)
    {
        if(board->cells[i].type != NONE)
        {
            SDL_RenderCopy(handler->renderer, board->cells[i].PiecesTex, &board->cells[i].src, &board->cells[i].dest);
        }
    }

}