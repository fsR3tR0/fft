/** \file geom.h
	\brief  Az  alapvetõ geometriai rajzolófüggvények találhatóak itt.
	\author gergõ

	7 rajzolófüggvény melyek segítségével megrajzolhatunk. alapvetõ geometriai alkzatokat.
*/

void fast_putpixel_rgb(int x,int y,int r, int g , int b);
void fast_putpixel(int x,int y,Uint32 col);

void putpixel_rgb(int x,int y,int r, int g , int b);
void putpixel(int x,int y,Uint32 col);


void DrawPixel_rgb(int x, int y,int R, int G, int B); // original DrawPixel_rgb From Marius
void DrawPixel(int x, int y, Uint32 color); // original DrawPixel_rgb From Marius

void circle_rgb (int x, int y,int r, int R, int G , int B); // Bresenham's
void circle     (int x, int y, int r, Uint32 color);

void fillcircle_rgb (int x, int y,int r, int R, int G , int B);   // Bresenham's
void fillcircle (int x, int y,int r, Uint32 color);   // Bresenham's

void line_rgb(int x,int y, int xx, int yy, int R, int G, int B);
void line(int x,int y, int xx, int yy, Uint32 color);

void bar_rgb(int x,int y,int xx, int yy, int R, int G, int B);
void bar(int x,int y,int xx, int yy, Uint32 col);
void bar_nofrs(int x,int y,int xx, int yy, Uint32 col);


//------------------------------------------------------------------------------
//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
//------------------------------------------------------------------------------

/** \brief Létrehoz egy kitöltött téglalapot a képernyõn
	\param x A téglalap bal felsõ pontjának x koordinátája.
	\param y A téglalap bal felsõ pontjának y koordinátája.
	\param xx A téglalap jobb alsó pontjának x koordinátája.
	\param yy A téglalap jobb alsó pontjának y koordinátája.
	\param R	a téglalap kitöltési színének PIROS összetevõje
	\param G	a téglalap kitöltési színének ZÖLD összetevõje
	\param B	a téglalap kitöltési színének KÉK összetevõje

	\ingroup GEOM
	
	A téglalap koordinátái lehetnek nagyobbak az ablakénál, csak az eredmény nem fog látszani<br>
	Törölni úgy lehet grafikus képernyõn, hogy egy háttérszínü téglalapot rajzolunk, a törölni kivánt objektumra.<br>
	Extra : ez a leggyorsabb törlési és területfeltöltési mód!
	
	\include  bar_00.c
*/

void bar_rgb(int x,int y,int xx, int yy, int R, int G, int B)
{
	int temp;
    SDL_Rect r;
	Uint32 col = SDL_MapRGB(screen->format,R,G,B);
	
	if(xx<x) {temp=x;x=xx;xx=temp;}
	if(yy<y) {temp=y;y=yy;yy=temp;}
	
	if(x<0) x=0;
	if(y<0) y=0;
	if(xx>screen->w) xx=screen->w;
	if(yy>screen->h) yy=screen->h;
	
	
	
	r.x=x;
    r.y=y;
    r.w=xx-x+1;
    r.h=yy-y+1;

	// ha kilog a keprol akkor nem csinalom meg
//	if(x<0 || x > screen->w || y<0 || y > screen->h || xx<0 || xx > screen->w || yy<0 || yy > screen->h)
//		return;
	
    
    SDL_FillRect(screen,&r,col);

//	if(r.w+x>screen->w) r.w=screen->w-x;
//	if(r.h+y>screen->h) r.h=screen->w-y;
	
	SDL_UpdateRect(screen,x,y,r.w,r.h);

//SDL_Flip(screen);
}



