#include "App.h"
#include "Handler.h"

static const unsigned int SCREEN_WIDTH = 640;
static const unsigned int SCREEN_HEIGHT = 640;

Handler handler;

void Run()
{
    if(!HL_Init("Chess", SCREEN_WIDTH, SCREEN_HEIGHT, &handler))
    {
        printf("failed creating handler!\n");
        return;
    }

    float dt = 0.f;

    while(handler.running)
    {
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
    SDL_RenderClear(handler.renderer);


    SDL_RenderPresent(handler.renderer);
}
void Quit()
{

}
