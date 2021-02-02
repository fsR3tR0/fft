
#include "SDL/SDL_ttf.h"

void ttf(int x,int y,char *str);


void ttf(int x,int y,char *str)
{
printf("ttf1");fflush(stdout);
        //TTF_Init();
       //TTF_Font *ttffont;
	   //ttffont= TTF_OpenFont("lazy.ttf",28);
        //SDL_Color col = { 255, 255, 255 };
       // SDL_Surface *message;

        //message=TTF_RenderText_Solid(ttffont,str,col);

        //SDL_Rect r;
        //r.x=x;
        //r.y=y;


        //SDL_BlitSurface(message,NULL,screen,&r);

       // TTF_CloseFont(ttffont);
	   TTF_Quit();

}

