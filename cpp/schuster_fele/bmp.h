/** \file bmp.h
	\brief  A bmp képek kezelést megvalósító függvények
	\author gergõ

	A bmp képek kezelést megvalósító függvények
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


/** \brief Adott xy koordinátkra kirjazol egy bmp fájlban lévõ képet
	\param filename a bmp fájl elérési útja, pl: "c:\\csoki.bmp"
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\ingroup PICTURE

	Adott xy koordinátkra kirjazol egy bmp fájlban lévõ képet.
	Lassú lehet, mert mind kirajzoláskor be kell olvasni a fájlból a képet!
	Gyorsabb a DrawPic()
	
	\include drawx_01.c
*/
void DrawBmp(char *filename,int x,int y)
{
SDL_Surface *image=SDL_LoadBMP(filename);   // betolti a bmp az image surfacere
DrawPic(image,x,y);
SDL_FreeSurface(image);
}

/** \brief Adott xy koordinátkra kirjazol egy SDL felszínben tárolt képet
	\param image 	az sdl felszín neve ahol képet tároljuk pl: elefant,pic0 ...
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\ingroup PICTURE

	Adott xy koordinátkra kirjazol egy SDL felszínben tárolt képet, mivel ez a memóriában tárolódik sokkal gyorsabban elérhetõ
	és kirajzolható.
	A környezet tartalmaz 5 alapvetõ képet: pic0,pic1,pic2,pic3,pic4,<br>
	az SDL_LoadBmp() függvénnyel mi is csinálhatunk sajátot.
	
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

/** \brief Adott xy koordinátkra kirjazol egy bmp fájlban lévõ képet a megadott MASK-al
	\param filename a bmp fájl elérési útja, pl: "c:\\csoki.bmp"
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\param mask	Azoknak a képpontoknak a színe, melyet a másoláskor nem vesz figyelembe
	\ingroup PICTURE

	Adott xy koordinátkra kirjazol egy bmp fájlban lévõ képet, de csak azokat a képpontokat, melyek színei nem egyezenk a MASK-ban megadottal.<br>
	A MASK használatának nagy elõnye, hogy a képrõl csak a lényeges elemeket másoljuk át, és a keretet pedig nem, így nem romboljuk az eredeti hátteret.<br>
	Érdemes a képek egy jellegzetes keretet adni (pl: ship képnek zöld)<br>
	Lassú lehet, mert mind kirajzoláskor be kell olvasni a fájlból a képet!
	Gyorsabb a DrawPic()
	
	\include drawxmask_00.c
*/
void DrawBmpMask(char *filename,int x,int y,Uint32 mask)
{
    SDL_Surface *image=SDL_LoadBMP(filename);   // betolti a bmp az image surfacere
    DrawPicMask(image,x,y,mask);
	SDL_FreeSurface(image);
}

/** \brief Adott xy koordinátkra kirjazol egy SDL felszínben tárolt képet a megadott MASK-al
	\param image 	az sdl felszín neve ahol képet tároljuk pl: elefant,pic0 ...
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\param mask	Azoknak a képpontoknak a színe, melyet a másoláskor nem vesz figyelembe
	\ingroup PICTURE

	Adott xy koordinátkra kirjazol egy bmp fájlban lévõ képet, de csak azokat a képpontokat, melyek színei nem egyezenk a MASK-ban megadottal.<br>
	A MASK használatának nagy elõnye, hogy a képrõl csak a lényeges elemeket másoljuk át, és a keretet pedig nem, így nem romboljuk az eredeti hátteret.<br>
	Érdemes a képek egy jellegzetes keretet adni (pl: ship képnek zöld)<br>
	A környezet tartalmaz 5 alapvetõ képet: pic0,pic1,pic2,pic3,pic4<br>
	az SDL_LoadBmp() függvénnyel mi is csinálhatunk sajátot.
	
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

/** \brief Adott xy koordinátkra kirjazolja egy bmp fájlban lévõ kép egy részletét
	\param filename a bmp fájl elérési útja, pl: "c:\\csoki.bmp"
	\param dstx	a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen - destination x
	\param dsty	a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen - destination y
	\param srcx	a kivágandó képrészlet bal felsõ sarkának x koordinátája a képen - source x
	\param srcy	a kivágandó képrészlet bal felsõ sarkának y koordinátája a képen - source y
	\param w		a kivágandó képrészlet szélessége
	\param h		a kivágandó képrészlet magassága
	\ingroup PICTURE

	Adott xy koordinátkra kirjazolja egy bmp fájlban lévõ kép egy részletét<br>
	Azt, hogy melyik részletét az scrx,srcy,w,h adatok döntik el.<br>
	Lehetséges például, ikonokat egy nagyobb fájlba betenni, és onnan kivágni mindig a megfelelõt!<br>
	Lassú lehet, mert mind kirajzoláskor be kell olvasni a fájlból a képet! 

	
	\see DrawPicPos()
*/
void DrawBmpPos(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h)
{
    SDL_Surface *image=SDL_LoadBMP(filename);
    DrawPicPos(image,dstx,dsty,srcx,srcy,w,h);
	SDL_FreeSurface(image);

}

