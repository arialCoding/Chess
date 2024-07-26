#ifndef HANDLER_H
#define HANDLER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "stdio.h"

typedef struct{

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    uint8_t input[256];
    uint8_t running;

    int mouseX;
    int mouseY;

    uint8_t LMBpressed;
    uint8_t RMBpressed;
    uint8_t MMBpressed;

    uint8_t LMBreleased;
    uint8_t RMBreleased;
    uint8_t MMBreleased;

} Handler;

int HL_Init(const char* title, int w, int h, Handler* handler);

void HL_HandleEvents(Handler* handler);

void HL_ClearRenderer(Handler* handler);
void HL_PresentRenderer(Handler* handler);

SDL_Texture* HL_LoadTexture(const char* path, Handler* handler);

void HL_CleanUp(Handler* handler);


#endif //HANDLER_H