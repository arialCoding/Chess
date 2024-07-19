#include "Handler.h"

static const unsigned int SCREEN_WIDTH = 640;
static const unsigned int SCREEN_HEIGHT = 640;


int main(int argc, char const *argv[])
{

    Handler handler;

    if(!HL_Init("Chess", SCREEN_WIDTH, SCREEN_HEIGHT, &handler))
    {
        printf("failed creating handler!\n");
        return -1;
    }

    while(handler.running)
    {
        HL_HandleEvents(&handler);

        SDL_RenderClear(handler.renderer);


        SDL_RenderPresent(handler.renderer);
    }

    HL_CleanUp(&handler);

    return 0;
}
