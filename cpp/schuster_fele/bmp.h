/** \file bmp.h
	\brief  A bmp k�pek kezel�st megval�s�t� f�ggv�nyek
	\author gerg�

	A bmp k�pek kezel�st megval�s�t� f�ggv�nyek
*/

SDL_Surface *pic0,*pic1,*pic2,*pic3,*pic4;
SDL_Surface *ship,*ufo,*sun,*garfield,*elefant;



void ksdl_bmpinit();

void DrawBmp(char *filename,int x,int y);
void DrawPic(SDL_Surface *image,int x,int y);

void DrawBmpMask(char *filename,int x,int y,Uint32 mask);
void DrawPicMask(SDL_Surface *image,int x,int y,Uint32 mask);

void DrawBmpPos(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h);
void DrawPicPos(SDL_Surface *image,int dstx,int dsty,int srcx,int srcy,int w,int h);

void DrawBmpPosMask(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h, Uint32 mask);
void DrawPicPosMask(SDL_Surface *image,int dstx,int dsty,int srcx,int srcy,int w,int h, Uint32 mask);

void MaskPic(SDL_Surface *screen,Uint32 colorkey);

void SetPictureMask_rgb(SDL_Surface *screen,int R, int G, int B);
void SetPictureMask(SDL_Surface *screen,Uint32 colorkey);

SDL_Surface* cut(int x,int y,int w,int h);
void paste(SDL_Surface *image,int x,int y);
SDL_Surface* move(int x, int y, int dx, int dy, SDL_Surface* background, SDL_Surface *image);


/** \brief Adott xy koordin�tkra kirjazol egy bmp f�jlban l�v� k�pet
	\param filename a bmp f�jl el�r�si �tja, pl: "c:\\csoki.bmp"
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazol egy bmp f�jlban l�v� k�pet.
	Lass� lehet, mert mind kirajzol�skor be kell olvasni a f�jlb�l a k�pet!
	Gyorsabb a DrawPic()
	
	\include drawx_01.c
*/
void DrawBmp(char *filename,int x,int y)
{
SDL_Surface *image=SDL_LoadBMP(filename);   // betolti a bmp az image surfacere
DrawPic(image,x,y);
SDL_FreeSurface(image);
}

/** \brief Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�pet
	\param image 	az sdl felsz�n neve ahol k�pet t�roljuk pl: elefant,pic0 ...
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�pet, mivel ez a mem�ri�ban t�rol�dik sokkal gyorsabban el�rhet�
	�s kirajzolhat�.
	A k�rnyezet tartalmaz 5 alapvet� k�pet: pic0,pic1,pic2,pic3,pic4,<br>
	az SDL_LoadBmp() f�ggv�nnyel mi is csin�lhatunk saj�tot.
	
	\include drawx_00.c
*/
void DrawPic(SDL_Surface *image,int x,int y)
{
SDL_Rect r;                                 // negyzet, hogy hova majd az alap
r.x=x;                                     // screen en a kepet
r.y=y;

SDL_BlitSurface(image,  // a kep surface pointere
                NULL,   // negyzet ha a kepbol akarnank kivagni reszeket
                        // mivell NULL ezert az egesz kep jon
                screen, // ahova akarjuk screen az alapfelulet
                &r      // ahova az alapfeluleten akarjuk tenni a kepet
                );

SDL_UpdateRect(screen,x,y,image->w,image->h);
//SDL_Flip(screen);
}

/** \brief Adott xy koordin�tkra kirjazol egy bmp f�jlban l�v� k�pet a megadott MASK-al
	\param filename a bmp f�jl el�r�si �tja, pl: "c:\\csoki.bmp"
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\param mask	Azoknak a k�ppontoknak a sz�ne, melyet a m�sol�skor nem vesz figyelembe
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazol egy bmp f�jlban l�v� k�pet, de csak azokat a k�ppontokat, melyek sz�nei nem egyezenk a MASK-ban megadottal.<br>
	A MASK haszn�lat�nak nagy el�nye, hogy a k�pr�l csak a l�nyeges elemeket m�soljuk �t, �s a keretet pedig nem, �gy nem romboljuk az eredeti h�tteret.<br>
	�rdemes a k�pek egy jellegzetes keretet adni (pl: ship k�pnek z�ld)<br>
	Lass� lehet, mert mind kirajzol�skor be kell olvasni a f�jlb�l a k�pet!
	Gyorsabb a DrawPic()
	
	\include drawxmask_00.c
*/
void DrawBmpMask(char *filename,int x,int y,Uint32 mask)
{
    SDL_Surface *image=SDL_LoadBMP(filename);   // betolti a bmp az image surfacere
    DrawPicMask(image,x,y,mask);
	SDL_FreeSurface(image);
}

