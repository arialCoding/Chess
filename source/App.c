#include "App.h"
#include "Handler.h"

static const unsigned int SCREEN_WIDTH = 640;
static const unsigned int SCREEN_HEIGHT = 640;

Handler handler;

SDL_Texture* board;
SDL_Rect src = {0, 0, 8, 8};

void Run()
{
    if(!HL_Init("Chess", SCREEN_WIDTH, SCREEN_HEIGHT, &handler))
    {
        printf("failed creating handler!\n");
        return;
    }

    board = HL_LoadTexture("resource/board.png", &handler);

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

void Update(float dt)
{
    HL_HandleEvents(&handler);
}
void Render()
{
    HL_ClearRenderer(&handler);

    SDL_RenderCopy(handler.renderer, board, &src, NULL);

    HL_PresentRenderer(&handler);
}
void Quit()
{
    HL_CleanUp(&handler);
}
