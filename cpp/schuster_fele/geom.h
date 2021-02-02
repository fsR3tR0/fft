/** \file geom.h
	\brief  Az  alapvet� geometriai rajzol�f�ggv�nyek tal�lhat�ak itt.
	\author gerg�

	7 rajzol�f�ggv�ny melyek seg�ts�g�vel megrajzolhatunk. alapvet� geometriai alkzatokat.
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

/** \brief L�trehoz egy kit�lt�tt t�glalapot a k�perny�n
	\param x A t�glalap bal fels� pontj�nak x koordin�t�ja.
	\param y A t�glalap bal fels� pontj�nak y koordin�t�ja.
	\param xx A t�glalap jobb als� pontj�nak x koordin�t�ja.
	\param yy A t�glalap jobb als� pontj�nak y koordin�t�ja.
	\param R	a t�glalap kit�lt�si sz�n�nek PIROS �sszetev�je
	\param G	a t�glalap kit�lt�si sz�n�nek Z�LD �sszetev�je
	\param B	a t�glalap kit�lt�si sz�n�nek K�K �sszetev�je

	\ingroup GEOM
	
	A t�glalap koordin�t�i lehetnek nagyobbak az ablak�n�l, csak az eredm�ny nem fog l�tszani<br>
	T�r�lni �gy lehet grafikus k�perny�n, hogy egy h�tt�rsz�n� t�glalapot rajzolunk, a t�r�lni kiv�nt objektumra.<br>
	Extra : ez a leggyorsabb t�rl�si �s ter�letfelt�lt�si m�d!
	
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



/** \brief L�trehoz egy kit�lt�tt t�glalapot a k�perny�n
	\param x A t�glalap bal fels� pontj�nak x koordin�t�ja.
	\param y A t�glalap bal fels� pontj�nak y koordin�t�ja.
	\param xx A t�glalap jobb als� pontj�nak x koordin�t�ja.
	\param yy A t�glalap jobb als� pontj�nak y koordin�t�ja.
	\param col A kit�lt�s sz�ne, ide lehet �rni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A t�glalap koordin�t�i lehetnek nagyobbak az ablak�n�l, csak az eredm�ny nem fog l�tszani<br>
	T�r�lni �gy lehet grafikus k�perny�n, hogy egy h�tt�rsz�n� t�glalapot rajzolunk, a t�r�lni kiv�nt objektumra.<br>
	Extra : ez a leggyorsabb t�rl�si �s ter�letfelt�lt�si m�d!
	
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

/** \brief L�trehoz egy kit�lt�tt t�glalapot a k�perny�n, de nem friss�ti mag�t a k�pet
	\param x A t�glalap bal fels� pontj�nak x koordin�t�ja.
	\param y A t�glalap bal fels� pontj�nak y koordin�t�ja.
	\param xx A t�glalap jobb als� pontj�nak x koordin�t�ja.
	\param yy A t�glalap jobb als� pontj�nak y koordin�t�ja.
	\param col A kit�lt�s sz�ne, ide lehet �rni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A t�glalap koordin�t�i NEM lehetnek nagyobbak az ablak�n�l.<br>
	Mivel nem friss�t ez�rt ut�nna majd nek�nk kell friss�teni a k�pet,<br>
	SDL_Flip(screen) vagy SDL_UpdateRect() f�ggv�nyekkel!
	FONTOS: ha ezt j�l hszn�lj�tok, akkor egy anim�ci�n�l nem fog bevillogni a k�p!
	
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


/** \brief Vonalat h�z a k�perny�n, kezd� �s v�gpontja k�z�tt
	\param x A vonal egyik pontj�nak x koordin�t�ja.
	\param y A vonal egyik pontj�nak y koordin�t�ja.
	\param xx A vonal m�sik pontj�nak x koordin�t�ja.
	\param yy A vonal m�sik pontj�nak y koordin�t�ja.
	\param R	a vonal sz�n�nek PIROS �sszetev�je
	\param G	a vonal sz�n�nek Z�LD �sszetev�je
	\param B	a vonal sz�n�nek K�K �sszetev�je

	\ingroup GEOM
	
	A vonal megrajzol�s�hoz teh�t k�t pontot kell megadni -�gy n�gy koordin�t�t<br>
	A vonal vastags�ga 1 pixel.
	
	\include  line_01.c
	
	\bug A 0.3 ban �s a 0.4 -ben bugos volt!
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


/** \brief Vonalat h�z a k�perny�n, kezd� �s v�gpontja k�z�tt
	\param x A vonal egyik pontj�nak x koordin�t�ja.
	\param y A vonal egyik pontj�nak y koordin�t�ja.
	\param xx A vonal m�sik pontj�nak x koordin�t�ja.
	\param yy A vonal m�sik pontj�nak y koordin�t�ja.
	\param color A vonal sz�ne, ide lehet �rni konstansokat is!  \ref COLORS "COLORS" 

	\ingroup GEOM

	A vonal megrajzol�s�hoz teh�t k�t pontot kell megadni -�gy n�gy koordin�t�t<br>
	A vonal vastags�ga 1 pixel.
	
	\include  line_00.c
	\bug A 0.3 ban �s a 0.4 -ben bugos volt!
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



/** \brief K�rt rajzol.
	\param x A k�r k�z�ppontj�nak x koordin�t�ja.
	\param y A k�r k�z�ppontj�nak y koordin�t�ja.
	\param r A k�r sugara.
	\param R	a k�rvonal kit�lt�si sz�n�nek PIROS �sszetev�je
	\param G	a k�rvonal kit�lt�si sz�n�nek Z�LD �sszetev�je
	\param B	a k�rvonal kit�lt�si sz�n�nek K�K �sszetev�je

	\ingroup GEOM

	A vonal megrajzol�s�hoz teh�t egy k�z�ppontot �s a sugarat kell megadni<br>
	A k�rvonal vastags�ga 1 pixel.
	
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


/** \brief K�rt rajzol.
	\param x A k�r k�z�ppontj�nak x koordin�t�ja.
	\param y A k�r k�z�ppontj�nak y koordin�t�ja.
	\param r A k�r sugara.
	\param color	A k�rvonal sz�ne, ide lehet �rni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM

	A vonal megrajzol�s�hoz teh�t egy k�z�ppontot �s a sugarat kell megadni<br>
	A k�rvonal vastags�ga 1 pixel.
	
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


/** \brief Kit�lt�tt k�rt rajzol.
	\param x A k�r k�z�ppontj�nak x koordin�t�ja.
	\param y A k�r k�z�ppontj�nak y koordin�t�ja.
	\param r A k�r sugara.
	\param R	a k�rkit�lt�si sz�n�nek PIROS �sszetev�je
	\param G	a k�rkit�lt�si sz�n�nek Z�LD �sszetev�je
	\param B	a k�rkit�lt�si sz�n�nek K�K �sszetev�je
	\ingroup GEOM

	A kit�lt�tt k�r megrajzol�s�hoz teh�t egy k�z�ppontot �s a sugarat kell megadni.<br>
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


/** \brief Kit�lt�tt k�rt rajzol.
	\param x A k�r k�z�ppontj�nak x koordin�t�ja.
	\param y A k�r k�z�ppontj�nak y koordin�t�ja.
	\param r A k�r sugara.
	\param color A k�r kit�lt�si sz�ne, ide lehet �rni konstansokat is!  \ref COLORS "COLORS"

	\ingroup GEOM

	A kit�lt�tt k�r megrajzol�s�hoz teh�t egy k�z�ppontot �s a sugarat kell megadni.<br>
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



/** \brief Az eredeti DrawPixel f�ggv�ny Marius Andra-t�l

	\author Marius Andra
	
	M�r nem ezeket a f�ggv�nyeket ahaszn�ljuk, de mivel t�le tanultam az SDL-t
	�gy meg�rdemli, hogy itt megeml�tsem a nev�t!
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

/** \brief Az eredeti DrawPixel f�ggv�ny Marius Andra-t�l

	\author Marius Andra
	
	M�r nem ezeket a f�ggv�nyeket ahaszn�ljuk, de mivel t�le tanultam az SDL-t
	�gy meg�rdemli, hogy itt megeml�tsem a nev�t!
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



/** \brief Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel.
	\param x A pont x koordin�t�ja.
	\param y A pont y koordin�t�ja.
	\param color A pont sz�ne, ide lehet �rni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM
	
	Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel.
	A legegyszer�bb razol�f�ggv�ny, m�gis b�rmit fel lehet �p�teni bel�le!<br>
	
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


/** \brief Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel.
	\param x A pont x koordin�t�ja.
	\param y A pont y koordin�t�ja.
	\param R	a pont sz�n�nek PIROS �sszetev�je
	\param G	a pont sz�n�nek Z�LD �sszetev�je
	\param B	a pont sz�n�nek K�K �sszetev�je

	\ingroup GEOM
	
	Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel.
	A legegyszer�bb razol�f�ggv�ny, m�gis b�rmit fel lehet �p�teni bel�le!<br>
	
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

/** \brief Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel, DE nem friss�ti ut�nna a k�pter�letet.
	\param x A pont x koordin�t�ja.
	\param y A pont y koordin�t�ja.
	\param color A pont sz�ne, ide lehet �rni konstansokat is! \ref COLORS "COLORS"

	\ingroup GEOM
	
	Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel, DE nem friss�ti ut�nna a k�pter�letet.
	Extra: a f�ggv�ny az�rt hasznos, mert: egy ter�letet sima putpixel()-ekkel is fel lehet t�lteni, de mivel mindegyik
	megrajzol�sa ut�n a rendszer friss�ti a k�perny�t, sokat lassul a kirjazol�s!<br>
	Ha ezzel a fv()-vel rajzolunk, akkor a csak a v�g�n kell friss�teni a k�perny�t �s az eredm�ny
	gyorsabban �s egyszerre l�tszik!
	
	\see 	pixel_03.c
*/

