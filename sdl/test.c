#include "include.h"

int main(int argc, char *argv[])
{
	printf("%s\n",argv[1]);

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

	//itt kell egy resz ami fogja a programot h ne zarodjon be egybol
		//varunk amig nem nyomjuk meg a kilepest
	SDL_Event veg;
	while(SDL_WaitEvent(&veg) && veg.type != SDL_QUIT){};

	SDL_Quit();

	return 0;
}
