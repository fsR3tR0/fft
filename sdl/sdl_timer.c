#include "include.h"
#include "sdl_ablak.h"
#include "labda.h"

#define ABLAK 500
#define GOLYO_R 10

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool quit = false;
	
	sdl_init(ABLAK,ABLAK,&window,&renderer,"Timer");
	
	SDL_TimerID id = SDL_AddTimer(20,idozit,NULL);
	
	labda g;
	g.x = ABLAK/2;
	g.y = ABLAK/3;
	g.vx = 3;
	g.vy = 2;
	
	while(!quit){
		SDL_Event event;
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_USEREVENT:
				filledCircleRGBA(renderer, g.x, g.y, GOLYO_R, 0x20, 0x20, 0x40, 0xFF);
                		/* kiszamitjuk az uj helyet */
               	 		g.x += g.vx;
               			g.y += g.vy;
                		/* visszapattanás */
                		if (g.x < GOLYO_R || g.x > ABLAK-GOLYO_R)
                   			g.vx *= -1;
                		if (g.y < GOLYO_R || g.y > ABLAK-GOLYO_R)
                   			g.vy *= -1;
                		/* ujra kirajzolas, es mehet a kepernyore */
                		filledCircleRGBA(renderer, g.x, g.y, GOLYO_R, 0x80, 0x80, 0xFF, 0xFF);
                		SDL_RenderPresent(renderer);
               		 break;
 
           	 	case SDL_QUIT:
                		quit = true;
                	 break;
        	}
    	}
    /* idozito torlese */
    	SDL_RemoveTimer(id);
	
	/*
	SDL_Event veg;
	while(SDL_WaitEvent(&veg) && veg.type != SDL_QUIT);
	*/
        SDL_Quit();

	return 0;
}
