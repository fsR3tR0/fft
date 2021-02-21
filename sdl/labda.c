#include "labda.h"

u32 idozit(u32 ms,void *param){
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	SDL_PushEvent(&ev);
	return ms;
}