void fast_putpixel(int x, int y, Uint32 color)
{
   *((Uint32 *)screen->pixels+x+y*screen->w) = color;
//SDL_Flip(screen);
}

/** \brief Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel, DE nem friss�ti ut�nna a k�pter�letet.
	\param x A pont x koordin�t�ja.
	\param y A pont y koordin�t�ja.
	\param R	a pont sz�n�nek PIROS �sszetev�je
	\param G	a pont sz�n�nek Z�LD �sszetev�je
	\param B	a pont sz�n�nek K�K �sszetev�je

	\ingroup GEOM
	
	Egy pixelt t�lt fel a k�perny�n a megadott sz�nnel, DE nem friss�ti ut�nna a k�pter�letet.
	Extra: a f�ggv�ny az�rt hasznos, mert: egy ter�letet sima putpixel()-ekkel is fel lehet t�lteni, de mivel mindegyik
	megrajzol�sa ut�n a rendszer friss�ti a k�perny�t, sokat lassul a kirjazol�s!<br>
	Ha ezzel a fv()-vel rajzolunk, akkor a csak a v�g�n kell friss�teni a k�perny�t �s az eredm�ny
	gyorsabban �s egyszerre l�tszik!
	
	\see 	pixel_03.c
*/

void fast_putpixel_rgb(int x,int y,int R, int G, int B)
{
    Uint32 color;

    color= SDL_MapRGB(screen->format, R,G,B);

    *((Uint32 *)screen->pixels+x+y*screen->w) = color;
//SDL_Flip(screen);
}