/** \brief Létrehoz egy kitöltött téglalapot a képernyõn
	\param x A téglalap bal felsõ pontjának x koordinátája.
	\param y A téglalap bal felsõ pontjának y koordinátája.
	\param xx A téglalap jobb alsó pontjának x koordinátája.
	\param yy A téglalap jobb alsó pontjának y koordinátája.
	\param col A kitöltés színe, ide lehet írni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A téglalap koordinátái lehetnek nagyobbak az ablakénál, csak az eredmény nem fog látszani<br>
	Törölni úgy lehet grafikus képernyõn, hogy egy háttérszínü téglalapot rajzolunk, a törölni kivánt objektumra.<br>
	Extra : ez a leggyorsabb törlési és területfeltöltési mód!
	
	\include  bar_00.c
*/
void bar(int x,int y,int xx, int yy,Uint32 col)
//void bar(int x,int y,int xx, int yy, Uint8 R, Uint8 G, Uint8 B)
{
    int temp;
	SDL_Rect r;

	if(xx<x) {temp=x;x=xx;xx=temp;}
	if(yy<y) {temp=y;y=yy;yy=temp;}

	
	if(x<0) x=0;
	if(y<0) y=0;
	if(xx>screen->w) xx=screen->w;
	if(yy>screen->h) yy=screen->h;

    r.x=x;
    r.y=y;
    r.w=xx-x+1;
    r.h=yy-y+1;

	// ha kilog a keprol akkor nem csinalom meg
//	if(x<0 || x > screen->w || y<0 || y > screen->h || xx<0 || xx > screen->w || yy<0 || yy > screen->h)
//		return;
	
    SDL_FillRect(screen,&r,col);
	SDL_UpdateRect(screen,x,y,r.w,r.h);
//SDL_Flip(screen);
}

/** \brief Létrehoz egy kitöltött téglalapot a képernyõn, de nem frissíti magát a képet
	\param x A téglalap bal felsõ pontjának x koordinátája.
	\param y A téglalap bal felsõ pontjának y koordinátája.
	\param xx A téglalap jobb alsó pontjának x koordinátája.
	\param yy A téglalap jobb alsó pontjának y koordinátája.
	\param col A kitöltés színe, ide lehet írni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A téglalap koordinátái NEM lehetnek nagyobbak az ablakénál.<br>
	Mivel nem frissít ezért utánna majd nekünk kell frissíteni a képet,<br>
	SDL_Flip(screen) vagy SDL_UpdateRect() függvényekkel!
	FONTOS: ha ezt jól hsználjátok, akkor egy animációnál nem fog bevillogni a kép!
	
*/
void bar_nofrs(int x,int y,int xx, int yy,Uint32 col)
//void bar(int x,int y,int xx, int yy, Uint8 R, Uint8 G, Uint8 B)
{
    int temp;
	SDL_Rect r;

	if(xx<x) {temp=x;x=xx;xx=temp;}
	if(yy<y) {temp=y;y=yy;yy=temp;}

	
	if(x<0) x=0;
	if(y<0) y=0;
	if(xx>screen->w) xx=screen->w;
	if(yy>screen->h) yy=screen->h;

    r.x=x;
    r.y=y;
    r.w=xx-x+1;
    r.h=yy-y+1;

	// ha kilog a keprol akkor nem csinalom meg
//	if(x<0 || x > screen->w || y<0 || y > screen->h || xx<0 || xx > screen->w || yy<0 || yy > screen->h)
//		return;
	
    SDL_FillRect(screen,&r,col);
	
//SDL_Flip(screen);
}


/** \brief Vonalat húz a képernyõn, kezdõ és végpontja között
	\param x A vonal egyik pontjának x koordinátája.
	\param y A vonal egyik pontjának y koordinátája.
	\param xx A vonal másik pontjának x koordinátája.
	\param yy A vonal másik pontjának y koordinátája.
	\param R	a vonal színének PIROS összetevõje
	\param G	a vonal színének ZÖLD összetevõje
	\param B	a vonal színének KÉK összetevõje

	\ingroup GEOM
	
	A vonal megrajzolásához tehát két pontot kell megadni -így négy koordinátát<br>
	A vonal vastagsága 1 pixel.
	
	\include  line_01.c
	
	\bug A 0.3 ban és a 0.4 -ben bugos volt!
*/


void line_rgb(int x,int y, int xx, int yy, int R, int G, int B)
{
    
     int temp,i,w,h,xb,yb;
    float dx,dy,xpy,ypx;
	Uint32 color=SDL_MapRGB(screen->format,R,G,B);
	

	if(x<0) x=0;
	if(y<0) y=0;
	if(xx>screen->w) xx=screen->w;
	if(yy>screen->h) yy=screen->h;



    dx=xx-x;
    dy=yy-y;

	(x>xx)?(xb=xx):(xb=x);
	(y>yy)?(yb=yy):(yb=y);
	w=(int)fabs(dx);
	h=(int)fabs(dy);
	
	
    if(fabs(dx)>fabs(dy))
    {
    if(xx<=x && yy<=y) {x=xx;y=yy;}

    if(yy>=y && xx<=x) {y=yy;x=xx;}
	ypx=dy/dx;
        dy=0;
        for(temp=0;temp<fabs(dx);temp++,dy=ypx+dy)
            {
            fast_putpixel(x+temp,(int)(y+dy),color);
            }
    }

    else
    {
    if(xx>=x && yy<=y) {x=xx;y=yy;}

    if(yy<=y && xx<=x) {y=yy;x=xx;}
    xpy=dx/dy;
        dx=0;
        for(temp=0;temp<fabs(dy);temp++,dx=xpy+dx)
            {
            fast_putpixel((int)dx+x,temp+y,color);
            }


    }

SDL_UpdateRect(screen,xb,yb,w+1,h+1);

}


