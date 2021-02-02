/** \file font.h
	\brief  A bmp fontkészlet kezelését támogató függvények.
	\author gergõ

	A bmp fontkészlet kezelését támogató függvények.
*/

/** \brief Egy betükészlet tulajdonságait leíró struktúra*/
typedef struct
{
	/** \brief A felszin változója amellyen a betübmp van*/
    SDL_Surface *font;  
	/** \brief A teljes betükészlet szélessége*/
    int w;
	/** \brief A teljes betükészlet magassága*/
	int h;            
	/** \brief Egy betü szélessége*/
    int charw;
	/** \brief Egy betü magassága*/
	int charh;    // egy karakterhez tartozo magassag es szelesseg
	/** \brief A betük közötti vízszintes távoság távolság*/
    int between_char_x;
	/** \brief A betük közötti függõleges távoság távolság*/
	int between_char_y; // betuk kozotti tavolsag stringek
                                        // kiirasa eseten
    /** \brief NEM használatos méret*/
	int size;           // !! nem hasznalatos - betumeret feltoltese
    /** \brief A betükészlet elérési útja*/
	char path_and_name[200];    // fajl neve es eleresi utja
	/** \brief A  betükészlet elõtérszíne*/
    Uint32 bkgcol;
	/** \brief A  betükészlet háttérszíne*/
	Uint32 fgcol;        // eloterszin es haterszin MapRGB()-vel kodolva

} FONT;

/** \brief Alapértelmezett betü mutatója.
	
	Ez nem egy konkrét betükészletet takar, hanem ezt a mutatót mindig át kell irányítani a
	egy másik készletre onnatól kezdve az a betü lesz az alalpértelmezett betükészlet, tehát azzal fogunk írni.
	\see ChangeFont()
*/
FONT *basefont;
/**	\brief A legkisebb betukészlet mutatója
*/
FONT *font0;
/**	\brief A betukészlet mutató
*/
FONT *font1;
/**	\brief A betukészlet mutató
*/
FONT *font2;
/**	\brief A betukészlet mutató
*/
FONT *font3;
/**	\brief A betukészlet mutató
*/
FONT *font4;




void InitFont(char *filename);
void DrawChar(int x, int y,char c);
void DrawString(int x, int y, char *str);


void set_fontcolor_rgb(int R,int G,int B);
void set_fontcolor(Uint32 newcol);



SDL_Surface* OpenFont_Transparent(char * filename);

void mask_surface_rgb(SDL_Surface *screen,int R,int G,int B);
void mask_surface(SDL_Surface *screen,Uint32 col);
FONT *initfont(char * filename);
void ChangeFont(FONT *font);

/** \brief Megváltoztatja az alapértelmezett betükészletet
	\param font Az új alapértelmezett betükészlet neve(font0,font1 ...)
	\ingroup FONT

	A függvény nem csinál mást mint a *basefont mutatót a átirányítja a paraméterként megadott fontkészletre.<br>
	\include changefont_00.c
*/
void ChangeFont(FONT *font)
{
basefont=font;
}

/** \brief Új fonkészletet lehet fájlból beemelni.
	\param filename	az új fontkészlet fájl neve és elérési útja
	\ingroup FONT

	Mindenki elkészítheti saját fontkészletét, erre vannak külön programok melyek segítenek. 
	Én ezt használtam:  http://www.lmnopc.com/bitmapfontbuilder/.
	
	\include initfont_00.c
	

*/
FONT *initfont(char * filename)
{
        //DrawBmp(filename,111,111);
        FONT *bf;
        bf=(FONT *)malloc(sizeof(FONT));
        // betesszuk a file nevet es eleresi utjat a strukturaba

        strcpy(bf->path_and_name, filename);

        // a font felszinbe betesszuk a hivatkozott bmp-t
        bf->font      =OpenFont_Transparent(filename);

        // alap betumeret, a bmp fajlban rogyitve van
        bf->size      =0;

        // a font struktura tudja, hogy  milyen szeles es magas
        // a kep
        bf->w         =bf->font->w;
        bf->h         =bf->font->h;

        // az alapertelmezett eloterszin a feher
        bf->fgcol     =SDL_MapRGB(bf->font->format,255,255,255);
        // az alapertelmezett hatterszin a fekete
        bf->bkgcol    =SDL_MapRGB(bf->font->format,0,0,0);

        // meghatarozzuk egy betu magassagat es szelesseget
        // abbo  kiindulva, hogy a 256 betu egy 16x16-os
        // negyzetben helyezkedik el
        bf->charw     =bf->w/16;
        bf->charh     =bf->h/16;

        bf->between_char_y    = bf->h/16;
        bf->between_char_x    = bf->w/16;

        return bf;
}


/** \brief Az aktuális fontkészletet átszinezi.
	\param R	az új betüszín PIROS összetevõje
	\param G	az új betüszín ZÖLD összetevõje
	\param B	az új betüszín KÉK összetevõje
	\ingroup FONT

	Az aktuális fongkészletet átszínezi.<br>
	Fontos: ha betükészletet váltunk akkor a szín is változik!
	
	\include	setfontcolor_00.c
*/
void set_fontcolor_rgb(int R,int G,int B)
{
    Uint32 newcol=SDL_MapRGB(basefont->font->format,R,G,B);
    set_fontcolor(newcol);
}