/** \brief Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�pet a megadott MASK-al
	\param image 	az sdl felsz�n neve ahol k�pet t�roljuk pl: elefant,pic0 ...
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\param mask	Azoknak a k�ppontoknak a sz�ne, melyet a m�sol�skor nem vesz figyelembe
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazol egy bmp f�jlban l�v� k�pet, de csak azokat a k�ppontokat, melyek sz�nei nem egyezenk a MASK-ban megadottal.<br>
	A MASK haszn�lat�nak nagy el�nye, hogy a k�pr�l csak a l�nyeges elemeket m�soljuk �t, �s a keretet pedig nem, �gy nem romboljuk az eredeti h�tteret.<br>
	�rdemes a k�pek egy jellegzetes keretet adni (pl: ship k�pnek z�ld)<br>
	A k�rnyezet tartalmaz 5 alapvet� k�pet: pic0,pic1,pic2,pic3,pic4<br>
	az SDL_LoadBmp() f�ggv�nnyel mi is csin�lhatunk saj�tot.
	
	\include drawxmask_00.c
*/
void DrawPicMask(SDL_Surface *image,int x,int y,Uint32 mask)
{
SDL_Rect r;                                 // negyzet, hogy hova majd az alap
r.x=x;                                     // screen en a kepet
r.y=y;

MaskPic(image,mask);

SDL_BlitSurface(image,  // a kep surface pointere
                NULL,   // negyzet ha a kepbol akarnank kivagni reszeket
                        // mivell NULL ezert az egesz kep jon
                screen, // ahova akarjuk screen az alapfelulet
                &r      // ahova az alapfeluleten akarjuk tenni a kepet
                );
SDL_UpdateRect(screen,x,y,image->w,image->h);
//SDL_Flip(screen);
}

/** \brief Adott xy koordin�tkra kirjazolja egy bmp f�jlban l�v� k�p egy r�szlet�t
	\param filename a bmp f�jl el�r�si �tja, pl: "c:\\csoki.bmp"
	\param dstx	a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten - destination x
	\param dsty	a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten - destination y
	\param srcx	a kiv�gand� k�pr�szlet bal fels� sark�nak x koordin�t�ja a k�pen - source x
	\param srcy	a kiv�gand� k�pr�szlet bal fels� sark�nak y koordin�t�ja a k�pen - source y
	\param w		a kiv�gand� k�pr�szlet sz�less�ge
	\param h		a kiv�gand� k�pr�szlet magass�ga
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazolja egy bmp f�jlban l�v� k�p egy r�szlet�t<br>
	Azt, hogy melyik r�szlet�t az scrx,srcy,w,h adatok d�ntik el.<br>
	Lehets�ges p�ld�ul, ikonokat egy nagyobb f�jlba betenni, �s onnan kiv�gni mindig a megfelel�t!<br>
	Lass� lehet, mert mind kirajzol�skor be kell olvasni a f�jlb�l a k�pet! 

	
	\see DrawPicPos()
*/
void DrawBmpPos(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h)
{
    SDL_Surface *image=SDL_LoadBMP(filename);
    DrawPicPos(image,dstx,dsty,srcx,srcy,w,h);
	SDL_FreeSurface(image);

}