/** \brief Adott xy koordinátkra kirjazol egy SDL felszínben tárolt kép részletet
	\param image 	az sdl felszín neve ahol képet tároljuk pl: elefant,pic0 ...
	\param dstx	a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen - destination x
	\param dsty	a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen - destination y
	\param srcx	a kivágandó képrészlet bal felsõ sarkának x koordinátája a képen - source x
	\param srcy	a kivágandó képrészlet bal felsõ sarkának y koordinátája a képen - source y
	\param w		a kivágandó képrészlet szélessége
	\param h		a kivágandó képrészlet magassága
	\ingroup PICTURE

	Adott xy koordinátkra kirjazol egy SDL felszínben tárolt kép részletet.<br>
	Azt, hogy melyik részletét az scrx,srcy,w,h adatok döntik el.<br>
	Lehetséges például, ikonokat egy nagyobb fájlba betenni, és onnan kivágni mindig a megfelelõt!<br>
	
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

/** \brief Adott xy koordinátkra kirjazolja egy bmp fájlban lévõ kép egy részletét maszkolva
	\param  filename	a bmp fájl elérési útja, pl: "c:\\csoki.bmp"
	\param dstx	a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen - destination x
	\param dsty	a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen - destination y
	\param srcx	a kivágandó képrészlet bal felsõ sarkának x koordinátája a képen - source x
	\param srcy	a kivágandó képrészlet bal felsõ sarkának y koordinátája a képen - source y
	\param w		a kivágandó képrészlet szélessége
	\param h		a kivágandó képrészlet magassága
	\param mask	a maszk színe
	\ingroup PICTURE
	
	\see DrawBmpMask()
	\see DrawBmpPos()

	Adott xy koordinátkra kirjazolja egy bmp fájlban lévõ kép egy részletét maszkolva<br>
	Azt, hogy melyik részletét az scrx,srcy,w,h adatok döntik el.<br>
	Lehetséges például, ikonokat egy nagyobb fájlba betenni, és onnan kivágni mindig a megfelelõt!<br>
	Lassú lehet, mert mind kirajzoláskor be kell olvasni a fájlból a képet! 

*/
void DrawBmpPosMask(char *filename,int dstx,int dsty,int srcx,int srcy,int w,int h, Uint32 mask)
{
    SDL_Surface *image=SDL_LoadBMP(filename);
    DrawPicPosMask(image,dstx,dsty,srcx,srcy,w,h,mask);
	SDL_FreeSurface(image);

}


/** \brief Adott xy koordinátkra kirjazol egy SDL felszínben tárolt kép részletet, maszkolva
	\param image 	az sdl felszín neve ahol képet tároljuk pl: elefant,pic0 ...
	\param dstx	a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen - destination x
	\param dsty	a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen - destination y
	\param srcx	a kivágandó képrészlet bal felsõ sarkának x koordinátája a képen - source x
	\param srcy	a kivágandó képrészlet bal felsõ sarkának y koordinátája a képen - source y
	\param w		a kivágandó képrészlet szélessége
	\param h		a kivágandó képrészlet magassága
	\param mask	a maszk színe
	\ingroup PICTURE

	\see DrawPicMask()
	\see DrawPicPos()
	
	Adott xy koordinátkra kirjazol egy SDL felszínben tárolt kép részletet, maszkolva.<br>
	Azt, hogy melyik részletét az scrx,srcy,w,h adatok döntik el.<br>
	Lehetséges például, ikonokat egy nagyobb fájlba betenni, és onnan kivágni mindig a megfelelõt!<br>
	
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


/** \brief Inícializálja az alapértelmezett képeket
	
	Inícializálja az alapértelmezett képeket.
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

/** \brief Képek maszkolása
	\param screen a maszkolandó kép
	\param colorkey	a maszk színe, használhattok konstansokat is!  \ref COLORS
	
	Ha egy képet ilyen módon maszkolunk akkor már a mezei DrawPic is maszkolva fogja kirjazolni.
*/
void MaskPic(SDL_Surface *screen,Uint32 colorkey)
{

   // Uint32 colorkey = SDL_MapRGB(screen->format,0,255,0);
    // a maszkot felhelyezem az felszinre
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}


