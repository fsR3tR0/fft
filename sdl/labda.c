#include "labda.h"

u32 idozit(u32 ms,void *param){
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	SDL_PushEvent(&ev);
	return ms;
}

u32 idozit2(u32 ms,void *param){
	SDL_Event ev;
	ev.type = SDL_USEREVENT+1;
	SDL_PushEvent(&ev);
	return ms;
}