/** \brief Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�p r�szletet
	\param image 	az sdl felsz�n neve ahol k�pet t�roljuk pl: elefant,pic0 ...
	\param dstx	a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten - destination x
	\param dsty	a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten - destination y
	\param srcx	a kiv�gand� k�pr�szlet bal fels� sark�nak x koordin�t�ja a k�pen - source x
	\param srcy	a kiv�gand� k�pr�szlet bal fels� sark�nak y koordin�t�ja a k�pen - source y
	\param w		a kiv�gand� k�pr�szlet sz�less�ge
	\param h		a kiv�gand� k�pr�szlet magass�ga
	\ingroup PICTURE

	Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�p r�szletet.<br>
	Azt, hogy melyik r�szlet�t az scrx,srcy,w,h adatok d�ntik el.<br>
	Lehets�ges p�ld�ul, ikonokat egy nagyobb f�jlba betenni, �s onnan kiv�gni mindig a megfelel�t!<br>
	
	\include drawxposmask_00.c
*/
void DrawPicPos(SDL_Surface *image,int dstx,int dsty,int srcx,int srcy,int w,int h)
{
SDL_Rect dst,src;                                 // negyzet, hogy hova majd az alap
dst.x=dstx;                                     // screen en a kepet
dst.y=dsty;

src.x=srcx;
src.y=srcy;
src.w=w;
src.h=h;

SDL_BlitSurface(image,  // a kep surface pointere
                &src,   // negyzet ha a kepbol akarnank kivagni reszeket
                        // mivell NULL ezert az egesz kep jon
                screen, // ahova akarjuk screen az alapfelulet
                &dst      // ahova az alapfeluleten akarjuk tenni a kepet
                );

SDL_UpdateRect(screen,dstx,dsty,dstx+w,dsty+h);
//SDL_Flip(screen);
}

/** \brief Adott xy koordin�tkra kirjazolja egy bmp f�jlban l�v� k�p egy r�szlet�t maszkolva
	\param  filename	a bmp f�jl el�r�si �tja, pl: "c:\\csoki.bmp"
	\param dstx	a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten - destination x
	\param dsty	a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten - destination y
	\param srcx	a kiv�gand� k�pr�szlet bal fels� sark�nak x koordin�t�ja a k�pen - source x
	\param srcy	a kiv�gand� k�pr�szlet bal fels� sark�nak y koordin�t�ja a k�pen - source y
	\param w		a kiv�gand� k�pr�szlet sz�less�ge
	\param h		a kiv�gand� k�pr�szlet magass�ga
	\param mask	a maszk sz�ne
	\ingroup PICTURE
	
	\see DrawBmpMask()
	\see DrawBmpPos()

	Adott xy koordin�tkra kirjazolja egy bmp f�jlban l�v� k�p egy r�szlet�t maszkolva<br>
	Azt, hogy melyik r�szlet�t az scrx,srcy,w,h adatok d�ntik el.<br>
	Lehets�ges p�ld�ul, ikonokat egy nagyobb f�jlba betenni, �s onnan kiv�gni mindig a megfelel�t!<br>
	Lass� lehet, mert mind kirajzol�skor be kell olvasni a f�jlb�l a k�pet! 

*/
void DrawBmpPosMask(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h, Uint32 mask)
{
    SDL_Surface *image=SDL_LoadBMP(filename);
    DrawPicPosMask(image,dstx,dsty,srcx,srcy,w,h,mask);
	SDL_FreeSurface(image);

}


/** \brief Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�p r�szletet, maszkolva
	\param image 	az sdl felsz�n neve ahol k�pet t�roljuk pl: elefant,pic0 ...
	\param dstx	a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten - destination x
	\param dsty	a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten - destination y
	\param srcx	a kiv�gand� k�pr�szlet bal fels� sark�nak x koordin�t�ja a k�pen - source x
	\param srcy	a kiv�gand� k�pr�szlet bal fels� sark�nak y koordin�t�ja a k�pen - source y
	\param w		a kiv�gand� k�pr�szlet sz�less�ge
	\param h		a kiv�gand� k�pr�szlet magass�ga
	\param mask	a maszk sz�ne
	\ingroup PICTURE

	\see DrawPicMask()
	\see DrawPicPos()
	
	Adott xy koordin�tkra kirjazol egy SDL felsz�nben t�rolt k�p r�szletet, maszkolva.<br>
	Azt, hogy melyik r�szlet�t az scrx,srcy,w,h adatok d�ntik el.<br>
	Lehets�ges p�ld�ul, ikonokat egy nagyobb f�jlba betenni, �s onnan kiv�gni mindig a megfelel�t!<br>
	
	\include drawxposmask_00.c
	
*/
void DrawPicPosMask(SDL_Surface *image,int dstx,int dsty,int srcx,int srcy,int w,int h,Uint32 mask)
{
MaskPic(image,mask);

SDL_Rect dst,src;                                 // negyzet, hogy hova majd az alap
dst.x=dstx;                                     // screen en a kepet
dst.y=dsty;

src.x=srcx;
src.y=srcy;
src.w=w;
src.h=h;

SDL_BlitSurface(image,  // a kep surface pointere
                &src,   // negyzet ha a kepbol akarnank kivagni reszeket
                        // mivell NULL ezert az egesz kep jon
                screen, // ahova akarjuk screen az alapfelulet
                &dst      // ahova az alapfeluleten akarjuk tenni a kepet
                );
				
SDL_UpdateRect(screen,dstx,dsty,dstx+w,dsty+h);
//SDL_Flip(screen);
}


