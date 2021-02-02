#include "SDL/SDL_mixer.h"



void music(char *filename);

void music(char *filename)
{
        Mix_Music *music;

     //   if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
     //   {return;        }

   //     music = Mix_LoadMUS(filename);
     Mix_PlayMusic(music,-1);

}


