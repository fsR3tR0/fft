#include "sdl_ablak.h"
#include "include.h"

int main(int argc, char *argv[])
{
	SDL_Window *window;
	SDL_Renderer *render;

	sdl_init(700,700,&window, &render,"Event-Rajzvaszon");
//	SDL_RenderClear(render);
	stringRGBA(render,10,10,"Feher",255,255,255,255);
	SDL_RenderPresent(render);
	
	int flag0 = 0;
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
					torol = true;
					elozox = event.button.x;
                                        elozoy = event.button.y;
				}
			 break;
			case SDL_MOUSEBUTTONUP:
				if(event.button.button == SDL_BUTTON_LEFT){
					click = false;
				}else if(event.button.button == SDL_BUTTON_RIGHT){
                                  	torol = false;
                                }
			 break;
			case SDL_MOUSEMOTION:
				if(click){
		/*			lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0xFF,0xFF,0x00,0xFF);
					stringRGBA(render,10,10,"Valami",255,255,255,255);
					rajzoltam = true;
					//aalineColor(render, elozox, elozoy, event.motion.x, event.motion.y, 0xFFFFFFFF);
		*/			switch(flag0){
						case 0:
							if(elozoy > 25){
								lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0xFF,0xFF,0xFF,0xFF);
//								stringRGBA(render,10,10,"Feher",255,255,255,255);
								rajzoltam = true;
							}
						 break;
						case 1:
							if(elozoy > 25){
								lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0xFF,0x00,0x00,0xFF);
								rajzoltam = true;
							}
						 break;
						case 2:
							if(elozoy > 25){
								lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0x00,0xFF,0x00,0xFF);
								rajzoltam = true;
						 	}
						 break;
						case 3:
							if(elozoy > 25){
								lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0x00,0x00,0xFF,0xFF);
								rajzoltam = true;
						 	}
						 break;
						case 4:
							if(elozoy > 25){
								lineRGBA(render,elozox,elozoy,event.motion.x,event.motion.y,0xFF,0xFF,0x00,0xFF);
								rajzoltam = true;
						 	}
						 break;
					}
				}else if(torol && elozoy > 25){
				//	lineRGBA(render, elozox, elozoy, event.motion.x, event.motion.y,0x00	,0x00,0x00, 0xFF);
                                  	rajzoltam = true;
					filledCircleRGBA(render,elozox, elozoy, 5, 0x00, 0x00,0x00,0xFF);
				}
				elozox = event.motion.x;
				elozoy = event.motion.y;
			 break;
			case SDL_KEYUP:
				//SDL_RenderClear(render);
//				boxRGBA(render, 0, 0, 700, 700, 0x00, 0x00, 0x00, 0xFF);
//				rajzoltam = true;
			 break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_LEFT:
						if(flag0 > 0){
							flag0--;
						}
						switch(flag0){
                                        	        case 0:
                                                 		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
						                stringRGBA(render,10,10,"Feher",255,255,255,255);
                                                 		rajzoltam = true;
                                                	 break;
                                                	case 1:
                                                      		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Piros",255,255,255,255);
                                                    		rajzoltam = true;
                                                 	 break;
                                                	case 2:
  								boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
                                                        	stringRGBA(render,10,10,"Zold",255,255,255,255);
                                                        	rajzoltam = true;
                                                 	 break;
                                                	case 3:
                                                       		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Kek",255,255,255,255);
                                                     		rajzoltam = true;
                                                 	 break;
                                                	case 4:
                                                        	boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Narga",255,255,255,255);
                                                        	rajzoltam = true;
                                                 	break;
						}

					 break;
					case SDLK_RIGHT:
						if(flag0 < 4){
							flag0++;
						}
						switch(flag0){
                                        	        case 0:
                                                 		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
						                stringRGBA(render,10,10,"Feher",255,255,255,255);
                                                 		rajzoltam = true;
                                                	 break;
                                                	case 1:
                                                      		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Piros",255,255,255,255);
                                                    		rajzoltam = true;
                                                 	 break;
                                                	case 2:
  								boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
                                                        	stringRGBA(render,10,10,"Zold",255,255,255,255);
                                                        	rajzoltam = true;
                                                 	 break;
                                                	case 3:
                                                       		boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Kek",255,255,255,255);
                                                     		rajzoltam = true;
                                                 	 break;
                                                	case 4:
                                                        	boxRGBA(render,0,0,60,25,0x00,0x00,0x00,0xFF);
								stringRGBA(render,10,10,"Narga",255,255,255,255);
                                                        	rajzoltam = true;
                                                 	break;
						}
					 break;
					case SDLK_UP:
						boxRGBA(render,60,0,700,700,0x00,0x00,0x00,0xFF);
						boxRGBA(render, 0, 25, 700, 700, 0x00, 0x00, 0x00, 0xFF);
	                      		        rajzoltam = true;
					 break;
				}
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