/** \brief In�cializ�lja az alap�rtelmezett k�peket
	
	In�cializ�lja az alap�rtelmezett k�peket.
*/
void ksdl_bmpinit()
{
char str_base[200];

strcpy(str_base,PATH);
strcat(str_base,"\\picture\\ship.bmp");
pic0=SDL_LoadBMP(str_base);

strcpy(str_base,PATH);
strcat(str_base,"\\picture\\ufo.bmp");
pic1=SDL_LoadBMP(str_base);

strcpy(str_base,PATH);
strcat(str_base,"\\picture\\sun.bmp");
pic2=SDL_LoadBMP(str_base);

strcpy(str_base,PATH);
strcat(str_base,"\\picture\\garfield.bmp");
pic3=SDL_LoadBMP(str_base);

strcpy(str_base,PATH);
strcat(str_base,"\\picture\\elefant.bmp");
pic4=SDL_LoadBMP(str_base);

//pic4=SDL_LoadBMP("c:\\mingw\\data\\picture\\elefant.bmp");


ship=pic0;
ufo=pic1;
sun=pic2;
garfield=pic3;
elefant=pic4;
}

/** \brief K�pek maszkol�sa
	\param screen a maszkoland� k�p
	\param colorkey	a maszk sz�ne, haszn�lhattok konstansokat is!  \ref COLORS
	
	Ha egy k�pet ilyen m�don maszkolunk akkor m�r a mezei DrawPic is maszkolva fogja kirjazolni.
*/
void MaskPic(SDL_Surface *screen,Uint32 colorkey)
{

   // Uint32 colorkey = SDL_MapRGB(screen->format,0,255,0);
    // a maszkot felhelyezem az felszinre
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}


/** \brief K�pek maszkol�sa
	\param screen a maszkoland� k�p
	\param R	az �j maszk PIROS �sszetev�je
	\param G	az �j maszk Z�LD �sszetev�je
	\param B	az �j maszk K�K �sszetev�je
	\ingroup PICTURE
	
	Ha egy k�pet ilyen m�don maszkolunk akkor m�r a mezei DrawPic is maszkolva fogja kirjazolni.
	
	\include setmask_00.c
*/
void SetPictureMask_rgb(SDL_Surface *screen,int R, int G, int B)
{
    // a kivant maszkot beteszem egy valtozoba
    Uint32 colorkey = SDL_MapRGB(screen->format,R,G,B);
    // a maszkot felhelyezem az felszinre
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}

/** \brief K�pek maszkol�sa
	\param screen a maszkoland� k�p
	\param colorkey	a maszk sz�ne, haszn�lhattok konstansokat is!  \ref COLORS
	\ingroup PICTURE
	
	Ha egy k�pet ilyen m�don maszkolunk akkor m�r a mezei DrawPic is maszkolva fogja kirjazolni.
	\include setmask_00.c
*/
void SetPictureMask(SDL_Surface *screen, Uint32 colorkey)
{
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}


