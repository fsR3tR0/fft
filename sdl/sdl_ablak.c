#include "sdl_ablak.h"

void sdl_init(u16 x, u16 y, SDL_Window **pwindow, SDL_Renderer **prenderer,char *name){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
                SDL_Log("Hiba: %s",SDL_GetError());
                exit(1);
        }

        SDL_Window *window = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,x,y,0);
 	if(window == NULL){
                SDL_Log("Hiba: %s",SDL_GetError());
                exit(1);
        }

        SDL_Renderer *renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_SOFTWARE);
        if(renderer == NULL){
                SDL_Log("Hiba: %s",SDL_GetError());
                exit(1);
	}
        SDL_RenderClear(renderer);

	*pwindow = window;
	*prenderer = renderer;
}

void test(u8 k){
	printf("%d",k);
}
