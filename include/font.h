/** \file font.h
	\brief  A bmp fontk�szlet kezel�s�t t�mogat� f�ggv�nyek.
	\author gerg�

	A bmp fontk�szlet kezel�s�t t�mogat� f�ggv�nyek.
*/

/** \brief Egy bet�k�szlet tulajdons�gait le�r� strukt�ra*/
typedef struct
{
	/** \brief A felszin v�ltoz�ja amellyen a bet�bmp van*/
    SDL_Surface *font;  
	/** \brief A teljes bet�k�szlet sz�less�ge*/
    int w;
	/** \brief A teljes bet�k�szlet magass�ga*/
	int h;            
	/** \brief Egy bet� sz�less�ge*/
    int charw;
	/** \brief Egy bet� magass�ga*/
	int charh;    // egy karakterhez tartozo magassag es szelesseg
	/** \brief A bet�k k�z�tti v�zszintes t�vos�g t�vols�g*/
    int between_char_x;
	/** \brief A bet�k k�z�tti f�gg�leges t�vos�g t�vols�g*/
	int between_char_y; // betuk kozotti tavolsag stringek
                                        // kiirasa eseten
    /** \brief NEM haszn�latos m�ret*/
	int size;           // !! nem hasznalatos - betumeret feltoltese
    /** \brief A bet�k�szlet el�r�si �tja*/
	char path_and_name[200];    // fajl neve es eleresi utja
	/** \brief A  bet�k�szlet el�t�rsz�ne*/
    Uint32 bkgcol;
	/** \brief A  bet�k�szlet h�tt�rsz�ne*/
	Uint32 fgcol;        // eloterszin es haterszin MapRGB()-vel kodolva

} FONT;

/** \brief Alap�rtelmezett bet� mutat�ja.
	
	Ez nem egy konkr�t bet�k�szletet takar, hanem ezt a mutat�t mindig �t kell ir�ny�tani a
	egy m�sik k�szletre onnat�l kezdve az a bet� lesz az alalp�rtelmezett bet�k�szlet, teh�t azzal fogunk �rni.
	\see ChangeFont()
*/
FONT *basefont;
/**	\brief A legkisebb betuk�szlet mutat�ja
*/
FONT *font0;
/**	\brief A betuk�szlet mutat�
*/
FONT *font1;
/**	\brief A betuk�szlet mutat�
*/
FONT *font2;
/**	\brief A betuk�szlet mutat�
*/
FONT *font3;
/**	\brief A betuk�szlet mutat�
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

/** \brief Megv�ltoztatja az alap�rtelmezett bet�k�szletet
	\param font Az �j alap�rtelmezett bet�k�szlet neve(font0,font1 ...)
	\ingroup FONT

	A f�ggv�ny nem csin�l m�st mint a *basefont mutat�t a �tir�ny�tja a param�terk�nt megadott fontk�szletre.<br>
	\include changefont_00.c
*/
void ChangeFont(FONT *font)
{
basefont=font;
}

/** \brief �j fonk�szletet lehet f�jlb�l beemelni.
	\param filename	az �j fontk�szlet f�jl neve �s el�r�si �tja
	\ingroup FONT

	Mindenki elk�sz�theti saj�t fontk�szlet�t, erre vannak k�l�n programok melyek seg�tenek. 
	�n ezt haszn�ltam:  http://www.lmnopc.com/bitmapfontbuilder/.
	
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


/** \brief Az aktu�lis fontk�szletet �tszinezi.
	\param R	az �j bet�sz�n PIROS �sszetev�je
	\param G	az �j bet�sz�n Z�LD �sszetev�je
	\param B	az �j bet�sz�n K�K �sszetev�je
	\ingroup FONT

	Az aktu�lis fongk�szletet �tsz�nezi.<br>
	Fontos: ha bet�k�szletet v�ltunk akkor a sz�n is v�ltozik!
	
	\include	setfontcolor_00.c
*/
void set_fontcolor_rgb(int R,int G,int B)
{
    Uint32 newcol=SDL_MapRGB(basefont->font->format,R,G,B);
    set_fontcolor(newcol);
}

/** \brief Az aktu�lis fontk�szletet �tszinezi.
	\param newcol	Az �j bet�sz�n v�ltoz�ja, ide �rhattok konstanst is! \ref COLORS
	\ingroup FONT

	Az aktu�lis fongk�szletet �tsz�nezi.<br>
	Fontos: ha bet�k�szletet v�ltunk akkor a sz�n is v�ltozik!
	
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

/** \brief Nem kell haszn�lni, bet�k�szletek maszkol�s��rt felel�s f�ggv�ny!
	\param filename a bet�ltend� fontbmp el�r�si �tja

	Bels� f�ggv�ny nem kell a hallgat�kank haszn�lni!
	Az initfont h�vja!
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

/** \brief Nem kell haszn�lni,  maszkol�s�rt felel�s f�ggv�ny!
	\param screen a maszkoland� fel�let
	\param R	az �j maszk PIROS �sszetev�je
	\param G	az �j maszk Z�LD �sszetev�je
	\param B	az �j maszk K�K �sszetev�je
	
	Bels� f�ggv�ny nem kell a hallgat�kank haszn�lni!
	
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


/** \brief Nem kell haszn�lni,  maszkol�s�rt felel�s f�ggv�ny!
	\param screen	a maszkoland� fel�let
	\param colorkey	az �j h�tt�rsz�n, haszn�lhattok konstansokat is! \ref COLORS
	
	Bels� f�ggv�ny nem kell a hallgat�kank haszn�lni!
	\see OpenFont_Transparent()	
	\see set_fontcolor()
	\see set_fontcolor_rgb()

	

*/
void mask_surface(SDL_Surface *screen,Uint32 colorkey)
{
    SDL_SetColorKey(screen,SDL_SRCCOLORKEY,colorkey);

}

/** \brief Kirajzol egy sztringet a k�perny�re
	\param x	Az els� bet� bal fels� sark�nak x koordin�t�ja
	\param y	Az els� bet� bal fels� sark�nak y koordin�t�ja 
	\param str	A ki�rand� sztring
	\ingroup FONT

	A f�ggv�ny karakterenk�nt ki�rja a stringet, addig ameddig a sztringz�r� 0-t meg nem tal�lja.
	V�g�l friss�ti az eg�sz k�perny�t.
	
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

/** \brief Kirajzol egy karaktert a k�perny�re
	\param x	Az els� bet� bal fels� sark�nak x koordin�t�ja
	\param y	Az els� bet� bal fels� sark�nak y koordin�t�ja 
	\param c	A kiirand� bet� ASCII k�dja.
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