/** \brief A k�pet m�sol az alapl�perny�re, de nem friss�ti a megjelen�t�st!
	\param image 	a bem�solni k�v�nt k�p-felsz�n neve (elefant, ship, hatter)
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten

	\ingroup PICTURE

	Ez f�ggv�ny nagyon hasonl�t a DrawPic-re csak itt nem friss�l az alapk�perny�!
	Ez az�rt fontos, mert ha friss�lne azonnal akkor egy anim�ci�n�l a k�p bevilloghat.
	Term�szetesen ha k�sz a teljes kirjazol�s ezek ut�n nek�nk kell friss�teni a k�perny�t
	SDL_Flip(screen) vagy SDL_UpdateRect() f�ggv�nyekkel.

*/
void paste(SDL_Surface *image,int x,int y)
{
SDL_Rect r;                                 // negyzet, hogy hova majd az alap
r.x=x;                                     // screen en a kepet
r.y=y;
r.w=image->w;
r.h=image->h;
SDL_BlitSurface(image,  // a kep surface pointere
                NULL,   // negyzet ha a kepbol akarnank kivagni reszeket
                        // mivell NULL ezert az egesz kep jon
                screen, // ahova akarjuk screen az alapfelulet
                &r      // ahova az alapfeluleten akarjuk tenni a kepet
                );


//SDL_UpdateRect(screen,x,y,image->w,image->h);

}

/** \brief A k�perny�r�l kiv�g egy r�szletet �s azt egy SDL felsz�nre (mintha egy k�p lenne) helyezi
	\param x		a k�p bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a k�p bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\param w		a kiv�gand� k�p sz�less�ge
	\param h		a kiv�gand� k�p magass�ga
	\return	az elk�sz�tett c�m�vel t�r vissza
	\ingroup PICTURE

	A kiv�gott ter�letnek l�trehoz egy SDL felsz�nt, majd �tm�solja a k�pet,
	v�g�l k�p c�m�vel tr� vissza!
	Olyan esetben haszn�latos, ha el akarom menteni valminek a h�tter�t:<br>
	egy �rhaj�t kirajzolok, akkor ha arr�b mozgatom ott marad a csillagos �gen,
	ez�rt el kell mentenem az els� kirajzol�s el�tt, a h�tteret, �s amikor az �rhaj� arr�bb ment
	akkor az elmentett h�tteret visszam�solom a hely�re. DrawPic-el vagy paste-el.
	
	\code 
		SDL_Surface *hatter;
		hatter=cut(100,100,50,50);
		DrawPic(hatter,200,200); 
	\endcode

*/
SDL_Surface* cut(int x,int y,int w,int h)
{

        SDL_Surface *image;
        SDL_Rect r;
        r.x=x;
        r.y=y;
        r.w=w;
        r.h=h;

        image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
            0x000000ff,  0x0000ff00, 0x00ff0000,  0x00000000);

        SDL_BlitSurface(screen,&r,image,NULL);

        return image;
}

/** \brief Ter�let vill�z�smentes mozgat�sa a k�perny�n - NEM k�telez� anyag, neh�z!
	\param x		x koord ahonnan mozgatjuk (ide vissza kell �ll�tani a h�tteret)
	\param y		y koord ahonnan mozgatjuk (ide vissza kell �ll�tani a h�tteret)
	\param dx		ahova az image-t be kell illeszteni
	\param dy		ahova az image-t be kell illeszteni
	\param background	az el�z�leg elmetett h�tt�k�p melyet vissza akarunk m�solni x,y -ra
	\param image		a dx,dy ra bem�soland� k�ppet kell megadni (maszkolt k�p pl: sip, ufo)
	\return	az elmetett h�tt� felsz�n�vel t�r vissza
	\ingroup PICTURE

	Ez egy bonyolult �s neh�z f�ggv�ny!

*/
SDL_Surface* move(int x, int y, int dx, int dy, SDL_Surface* background, SDL_Surface *image)
{
SDL_Rect rect[2];
SDL_Surface *newbck;
    paste(background,x,y);
//ksdl_getch();
newbck=cut(dx,dy,image->w,image->h);
//ksdl_getch();
    paste(image,dx,dy);
//ksdl_getch();
rect[1].x=dx;
rect[1].y=dy;
rect[1].h=image->w;
rect[1].w=image->h;


rect[0].x=x;
rect[0].y=y;
rect[0].h=background->w;
rect[0].w=background->h;

SDL_UpdateRects(screen,2,rect);
SDL_FreeSurface(background);
return newbck;
}

