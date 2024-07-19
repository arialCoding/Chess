#include <SDL2/SDL.h>


int main(int argc, char const *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    

    SDL_Event event;

    int running = 1;

    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                running = 0;
        }
    }

    return 0;
}
