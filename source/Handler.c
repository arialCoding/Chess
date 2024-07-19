#include "Handler.h"

int HL_Init(const char* title, int w, int h, Handler* handler)
{
    int SDL_INIT_SUCCESS = SDL_Init(SDL_INIT_EVERYTHING);
    if(SDL_INIT_SUCCESS < 0)
    {
        printf("failed to init SDL2. ERR: %s\n", SDL_GetError());
        return 0;
    }

    int IMG_INIT_SUCCESS = IMG_Init(IMG_INIT_PNG);
    if(!IMG_INIT_SUCCESS)
    {
        printf("failed to init SDL2_image. ERR: %s\n", SDL_GetError());
        return 0;
    }
    
    handler->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(!handler->window)
    {
        printf("failed to create window. ERR: %s\n", SDL_GetError());
        return 0;    
    }

    handler->renderer = SDL_CreateRenderer(handler->window, -1, 0);
    if(!handler->renderer)
    {
        printf("failed to create renderer. ERR: %s\n", SDL_GetError());
        return 0;    
    }

    for(int i = 0; i < 256; i++)
    {
        handler->input[i] = 0;
    }

    handler->running = 1;

    return 1;
}

void HL_HandleEvents(Handler* handler)
{
    while(SDL_PollEvent(&handler->event))
    {
        switch (handler->event.type)
        {
            case SDL_QUIT:
                handler->running = 0;
                break;
            
            case SDL_KEYDOWN:
                handler->input[handler->event.key.keysym.scancode] = 1;
                break;

            case SDL_KEYUP:
                handler->input[handler->event.key.keysym.scancode] = 1;
                break;

            default:
                break;
        }
    }
}

void HL_CleanUp(Handler* handler)
{
    SDL_DestroyRenderer(handler->renderer);
    SDL_DestroyWindow(handler->window);
    IMG_Quit();
    SDL_Quit();
}