/** \brief Vonalat húz a képernyõn, kezdõ és végpontja között
	\param x A vonal egyik pontjának x koordinátája.
	\param y A vonal egyik pontjának y koordinátája.
	\param xx A vonal másik pontjának x koordinátája.
	\param yy A vonal másik pontjának y koordinátája.
	\param color A vonal színe, ide lehet írni konstansokat is!  \ref COLORS "COLORS" 

	\ingroup GEOM

	A vonal megrajzolásához tehát két pontot kell megadni -így négy koordinátát<br>
	A vonal vastagsága 1 pixel.
	
	\include  line_00.c
	\bug A 0.3 ban és a 0.4 -ben bugos volt!
*/

void line(int x,int y, int xx, int yy, Uint32 color)
{
 
       int temp,i,w,h,xb,yb;
    float dx,dy,xpy,ypx;


	if(x<0) x=0;
	if(y<0) y=0;
	if(xx>screen->w) xx=screen->w;
	if(yy>screen->h) yy=screen->h;



    dx=xx-x;
    dy=yy-y;

	(x>xx)?(xb=xx):(xb=x);
	(y>yy)?(yb=yy):(yb=y);
	w=(int)fabs(dx);
	h=(int)fabs(dy);
	
    if(fabs(dx)>fabs(dy))
    {
    if(xx<=x && yy<=y) {x=xx;y=yy;}

    if(yy>=y && xx<=x) {y=yy;x=xx;}
	ypx=dy/dx;
        dy=0;
        for(temp=0;temp<fabs(dx);temp++,dy=ypx+dy)
            {
            fast_putpixel(x+temp,(int)(y+dy),color);
            }
    }

    else
    {
    if(xx>=x && yy<=y) {x=xx;y=yy;}

    if(yy<=y && xx<=x) {y=yy;x=xx;}
    xpy=dx/dy;
        dx=0;
        for(temp=0;temp<fabs(dy);temp++,dx=xpy+dx)
            {
            fast_putpixel((int)dx+x,temp+y,color);
            }


    }

	SDL_UpdateRect(screen,xb,yb,w+1,h+1);

}



/** \brief Kört rajzol.
	\param x A kör középpontjának x koordinátája.
	\param y A kör középpontjának y koordinátája.
	\param r A kör sugara.
	\param R	a körvonal kitöltési színének PIROS összetevõje
	\param G	a körvonal kitöltési színének ZÖLD összetevõje
	\param B	a körvonal kitöltési színének KÉK összetevõje

	\ingroup GEOM

	A vonal megrajzolásához tehát egy középpontot és a sugarat kell megadni<br>
	A körvonal vastagsága 1 pixel.
	
	\include  circle_00.c
*/

void circle_rgb(int x, int y, int r, int R, int G , int B)
{
    Uint32 color=SDL_MapRGB(screen->format,R,G,B);
	int xx,yy,r2=r*r;
	
	// ellenorzo resz
	x=x-r;
	y=y-r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	x=x+2*r;
	y=y+2*r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	
	x=x-r;	// visszaallitom az eredeti xet
	y=y-r;	// visszaallitom az eredeti y t
	// vege az ellenorzo resznek
	
    xx=1;
    yy=(int)(sqrt(r2-xx*xx)+0.5);
    while(xx<=yy)
    {

        fast_putpixel(x+xx,y+yy,color);
        fast_putpixel(x+xx,y-yy,color);

        fast_putpixel(x-xx,y+yy,color);
        fast_putpixel(x-xx,y-yy,color);

        fast_putpixel(x+yy,y+xx,color);
        fast_putpixel(x-yy,y-xx,color);

        fast_putpixel(x+yy,y-xx,color);
        fast_putpixel(x-yy,y+xx,color);
        xx++;
        yy=(int)(sqrt(r2-xx*xx)+0.5);
    }

    fast_putpixel(x,y+r,color);
    fast_putpixel(x,y-r,color);
    fast_putpixel(x-r,y,color);
    fast_putpixel(x+r,y,color);
	SDL_UpdateRect(screen,x-r,y-r,2*r+1,2*r+1);
//SDL_Flip(screen);
}