/** \brief Képek maszkolása
	\param screen a maszkolandó kép
	\param R	az új maszk PIROS összetevõje
	\param G	az új maszk ZÖLD összetevõje
	\param B	az új maszk KÉK összetevõje
	\ingroup PICTURE
	
	Ha egy képet ilyen módon maszkolunk akkor már a mezei DrawPic is maszkolva fogja kirjazolni.
	
	\include setmask_00.c
*/
void SetPictureMask_rgb(SDL_Surface *screen,int R, int G, int B)
{
    // a kivant maszkot beteszem egy valtozoba
    Uint32 colorkey = SDL_MapRGB(screen->format,R,G,B);
    // a maszkot felhelyezem az felszinre
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}

/** \brief Képek maszkolása
	\param screen a maszkolandó kép
	\param colorkey	a maszk színe, használhattok konstansokat is!  \ref COLORS
	\ingroup PICTURE
	
	Ha egy képet ilyen módon maszkolunk akkor már a mezei DrawPic is maszkolva fogja kirjazolni.
	\include setmask_00.c
*/
void SetPictureMask(SDL_Surface *screen, Uint32 colorkey)
{
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}


/** \brief A képet másol az alaplépernyõre, de nem frissíti a megjelenítést!
	\param image 	a bemásolni kívánt kép-felszín neve (elefant, ship, hatter)
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen

	\ingroup PICTURE

	Ez függvény nagyon hasonlít a DrawPic-re csak itt nem frissül az alapképernyõ!
	Ez azért fontos, mert ha frissülne azonnal akkor egy animációnál a kép bevilloghat.
	Természetesen ha kész a teljes kirjazolás ezek után nekünk kell frissíteni a képernyõt
	SDL_Flip(screen) vagy SDL_UpdateRect() függvényekkel.

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

/** \brief A képernyõrõl kivág egy részletet és azt egy SDL felszínre (mintha egy kép lenne) helyezi
	\param x		a kép bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a kép bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\param w		a kivágandó kép szélessége
	\param h		a kivágandó kép magassága
	\return	az elkészített címével tér vissza
	\ingroup PICTURE

	A kivágott területnek létrehoz egy SDL felszínt, majd átmásolja a képet,
	végül kép címével tré vissza!
	Olyan esetben használatos, ha el akarom menteni valminek a hátterét:<br>
	egy ûrhajót kirajzolok, akkor ha arréb mozgatom ott marad a csillagos égen,
	ezért el kell mentenem az elsõ kirajzolás elött, a hátteret, és amikor az ûrhajó arrébb ment
	akkor az elmentett hátteret visszamásolom a helyére. DrawPic-el vagy paste-el.
	
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

/** \brief Terület villózásmentes mozgatása a képernyõn - NEM kötelezõ anyag, nehéz!
	\param x		x koord ahonnan mozgatjuk (ide vissza kell állítani a hátteret)
	\param y		y koord ahonnan mozgatjuk (ide vissza kell állítani a hátteret)
	\param dx		ahova az image-t be kell illeszteni
	\param dy		ahova az image-t be kell illeszteni
	\param background	az elõzõleg elmetett háttékép melyet vissza akarunk másolni x,y -ra
	\param image		a dx,dy ra bemásolandó képpet kell megadni (maszkolt kép pl: sip, ufo)
	\return	az elmetett hátté felszínével tér vissza
	\ingroup PICTURE

	Ez egy bonyolult és nehéz függvény!

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

