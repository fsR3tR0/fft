#include "sdl_ablak.h"
#include "include.h"

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *render;

	sdl_init(700,700,&window, &render,"Event-Rajzvaszon");
//	SDL_RenderClear(render);

	bool quit = false;
	bool click = false;
	bool torol = false;
	bool rajzoltam = false;
	int elozox = 0;
	int elozoy = 0;

	while(!quit){
		SDL_Event event;
		SDL_WaitEvent(&event);
		switch(event.type){
			case SDL_MOUSEBUTTONDOWN:
				if(event.button.button == SDL_BUTTON_LEFT){
					click = true;
					elozox = event.button.x;
					elozoy = event.button.y;
				}else if(event.button.button == SDL_BUTTON_RIGHT){
					//SDL_RenderClear(render);
				//	boxColor(render,100,100,100,100,0x00000FFF);
			//		rajzoltam = true;
					torol = true;
					elozox = event.button.x;
                                        elozoy = event.button.y;
				}
			 break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT){
					click = false;
				}else if(event.button.button == SDL_BUTTON_RIGHT){
                                        //SDL_RenderClear(render);
                                  //     boxColor(render,1000,1000,1000,1000,0x0);
                                       // rajzoltam = true;
					torol = false;
                                }
			 break;
			case SDL_MOUSEMOTION:
				if(click){
					aalineColor(render, elozox, elozoy, event.motion.x, event.motion.y, 0xFFFFFFFF);
					rajzoltam = true;
				}else if(torol){
				//	lineRGBA(render, elozox, elozoy, event.motion.x, event.motion.y,0x00	,0x00,0x00, 0xFF);
                                  	rajzoltam = true;
					filledCircleRGBA(render,elozox, elozoy, 5, 0x00, 0x00,0x00,0xFF);
				}
				elozox = event.motion.x;
				elozoy = event.motion.y;
			 break;
			case SDL_KEYUP:
				//SDL_RenderClear(render);
				boxRGBA(render, 0, 0, 700, 700, 0x00, 0x00, 0x00, 0xFF);
				rajzoltam = true;
			 break;
			case SDL_QUIT:
				quit = true;
			 break;
		}
		if(rajzoltam){
			SDL_RenderPresent(render);
		}
	}
	SDL_Quit();

	return 0;
}