/** \brief Kört rajzol.
	\param x A kör középpontjának x koordinátája.
	\param y A kör középpontjának y koordinátája.
	\param r A kör sugara.
	\param color	A körvonal színe, ide lehet írni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A vonal megrajzolásához tehát egy középpontot és a sugarat kell megadni<br>
	A körvonal vastagsága 1 pixel.
	
	\include  circle_00.c
*/
void circle(int x, int y,int r, Uint32 color)
{
    int xx,yy,r2=r*r;

	// ellenorzo resz
	x=x-r;
	y=y-r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	x=x+2*r;
	y=y+2*r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	
	x=x-r;	// visszaallitom az eredeti xet
	y=y-r;	// visszaallitom az eredeti y t
	// vege az ellenorzo resznek
	

    xx=1;
    yy=(int)(sqrt(r2-xx*xx)+0.5);
    while(xx<=yy)
    {

        fast_putpixel(x+xx,y+yy,color);
        fast_putpixel(x+xx,y-yy,color);

        fast_putpixel(x-xx,y+yy,color);
        fast_putpixel(x-xx,y-yy,color);

        fast_putpixel(x+yy,y+xx,color);
        fast_putpixel(x-yy,y-xx,color);

        fast_putpixel(x+yy,y-xx,color);
        fast_putpixel(x-yy,y+xx,color);
        xx++;
        yy=(int)(sqrt(r2-xx*xx)+0.5);
    }


    fast_putpixel(x,y+r,color);
    fast_putpixel(x,y-r,color);
    fast_putpixel(x-r,y,color);
    fast_putpixel(x+r,y,color);

		SDL_UpdateRect(screen,x-r,y-r,2*r+1,2*r+1);
//SDL_Flip(screen);
}


/** \brief Kitöltött kört rajzol.
	\param x A kör középpontjának x koordinátája.
	\param y A kör középpontjának y koordinátája.
	\param r A kör sugara.
	\param R	a körkitöltési színének PIROS összetevõje
	\param G	a körkitöltési színének ZÖLD összetevõje
	\param B	a körkitöltési színének KÉK összetevõje
	\ingroup GEOM

	A kitöltött kör megrajzolásához tehát egy középpontot és a sugarat kell megadni.<br>
	\include  fillcircle_00.c
*/
void fillcircle_rgb(int x, int y,int r, int R, int G, int B)
{
    Uint32 color=SDL_MapRGB(screen->format, R, G, B);
    int xx,yy,temp,r2=r*r;
	
	// ellenorzo resz
	x=x-r;
	y=y-r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	x=x+2*r;
	y=y+2*r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	
	x=x-r;	// visszaallitom az eredeti xet
	y=y-r;	// visszaallitom az eredeti y t
	// vege az ellenorzo resznek

	
    xx=1;
    yy=(int)(sqrt(r2-xx*xx)+0.5);
    while(xx<=yy)
    {

        fast_putpixel(x+xx,y+yy,color);
        fast_putpixel(x+xx,y-yy,color);
        fast_putpixel(x-xx,y+yy,color);
        fast_putpixel(x-xx,y-yy,color);

        fast_putpixel(x+yy,y+xx,color);
        fast_putpixel(x-yy,y-xx,color);

        fast_putpixel(x+yy,y-xx,color);
        fast_putpixel(x-yy,y+xx,color);

        //fill

        for(temp=x-xx;temp<=x+xx;temp++)
            {
                fast_putpixel(temp,y+yy,color);
                fast_putpixel(temp,y-yy,color);
                fast_putpixel(temp,y+xx,color);
                fast_putpixel(temp,y-xx,color);
            }

        for(temp=y-xx;temp<=y+xx;temp++)
            {
                fast_putpixel(x+yy,temp,color);
                fast_putpixel(x-yy,temp,color);
                fast_putpixel(x+xx,temp,color);
                fast_putpixel(x-xx,temp,color);
            }





        xx++;
        yy=(int)(sqrt(r2-xx*xx)+0.5);
    }

    fast_putpixel(x,y,color);
    fast_putpixel(x,y+r,color);
    fast_putpixel(x,y-r,color);
    fast_putpixel(x-r,y,color);
    fast_putpixel(x+r,y,color);
	
	SDL_UpdateRect(screen,x-r,y-r,2*r+1,2*r+1);
//SDL_Flip(screen);
}


