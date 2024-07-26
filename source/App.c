#include "App.h"
#include "Handler.h"

#include "Board.h"

static const unsigned int SCREEN_WIDTH = 83*8;
static const unsigned int SCREEN_HEIGHT = 83*8;

Handler handler;

Board board;

void Run()
{
    Init();
    
    float dt = 0.f;
    int frameStart = 0;

    while(handler.running)
    {
        dt = (SDL_GetTicks() - frameStart)/1000.f;
        frameStart = SDL_GetTicks();
        
        Update(dt);
        Render();
    }

    HL_CleanUp(&handler);

}

void Init()
{
    if(!HL_Init("Chess", SCREEN_WIDTH, SCREEN_HEIGHT, &handler))
    {
        printf("failed creating handler!\n");
        return;
    }

    initBoard(&board, &handler);

}

void Update(float dt)
{
    HL_HandleEvents(&handler);

    updateBoard(&board, &handler);
}
void Render()
{
    HL_ClearRenderer(&handler);
    
    drawBoard(&board, &handler);

    HL_PresentRenderer(&handler);
}
void Quit()
{
    HL_CleanUp(&handler);
}
