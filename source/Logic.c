#include "Logic.h"

void handleMovement(Board* board, int mousePressedX, int mousePressedY, int mouseReleasedX, int mouseReleasedY)
{
    //printf("pressed at (%i, %i)\nreleased at (%i, %i)\n", mousePressedX/83, mousePressedY/83, mouseReleasedX/83, mouseReleasedY/83);
    mousePressedX /= 83;
    mousePressedY /= 83;
    mouseReleasedX /= 83;
    mouseReleasedY /= 83;

    uint8_t selectedType = board->board[mousePressedY][mousePressedX].type;
    uint8_t selectedTeam = board->board[mousePressedY][mousePressedX].team;

    board->board[mousePressedY][mousePressedX].type = EMPTY;
    board->board[mousePressedY][mousePressedX].team = NONE;

    board->board[mouseReleasedY][mouseReleasedX].type = selectedType;
    board->board[mouseReleasedY][mouseReleasedX].team = selectedTeam;
}