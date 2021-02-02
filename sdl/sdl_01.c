#include "include.h"
#include "sdl_ablak.h"
#include "sdl_ablak.c"


void sdl_init2(u16 x, u16 y, SDL_Window **pwindow, SDL_Renderer **prenderer){
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
                SDL_Log("Hiba: %s",SDL_GetError());
                exit(1);
        }

        SDL_Window *window = SDL_CreateWindow("Proba",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,x,y,0);
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


int main(int argc, char *argv[])
{
	u16 magassag = 100, szelesseg = 100;
	SDL_Window *window;
	SDL_Renderer *renderer;

	test(123);
	sdl_init2(400, 400, &window, &renderer);

	if(argc > 1){
		printf("%s\n",argv[1]);
	}
	//string kiiras
	stringRGBA(renderer,110,350,"Szovegecske",255,255,255,255);
/*

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		SDL_Log("Hiba: %s",SDL_GetError());
		exit(1);
	}

	SDL_Window *window = SDL_CreateWindow("Proba",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,440,360,0);
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
*/
	SDL_RenderPresent(renderer);




	//itt kell egy resz ami fogja a programot h ne zarodjon be egybol
		//varunk amig nem nyomjuk meg a kilepest
	SDL_Event veg;
	while(SDL_WaitEvent(&veg) && veg.type != SDL_QUIT){};

	SDL_Quit();

	return 0;
}