/** \brief Kitöltött kört rajzol.
	\param x A kör középpontjának x koordinátája.
	\param y A kör középpontjának y koordinátája.
	\param r A kör sugara.
	\param color A kör kitöltési színe, ide lehet írni konstansokat is!  \ref COLORS "COLORS"

	\ingroup GEOM

	A kitöltött kör megrajzolásához tehát egy középpontot és a sugarat kell megadni.<br>
	\include  fillcircle_00.c
*/
void fillcircle(int x, int y,int r, Uint32 color)
{
    int xx,yy,temp,r2=r*r;
    xx=1;
	
	// ellenorzo resz
	x=x-r;
	y=y-r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	x=x+2*r;
	y=y+2*r;
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	
	x=x-r;	// visszaallitom az eredeti xet
	y=y-r;	// visszaallitom az eredeti y t
	// vege az ellenorzo resznek
	
	
    yy=(int)(sqrt(r2-xx*xx)+0.5);
    while(xx<=yy)
    {

        fast_putpixel(x+xx,y+yy,color);
        fast_putpixel(x+xx,y-yy,color);
        fast_putpixel(x-xx,y+yy,color);
        fast_putpixel(x-xx,y-yy,color);

        fast_putpixel(x+yy,y+xx,color);
        fast_putpixel(x-yy,y-xx,color);

        fast_putpixel(x+yy,y-xx,color);
        fast_putpixel(x-yy,y+xx,color);


        for(temp=x-xx;temp<=x+xx;temp++)
            {
                fast_putpixel(temp,y+yy,color);
                fast_putpixel(temp,y-yy,color);
                fast_putpixel(temp,y+xx,color);
                fast_putpixel(temp,y-xx,color);
            }
        for(temp=y-xx;temp<=y+xx;temp++)
            {
                fast_putpixel(x+yy,temp,color);
                fast_putpixel(x-yy,temp,color);
                fast_putpixel(x+xx,temp,color);
                fast_putpixel(x-xx,temp,color);
            }






        xx++;
        yy=(int)(sqrt(r2-xx*xx)+0.5);
    }

    fast_putpixel(x,y,color);
    fast_putpixel(x,y+r,color);
    fast_putpixel(x,y-r,color);
    fast_putpixel(x-r,y,color);
    fast_putpixel(x+r,y,color);

	SDL_UpdateRect(screen,x-r,y-r,2*r+1,2*r+1);
//SDL_Flip(screen);
}



/** \brief Az eredeti DrawPixel függvény Marius Andra-tól

	\author Marius Andra
	
	Már nem ezeket a függvényeket ahasználjuk, de mivel tõle tanultam az SDL-t
	így megérdemli, hogy itt megemlítsem a nevét!
*/
void DrawPixel_rgb(int x, int y, int R, int G, int B) // original DrawPixel_rgb From Marius
{
  Uint32 color = SDL_MapRGB(screen->format, R, G, B);
  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
SDL_Flip(screen);
}

/** \brief Az eredeti DrawPixel függvény Marius Andra-tól

	\author Marius Andra
	
	Már nem ezeket a függvényeket ahasználjuk, de mivel tõle tanultam az SDL-t
	így megérdemli, hogy itt megemlítsem a nevét!
*/
void DrawPixel(int x, int y, Uint32 color) // original DrawPixel_rgb From Marius
{

  switch (screen->format->BytesPerPixel)
  {
    case 1: // Assuming 8-bpp
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
        *bufp = color;
      }
      break;
    case 2: // Probably 15-bpp or 16-bpp
      {
        Uint16 *bufp;
        bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
        *bufp = color;
      }
      break;
    case 3: // Slow 24-bpp mode, usually not used
      {
        Uint8 *bufp;
        bufp = (Uint8 *)screen->pixels + y*screen->pitch + x * 3;
        if(SDL_BYTEORDER == SDL_LIL_ENDIAN)
        {
          bufp[0] = color;
          bufp[1] = color >> 8;
          bufp[2] = color >> 16;
        } else {
          bufp[2] = color;
          bufp[1] = color >> 8;
          bufp[0] = color >> 16;
        }
      }
      break;
    case 4: // Probably 32-bpp
      {
        Uint32 *bufp;
        bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
        *bufp = color;
      }
      break;
  }
