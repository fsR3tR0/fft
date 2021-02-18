#include "include.h"
#include "sdl_ablak.h"

int main(int argc, char *argv[])
{
	u16 magassag = 100, szelesseg = 100;
	int x = 0, y = 0, r = 0;
	SDL_Window *window;
	SDL_Renderer *renderer;

	printf("Megy te gechi!\n");

	sdl_init(400, 400, &window, &renderer,"Ablak nev");

	if(argc > 1){
		printf("%s\n",argv[1]);
	}

	//string kiiras
	stringRGBA(renderer,10,10,"Szovegecske",255,255,255,255);

	/* Rajzok */
		//karika
	r = 50;
	x = 100;
	y = 100;
	circleRGBA(renderer, x, y, r, 255, 0, 0, 255);	//voros, zold, kek, atlatszosag
	circleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);

		//antialias karika
	x = 280;
	y = 100;
	aacircleRGBA(renderer, x, y, r, 255, 0, 0, 255);
	aacircleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);

		//kitoltott kor
	x = 100;
	y = 280;
   	filledCircleRGBA(renderer, x, y, r, 255, 0, 0, 255);
   	filledCircleRGBA(renderer, x + r, y, r, 0, 255, 0, 255);

		//attetszo kor
	x = 280;
	y = 280;
    	filledCircleRGBA(renderer, x, y, r, 255, 0, 0, 96);
    	filledCircleRGBA(renderer, x + r, y, r, 0, 255, 0, 96);

	/* Szoveg kiirasas */
	SDL_RenderPresent(renderer);


	//itt kell egy resz ami fogja a programot h ne zarodjon be egybol
		//varunk amig nem nyomjuk meg a kilepest
	SDL_Event veg;
	while(SDL_WaitEvent(&veg) && veg.type != SDL_QUIT){};

	SDL_Quit();	//ablak zarasa

	return 0;
}
