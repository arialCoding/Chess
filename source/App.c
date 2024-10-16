#include "App.h"
#include "Handler.h"

#include "Game.h"

static const unsigned int SCREEN_WIDTH = 83*8;
static const unsigned int SCREEN_HEIGHT = 83*8;

Handler handler;

Board board;

//the main game loop
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

    if(handler.input[SDL_SCANCODE_R])
        resetBoard(&board);

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
