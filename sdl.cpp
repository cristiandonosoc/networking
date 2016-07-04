#include "SDL.h"
#include <iostream>

void quit(int returnCode)
{
    // TODO(Cristian): SDL Cleanup
    exit(returnCode);
}

void InitSDL(SDL_Rect *viewport,
             SDL_Window **window,
             SDL_Renderer **renderer)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "UNABLE TO INITIALIZE SDL: "
                  << SDL_GetError() << std::endl;
        quit(1);
    }

    (*viewport).x = 0;
    (*viewport).y = 0;
    // TODO(Cristian): Do correct viewport sizing
    (*viewport).w = 800;
    (*viewport).h = 600;

    *window = SDL_CreateWindow("SDL Window",            // Title
                               SDL_WINDOWPOS_UNDEFINED, // Initial x
                               SDL_WINDOWPOS_UNDEFINED, // Initial y
                               (*viewport).w,           // width, in px
                               (*viewport).h,           // height, in px
                               SDL_WINDOW_SHOWN);       // flags

    if (*window  == nullptr)
    {
        std::cerr << "UNABLE TO CREATE WINDOW: "
                  << SDL_GetError() << std::endl;
        quit(1);
    }

    *renderer = SDL_CreateRenderer(*window, -1, 0);
    if (*renderer < 0)
    {
        std::cerr << "UNABLE TO CREATE RENDERER: "
                  << SDL_GetError() << std::endl;
        quit(1);
    }

    SDL_RenderGetViewport(*renderer, viewport);
}

int main(int, char **)
{
    SDL_Rect viewport;
    SDL_Window *window;
    SDL_Renderer *renderer;


    InitSDL(&viewport, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);


}