/** \brief Az aktuális fontkészletet átszinezi.
	\param newcol	Az új betüszín változója, ide írhattok konstanst is! \ref COLORS
	\ingroup FONT

	Az aktuális fongkészletet átszínezi.<br>
	Fontos: ha betükészletet váltunk akkor a szín is változik!
	
	\include	setfontcolor_00.c
*/
void set_fontcolor(Uint32 newcol)
{
    int i=0,j=0;


    if(newcol == basefont->fgcol) return;

    if(newcol == basefont->bkgcol)  // ha a hatterszinre akarjuk megvaltoztatni
                                    // az eloterszint akkor meg kell valztoztatni a
                                    // maszkot
        {
            // ebben a ciklusban a hatterszint inkrementalom
            for(;i<(basefont->w*basefont->h)-1;i++)
            {
                if(((Uint32 *)basefont->font->pixels)[i]==basefont->bkgcol)
                {
                    ((Uint32 *)basefont->font->pixels)[i]++;
                }
            }

            // a strukturaban is atirom a hatterszint
            basefont->bkgcol++;
            // az uj hatterszinhez beallitom az uj maszkot
            mask_surface(basefont->font,basefont->bkgcol);

        }

    for(i=0;i<(basefont->w*basefont->h)-1;i++)
    {

        if(((Uint32 *)basefont->font->pixels)[i]!=basefont->bkgcol)
        {
            j++;
            ((Uint32 *)basefont->font->pixels)[i]=newcol;
        }

    }
    basefont->fgcol=newcol;
}

/** \brief Nem kell használni, betükészletek maszkolásáért felelõs függvény!
	\param filename a betöltendõ fontbmp elérési útja

	Belsõ függvény nem kell a hallgatókank használni!
	Az initfont hívja!
	\see initfont()
	

*/
SDL_Surface* OpenFont_Transparent(char *filename)
{
    // ebben a fvben betoltunk egy kepet, majd atmasoljuk egy masik
    // felszinre, melynek beallitunk egy maszkot. Ha a jovoben
    // errol a felszinrol masolunk a maszkal keppontjait nem fogja
    // masolni a rendszer. Igy vaghatjuk le a hatteret a betukrol
    // es egyeb sprite -okrol

    // betoltom az eredeti kepet
    SDL_Surface *original=SDL_LoadBMP(filename);
    // letrehozom az uj felszint
    SDL_Surface *optimized=NULL;
    // atmasolom
    optimized   =   SDL_DisplayFormat(original);
    // felszabaditom az eredeti felszint
    SDL_FreeSurface(original);
    // a kivant maszkot beteszem egy valtozoba

    mask_surface_rgb(optimized,0,0,0);

//    Uint32 colorkey = SDL_MapRGB(optimized->format,0,0,0);
    // a maszkot felhelyezem az felszinre
//    SDL_SetColorKey(optimized,SDL_SRCCOLORKEY,colorkey);
    //visszaterek a felszin mutatojaval
    return optimized;
}

/** \brief Nem kell használni,  maszkolásért felelõs függvény!
	\param screen a maszkolandó felület
	\param R	az új maszk PIROS összetevõje
	\param G	az új maszk ZÖLD összetevõje
	\param B	az új maszk KÉK összetevõje
	
	Belsõ függvény nem kell a hallgatókank használni!
	
	\see OpenFont_Transparent()	
	\see set_fontcolor()
	\see set_fontcolor_rgb()	

*/
void mask_surface_rgb(SDL_Surface *screen,int R,int G,int B)
{
    // a kivant maszkot beteszem egy valtozoba
    Uint32 colorkey = SDL_MapRGB(screen->format,0,0,0);
    // a maszkot felhelyezem az felszinre
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);
}


/** \brief Nem kell használni,  maszkolásért felelõs függvény!
	\param screen	a maszkolandó felület
	\param colorkey	az új háttérszín, használhattok konstansokat is! \ref COLORS
	
	Belsõ függvény nem kell a hallgatókank használni!
	\see OpenFont_Transparent()	
	\see set_fontcolor()
	\see set_fontcolor_rgb()

	

*/
void mask_surface(SDL_Surface *screen,Uint32 colorkey)
{
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);

}

/** \brief Kirajzol egy sztringet a képernyõre
	\param x	Az elsõ betü bal felsõ sarkának x koordinátája
	\param y	Az elsõ betü bal felsõ sarkának y koordinátája 
	\param str	A kiírandó sztring
	\ingroup FONT

	A függvény karakterenként kiírja a stringet, addig ameddig a sztringzáró 0-t meg nem találja.
	Végül frissíti az egész képernyõt.
	
	\include	dstring_00.c
*/
void DrawString(int x, int y, char *str)
{
    int i=0;
    for(;str[i]!=0;i++)
    {
        DrawChar(x+i*basefont->between_char_x,y,str[i]);
    }
SDL_Flip(screen);
}

/** \brief Kirajzol egy karaktert a képernyõre
	\param x	Az elsõ betü bal felsõ sarkának x koordinátája
	\param y	Az elsõ betü bal felsõ sarkának y koordinátája 
	\param c	A kiirandó betü ASCII kódja.
	\ingroup FONT
	
	\include	dchar_00.c

*/
void DrawChar(int x,int y, char c)
{
    int cx,cy;


    //=c%16*16;
    cx=(c%basefont->charh)*basefont->charh; // az oszlop kezdokoordinataja
    cy=(c/basefont->charh)*basefont->charh; // a sor kezdokoordinataja

    SDL_Rect src,dst;
    src.x=cx;
    src.y=cy+1;
    src.w=basefont->charw;
    src.h=basefont->charh+1;
    dst.x=x;
    dst.y=y;

    SDL_BlitSurface(basefont->font,&src,screen,&dst);
	if(cx+src.w > screen->w || cy+src.y > screen->h)
		SDL_Flip(screen);
	else
		SDL_UpdateRect(screen, cx, cy, (int)src.w, (int)src.h);
	
}




