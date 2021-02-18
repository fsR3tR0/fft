#include <stdio.h>
#include <SDL/SDL.h>

#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32

void DrawScreen()
{
    // Draw everything you need here
}

int main(int argc, char* argv[])
{
    SDL_Surface *screen;
    SDL_Event event;

    int keypress = 0;
    int h=0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;

    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_OPENGL|SDL_HWSURFACE|SDL_DOUBLEBUF)))
    {
        SDL_Quit();
        return 1;
    }

    while(!keypress)
    {
         DrawScreen(screen,h++);
         while(SDL_PollEvent(&event))
         {
              switch (event.type)
              {
                  case SDL_QUIT:
	              keypress = 1;
	              break;
                  case SDL_KEYDOWN:
                       keypress = 1;
                       break;
              }
         }
    }

    SDL_Quit();

    return 0;
}