SDL_Flip(screen);
}



/** \brief Egy pixelt tölt fel a képernyõn a megadott színnel.
	\param x A pont x koordinátája.
	\param y A pont y koordinátája.
	\param color A pont színe, ide lehet írni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM
	
	Egy pixelt tölt fel a képernyõn a megadott színnel.
	A legegyszerübb razolófüggvény, mégis bármit fel lehet építeni belõle!<br>
	
	\include  pixel_00.c
*/
void putpixel(int x, int y, Uint32 color)
{
	// ellenorzo resz
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	// vege az ellenorzo resznek
   *((Uint32 *)screen->pixels+x+y*screen->w) = color;
   
   SDL_UpdateRect(screen,x,y,1,1);
//SDL_Flip(screen);
}


/** \brief Egy pixelt tölt fel a képernyõn a megadott színnel.
	\param x A pont x koordinátája.
	\param y A pont y koordinátája.
	\param R	a pont színének PIROS összetevõje
	\param G	a pont színének ZÖLD összetevõje
	\param B	a pont színének KÉK összetevõje

	\ingroup GEOM
	
	Egy pixelt tölt fel a képernyõn a megadott színnel.
	A legegyszerübb razolófüggvény, mégis bármit fel lehet építeni belõle!<br>
	
	\include  pixel_00.c
*/
void putpixel_rgb(int x,int y,int R, int G, int B)
{
    Uint32 color;

	// ellenorzo resz
	if(x<0 || x > screen->w || y<0 || y > screen->h)
		return;
	// vege az ellenorzo resznek
	
    color= SDL_MapRGB(screen->format, R,G,B);

    *((Uint32 *)screen->pixels+x+y*screen->w) = color;
	SDL_UpdateRect(screen,x,y,1,1);
//SDL_Flip(screen);
}

/** \brief Egy pixelt tölt fel a képernyõn a megadott színnel, DE nem frissíti utánna a képterületet.
	\param x A pont x koordinátája.
	\param y A pont y koordinátája.
	\param color A pont színe, ide lehet írni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM
	
	Egy pixelt tölt fel a képernyõn a megadott színnel, DE nem frissíti utánna a képterületet.
	Extra: a függvény azért hasznos, mert: egy területet sima putpixel()-ekkel is fel lehet tölteni, de mivel mindegyik
	megrajzolása után a rendszer frissíti a képernyõt, sokat lassul a kirjazolás!<br>
	Ha ezzel a fv()-vel rajzolunk, akkor a csak a végén kell frissíteni a képernyõt és az eredmény
	gyorsabban és egyszerre látszik!
	
	\see 	pixel_03.c
*/

void fast_putpixel(int x, int y, Uint32 color)
{
   *((Uint32 *)screen->pixels+x+y*screen->w) = color;
//SDL_Flip(screen);
}

/** \brief Egy pixelt tölt fel a képernyõn a megadott színnel, DE nem frissíti utánna a képterületet.
	\param x A pont x koordinátája.
	\param y A pont y koordinátája.
	\param R	a pont színének PIROS összetevõje
	\param G	a pont színének ZÖLD összetevõje
	\param B	a pont színének KÉK összetevõje

	\ingroup GEOM
	
	Egy pixelt tölt fel a képernyõn a megadott színnel, DE nem frissíti utánna a képterületet.
	Extra: a függvény azért hasznos, mert: egy területet sima putpixel()-ekkel is fel lehet tölteni, de mivel mindegyik
	megrajzolása után a rendszer frissíti a képernyõt, sokat lassul a kirjazolás!<br>
	Ha ezzel a fv()-vel rajzolunk, akkor a csak a végén kell frissíteni a képernyõt és az eredmény
	gyorsabban és egyszerre látszik!
	
	\see 	pixel_03.c
*/

void fast_putpixel_rgb(int x,int y,int R, int G, int B)
{
    Uint32 color;

    color= SDL_MapRGB(screen->format, R,G,B);

    *((Uint32 *)screen->pixels+x+y*screen->w) = color;
//SDL_Flip(screen);
}

