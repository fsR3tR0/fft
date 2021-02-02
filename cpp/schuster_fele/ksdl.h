/** \file ksdl.h
	\brief  Az  alapvetõ inícilazácós, illetve billetyûzetkezelõ függvényeket tartalmazza.
	\author gergõ

	Ebben a fájlban találhatók a azok a függvények melyek segítségével a <br> 
	fel lehet inícializálni a KSDL-t, illetve az alapvetõ billentyübeolvasásái rutinok kaptak itt helyet<br> 
*/

/**	\defgroup ALAP		ALAP		Az alapvetõ inícilazácós, illetve billetyûzetkezelõ függvényeket tartalmazza.

	\defgroup PICTURE	PICTURE	A képek kezelésével kapcsolatos függvényeket és változókat tartalmazza.

	\defgroup GEOM	GEOM	A geometriai modul alapvetõ rajzolófüggvényeket tartalmaz.

	\defgroup FONT		FONT	A bmpfontkészletek használatát biztosító függvényeket tartalmazza.

	\defgroup COLORS	COLORS	Színek konstansait  találhatjátok itt!
	
	\defgroup	MOUSE	MOUSE		Az egérkezeléshez szükséges függvények és a mouse struktúra.
	
	\defgroup	SDL	SDL		Az SDL függvények leírása (MINDEN ami SDL_ -el kezdõdik)
*/

/** A PI értékét a legegyszerübb így konstansal megadni.
*/
#define PI 3.1415926535897932384626433832795f
#include <math.h>

/**	Alapértelmezett SDL felszín.

	Ez a felszín jelenik meg a képernyõn.
	Majdnem minden KSDL függvény ezt használja rajzolófelületként. 
	Az SDL-ben mi is hozhatunk létre felszíneket, így tudunk rajzolni az egyikre, míg a másikat megjelenítjük, illetve
	az elõre betöltött képek és fontok egy elõre elkészített hasonló felszínben vannak eltárolva.
*/

SDL_Surface *screen;    // Globalis valtozo  (strukturapointer) ennek segitsegevel
                        // lehet elerni a grafikus feluletet

/**	Ebben a struktúrában tárolódik minden egér információ.
	\ingroup MOUSE
	
*/
struct PATKANY{
	/** \brief  Az egér x koordinátája az utolsó lenyomás pillanatában.*/
    int xbut;
	/** \brief  Az egér y koordinátája az utolsó lenyomás pillanatában.*/
	int ybut;
	/** \brief  Az egér x koordinátája az a jelen pillanatban.*/
    int xnow;
	/** \brief  Az egér y koordinátája az a jelen pillanatban.*/
	int ynow;
	/** \brief  Az egér x koordinátájának változása az utolsó lekérdezéshez képest.*/
    int xrel;
	/** \brief  Az egér y koordinátájának változása az utolsó lekérdezéshez képest.*/
	int yrel;
	/** \brief  A lenyomott gomb azonosítója 
	1 - bal 2 - középsõ 3 - jobb<br>
	4 - wheel up 5 - wheel down
	 */
    int button;
	int state;
	int type;
	/** \brief  A lenyomás ideje - a program elindításától  eltelt milisecundomok száma*/
	int time;
	int newevent;
}mouse;



SDL_Event event;
//#include "ttf.h"
//#include "sound.h"
#include "default.h"
#include "font.h"
#include "geom.h"
#include "bmp.h"



int ksdl_init(int w,int h); // sdl inicializalo fuggveny
                                        // int w - width syelesseg pixelben (pl 640)
                                        // int h - height magassag pixelben (pl 480)
int ksdl_init_extra(int w,int h,int FULL,int HWpSW);


int ksdl_fontinit(void);               // betolti a font1..4 be az alapertelmezett fontokat
void waitforkey(void);
char ksdl_getch(void);  
char ksdl_kbhit();
int getpixel(int x,int y);
void getpixel_rgb(int x,int y, int *r, int *g, int *b);
int getbutton();
void getmotion();
//void ksdl_quit();


/** \brief Létrehoz egy ablakot a megadott felbontással
	\param w az ablak szélességét adja meg pixelben
	\param h az ablak magasságát adja meg pixelben
	\return nullával tér vissza ha nem ütközött hibába, egyébként a visszatérési érték 1

	\ingroup ALAP

	Inícializálja a SDL videó szegmensét, majd létrehoz egy w x h méretû 32 bit-es szinmélységû ablakot!<br>
	Extra : szoftveres felületet készít, ami egy kicsit lassúvá teheti rendszert, ugyanakkor minden körülmény között mûködik, ezt azért
	írom le mert a bátrabbak áttehetik HW_SURFACE -is a SetVideomode() függvényt!
	
	\since 5.0 Bekerült egy SDL_EnableKeyRepeat(1,100); függvényhívás, így a folyamatos nyomvatartást úgy érzékeli
	mintha 100 ms-enként leütöttünk volna azt a billentyût.
*/
int ksdl_init(int w,int h)// sdl inicializalo fuggveny
                                        // int w - width syelesseg pixelben (pl 640)
                                        // int h - height magassag pixelben (pl 480)
{
if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(w, h, 32, SDL_SWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Nem tudom beallítani %ix%i felbontast: %s\n",w,h, SDL_GetError());
        return 1;
    }

    SDL_EnableUNICODE(1);

#ifndef SAFEMODE
//   ksdl_fontinit();
//   ksdl_bmpinit();
#endif

   SDL_EnableKeyRepeat(1,100);
	return 0;
}

/** \brief Létrehoz egy ablakot a megadott felbontással, választható hardvers és szoftveres gyorsítás, választható fullscreen mód
	\param w az ablak szélességét adja meg pixelben
	\param h az ablak magasságát adja meg pixelben
	\param FULL ha az értéke nem nulla akkor teljes képernyõs módban indul a program
	\param HWpSW  ha az értéke nem nulla akkor hardveres gyorsítást használ SDL a rajzolásoz
	\return nullával tér vissza ha nem ütközött hibába, egyébként a visszatérési érték 1

	\ingroup ALAP


	Inícializálja a SDL videó szegmensét, majd létrehoz egy w x h méretû 32 bit-es szinmélységû ablakot!<br>
	Beállítható a hardveres gyorsítás és a teljesképoernyõs mód! <br>
	FONTOS - a ksdl_init()  helyett lehet használni (Nem kötelezõ)!!!
	
	\code	ksdl_init_extra(i1024,768,1,1);
	\endcode
	
	\since 0.6
	
	\warning  5.0 Bekerült egy SDL_EnableKeyRepeat(1,100); függvényhívás, így a folyamatos nyomvatartást úgy érzékeli
	mintha 100 ms-enként leütöttünk volna azt a billentyût.
*/
int ksdl_init_extra(int w,int h,int FULL,int HWpSW)
{
int param;
if(HWpSW)
    {
        if(FULL) param=(SDL_FULLSCREEN|SDL_HWSURFACE);
        else     param=(SDL_HWSURFACE);
    }
else
    {
        if(FULL) param=(SDL_FULLSCREEN|SDL_SWSURFACE);
        else     param=(SDL_SWSURFACE);
    }

if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window

    screen = SDL_SetVideoMode(w, h, 32, param);
    if ( !screen )
    {
        printf("Nem tudom beallítani %ix%i felbontast: %s\n",w,h, SDL_GetError());
        return 1;
    }

    SDL_EnableUNICODE(1);

#ifndef SAFEMODE
   ksdl_fontinit();
   ksdl_bmpinit();
#endif
   SDL_EnableKeyRepeat(1,100);
	return 0;
}


/** \brief Lekérdezi egy pixel színét
	\param x a lekérdezett pixel x koordinátája
	\param y a lekérdezett pixel y koordinátája
	\return a kívánt színnel tér vissza, összehasonlítható a COLORS konstansokkal

	\ingroup ALAP

	A függvény segítségével megtudhatjuk, hogy az adott területen milyen színü a pixel!
	
	\since 0.6 
	\include	getpixel_00.c	
*/
int getpixel(int x,int y)
{
   int color;
   if(x>screen->w || x<0 || y>screen->h || y<0) {return 0;}	// ha kilog a kepernyorol akkor nullaval terek vissza

   color = *((Uint32 *)screen->pixels+x+y*screen->w) ;

   return color;
}

/** \brief Lekérdezi egy pixel színét, de rgb összetevõnként.
	\param x a lekérdezett pixel x koordinátája
	\param y a lekérdezett pixel y koordinátája
	\param r annak a változónak a címe amelybe a piros színösszetevõ mértékét szeretnénk tenni (0-256) szám lesz!
	\param g annak a változónak a címe amelybe a zöld színösszetevõ mértékét szeretnénk tenni (0-256) szám lesz!
	\param b annak a változónak a címe amelybe a kék színösszetevõ mértékét szeretnénk tenni (0-256) szám lesz!
	\ingroup ALAP

	A függvény segítségével megtudhatjuk, hogy az adott területen milyen színü a pixel!
	FIGYELEM a függvény címeket vár az utolsó 3 paraméterében (tessék használni a címképzõ & operátort), 
	azért kell címekkel dolgozni mert a függvény csak egy értékkel térhet vissza és nekünk itt 3-ra van szükségünk!
	
	\since 0.6 
	\include	getpixel_rgb_00.c	
*/
void getpixel_rgb(int x,int y, int *r, int *g, int *b)
{
     int color;
   if(x>screen->w || x<0 || y>screen->h || y<0) {return;} // ha kilog a kepernyorol akkor nullaval terek vissza

   color = *((Uint32 *)screen->pixels+x+y*screen->w) ;

   *b=color&0x0000ff;   // a maskolas autan csak a kek marad
   
   *g=(color&0x00ff00)>>8;  // lemaszkolom a kek es a piros szint
                            // csak a zold hagyva, majd az eredmenyt
                            // elshiftelem 8 bittel jobbra, hogy 0-256 kozott legyen

   *r=(color&0xff0000)>>16; // lemaszkolom a kek es a zold szint
                            // csak a pirosat hagyva, majd az eredmenyt
                            // elshiftelem 16 bittel jobbra, hogy 0-256 kozott legyen
   return;
}




/** \brief Megállítja a program futását és várakozik egy billentyû leütésére, majd annak ASCII kódjával visszatér.
	\return	A visszatérési érték a lenyomott billentyû ASCII kódja.
	\ingroup ALAP

	A függvény segítségével karaktert kérhetünk be a billentyûzetrõl, madj a programunk azt vizsgálva haladhat tovább.
	<br> 10 ms-ként megvizsgálja, hogy történt-e billentyûzet esemény, ha igen akkor visszaadja fõprogramnak a billenytû ASCII kódját, majd az folyatatja futását.
	<br>EXTRA:	minden vizsgálatkor frissíti a képernyõtartalmat, és vizsgálja az exit eseményt!

	\include	getch_00.c	
*/

char ksdl_getch() 
{
    bool done = false;
    char c;



    while (!done)
    {
        // message processing loop
        //SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(1);
                break;
            // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    c=event.key.keysym.unicode & 0x7F;
                    done = true;
                    break;
                }
            } // end switch
        } // end of message processing


        SDL_Flip(screen);
        SDL_Delay(10);
    }
    return c;
}







/** \brief Megvizsgája a billenytûzetmemória tartalmát, és ha volt leütés akkor annak ASCII kódjával tér vissza, ha nem volt akkor nulla értékkel!
	\return	A visszatérési érték a lenyomott billentyû ASCII kódja, ha nem volt lenyomott billentyû akkor nulla.
	\ingroup ALAP

	A függvény arra alkamas, hogy úgy kérjünk be billentyût, hogy nem állítjuk meg a programot, mint a ksdl_getch()-val tennénk, így egy animáció folyamatos futat
	és csak akkor avatkozunk be, volt billentyûzet leütés.
	<br>10 ms-ként megvizsgálja, hogy történt-e billentyûzet esemény, ha igen akkor a fõprogram folyatatja futását. 
	<br>EXTRA:	minden vizsgálatkor frissíti a képernyõtartalmat, és vizsgálja az exit eseményt!
	
	\include ksdl_kbhit_00.c	
*/
char ksdl_kbhit()
{
    char c;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_KEYDOWN)
        {
        c=event.key.keysym.unicode & 0x7F;

        return c;
        }
        else if(event.type==SDL_QUIT)
        {
            SDL_Quit();
                exit(1);
        }
    }
    return 0;


}








/** \brief Megállítja a program futását és várakozik egy billentyû leütésére.

	\ingroup ALAP

	10 ms-ként megvizsgálja, hogy történt-e billentyûzet esemény, ha igen akkor a fõprogram folyatatja futását. 
	<br>EXTRA:	minden vizsgálatkor frissíti a képernyõtartalmat, és vizsgálja az exit eseményt!
*/
void waitforkey()
{
    bool done = false;

    while (!done)
    {
        // message processing loop
        //SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                exit(1);
                break;
            // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    //if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                    break;
                }
            } // end switch
        } // end of message processing


        SDL_Flip(screen);
        SDL_Delay(10);
    }
}





/**	\brief Inicializálja az alapvetõ fontkészletet

	\ingroup FONT

	Betölti az alapvetõ fontkészleteket a data/font könyvtárból.
	Ha nem adta meg helyesen a data könyvtár elérési útját, a program nem fog mûködni!
*/
int ksdl_fontinit()
{
    char str_base[150];

    strcpy(str_base,PATH);
    strcat(str_base,"\\font\\arial_9_n.bmp");
    font0=initfont(str_base);

    strcpy(str_base,PATH);
    strcat(str_base,"\\font\\arial_10_n.bmp");
    font1=initfont(str_base);

    strcpy(str_base,PATH);
    strcat(str_base,"\\font\\arial_11_n.bmp");
    font2=initfont(str_base);

    strcpy(str_base,PATH);
    strcat(str_base,"\\font\\arial_12_n.bmp");
    font3=initfont(str_base);

    strcpy(str_base,PATH);
    strcat(str_base,"\\font\\arial_12_n.bmp");
    font4=initfont(str_base);

    basefont=font0;
	return 0;
}

/** \brief Lekérdezi egy kép (felszín) szélességét
	\param surface annak az sdl felszínnek a neve amelynek a meretere vagyunk kivancsiak ( elefant, ship,screen )
	\ingroup ALAP

	A függvény segítségével megtudhatjuk, a megadott felszín szélességét.
	FIGYELEM ha az alap ablakra vagyunk kíváncsiak akkor screen-t kell megadni paraméterként!!!
	
	\since 0.6 
	\include	getx_gety_00.c	
*/
int getx(SDL_Surface *surface)
{
return    surface->w;   // visszater az adott felszin szelessegevel
}

/** \brief Lekérdezi egy kép (felszín) magasságát
	\param surface annak az sdl felszínnek a neve amelynek a méretére vagyunk kíváncsiak ( elefant, ship,screen )
	\ingroup ALAP

	A függvény segítségével megtudhatjuk, a megadott felszín magasságát.
	FIGYELEM ha az alap ablakra vagyunk kíváncsiak akkor screen-t kell megadni paraméterként!!!
	
	\since 0.6 
	\include	getx_gety_00.c	
*/
int gety(SDL_Surface *surface)
{
return     surface->h; // visszater az adott felszin magassagaval
}

/** \brief Firssiti a mouse struktúra adatait, az egér ektuális információival.
	\ingroup MOUSE

	A mosuse struktúrában tárolódnak az egérrel kacpcsolatos információk.
	A függvény hívása után, ha volt új, eddig le nem kezelt gombnyomás akkor annak értékeivel tölti fel a következõ változókat:<br>
	mouse.xnow  - az egér x koordinátája <br>
	mouse.ynow  - a egér y koordinátája <br>
	mouse.xrel   -  az elõzõ vizsgálattól mért  x koordinátája <br>
	mouse.yrel   -  a lenyomás helyének y koordinátája <br>
	mouse.time  - a vizsgálat idõpillanata (a program elindításától eltelt milsecundumok száma) <br>
	
	\include	mouse_00.c	
	
	Figyelem ha nem volt új esemény akkor a struktóra tagjai nem frissülnek!
	
	\since 0.7 
*/
void getmotion()
{
    bool done = false;
    char c;
    int x,y;

    SDL_PollEvent(&event);
    switch (event.type)
        {
        case SDL_MOUSEMOTION :
            mouse.xrel=event.motion.xrel;
            mouse.yrel=event.motion.yrel;
            mouse.xnow=event.motion.x;
            mouse.ynow=event.motion.y;
            mouse.time=SDL_GetTicks();
        break;

        case SDL_QUIT:
             SDL_Quit();
                exit(1);
        break;


        }

}


/** \brief Firssiti a mouse struktúra adatait, az utolsó lenyomás adataival.
	\return Igaz értékkel tér vissza ha volt uj gombesemény.
	\ingroup MOUSE

	A mosuse struktúrában tárolódnak az egérrel kacpcsolatos információk.
	A függvény hívása után, ha volt új, eddig le nem kezelt gombnyomás akkor annak értékeivel tölti fel a következõ változókat:<br>
	mouse.xbut  - a lenyomás helyének x koordinátája <br>
	mouse.ybut  - a lenyomás helyének y koordinátája <br>
	mouse.button  - a lenyomott gomb azonosítója (0,1,2,3,4,5) <br>
	mouse.time  - a lenyomás idõpillanata (a program elindításától eltelt milsecundumok száma) <br>
	
	\include	mouse_00.c
	
	FONTOS - nezzetek meg a mosue_01.c -t is!
	Figyelem ha nem volt új esemény akkor a struktóra tagjai nem frissülnek!
	
	\since 0.7 
*/
int getbutton()
{
    bool done = false;
    char c;
    int x,y;

    SDL_PollEvent(&event);
    mouse.newevent=0;
    switch (event.type)
        {

        case SDL_MOUSEBUTTONDOWN :
       // case SDL_MOUSEBUTTONUP :
            mouse.xbut=event.button.x;
            mouse.ybut=event.button.y;
            mouse.state=event.button.state;
            mouse.type=event.button.type;
            mouse.button=event.button.button;
            mouse.time=SDL_GetTicks();
            mouse.newevent=1;
            break;

        case SDL_QUIT:
                SDL_Quit();
                exit(1);
                break;

        }
    return mouse.newevent;	// ha igaz akkor volt uj esemeny 
}


/*! \mainpage Ksdl leírás


	
Elkészült a V0.7 !
  
A régen várt egérkezelés végre megérkezett!

A modulok címszó alól könnyedén el lehet indulni!

Fontos : elkészült a 0.7-os változat a kódból, a projekt templatebõl elég a 0.3-as azt nem kell újratelepíteni!

<br>


\section 	download  Telepítés és letöltés
Telepítés a wiki lapról!    <A href="http://wiki.mai.kando.hu/index.php/Sdl/download#A_KSDL_telep.C3.ADt.C3.A9se"> WIKI-KSDL telepítése.</A>

<A href="http://mai.kando.hu/downloads/ksdl-v0.7.zip"> KSDL-V0.6 letöltése.</A>

<A href="http://mai.kando.hu/downloads/ksdl.chm"> CHM letöltése.</A>

<br>
\section news Újdonságok a V0.7-ben

<br>
\subsection Egér Egérkezelés 
<br>
Az egérkezlés végre elérhetõvé vált, egyenlõre
két függvénnyel és egy struktúráva.
A mouse struktúra tárolja az egér adait mely a két függvény<br>
getbutton();<br>
getmotion();<br>
hatására frissül!

<br><br>

\subsection SAFEMOD SAFEMOD
Új opcióként a SAFEMOD konstansal definiálásával be lehet állítani a ,
hogy ne töltse be az alapértelmezett képeket és fontkészleteket.
Így ha elérhetetlenek, (más oprenszer, rossz elérési út) akkor is
használható a rendszer. <br>
<br>
Használata: a proram elején a másik define alá  be kell írni a köv sort:<br>
##define SAFEMOD<br>
<br>
FONTOS ha ezt használjátok akkor az alap pédaprogram nem fog menni,<br>
mert a DrawPic(elephant,100,100); az elefant képet hasznalana amit most nem toltunk be.

<br><br>



\section news Újdonságok a V0.6-ban

<br>
\subsection chm CHM - AZAZ help fromátum
<br>
Jelen dokumentáció eléretõ chm formátumban is!<br>
Nézzétek meg, így webkapcsolat nélkül is használható a help!<br>
<A href="http://mai.kando.hu/downloads/ksdl.chm"> CHM letöltése.</A><br>
A menüben még gondok vannak a magyar ékezetekkel!<br>

\subsection nuwfuncbase Új függvények az ALAP modulban
Néhány Új függvény segíti a felhasználót a munkában: <br><br>
ksdl_init_extra() - Lehetõvé válik, teljes képernyõs program írása valamint hardveres gyorsítás használata (a ksdl_init() helyett lehet használni) <br><br>
getx() - Megmondja egy kép vagy az ablak vízszintes és méretét pixelekben. <br><br>
gety() - Megmondja egy kép vagy az ablak függõleges és méretét pixelekben. <br><br>
getpixel() - Egy pixel színét tudjuk vele megálapítani. <br><br>
getpixel_rgb() - Egy pixel színét kapjuk meg R,G,B külön változókban. <br><br>
<br>

\subsection nuwfuncpic Új függvények a PICTURE modulban
cut() - Terület kivágása és felszínre elyezése. <br><br>
paste() - Kép beillesztése frissítés nélkül. <br><br>
move() - Animáció megvalósítása. <br><br>

<br>

\subsection nuwdoc Dokumentáció
Leírtam néhány SDL függvényt, ezeket érdemes használni
SDL_EnableKeyRepeat() - billentyû ismétlés <br><br>
SDL_WM_SetCaption() - ablak címbeállítás<br><br>
SDL_WM_IconifyWindow() - ikonizálás<br><br>
SDL_Delay() - késleltetés<br><br>
SDL_Flip() - ikonizálás<br><br>
SDL_UpdateRect() - ikonizálás<br><br>
<br>




\author Gergõ
*/

/**	PIXEL PÉLDÁK

	\example pixel_00.c	
	Pixel példa <br> 
	A két putpixel függvényt használva kirajzolunk egy egy pontot.
	
	\example pixel_01.c	
	Pixel példa <br> 
	Egy forciklus segítségével vízszintes vonalakat húzunk!<br>
	Gyakorlásként csináljátok meg függõlegesre!
		
	\example pixel_02.c	
	Pixel példa <br> 
	Egymásba ágyazott cikluspár segítségével négyzet alakú területet töltünk fel.

	\example pixel_03.c	
	Pixel példa <br> 
	Feltöltjük a teljes képernyõt egymásba ágyazott cikluspár segítségével.
	
*/

/**	LINE PÉLDÁK
	\example line_00.c	
	Vonal rajzoló példa,<br> 
	ebben  a programban csak egy fehér vonalat rajzolunk, két pont között.
	
	\example line_01.c	
	Vonal rajzoló példa,<br> 
	ebben  a programban  a line_rgb() segítségével rajzolunk több színes vonalat.
	
	\example line_02.c	
	Vonal rajzoló példa,<br> 
	ebben  a programban két egymásnak szembefordíított legyezõt rajzolunk,<br>
	így muttava meg a for ciklus és line függvények összekapcsolását.
*/



/**	BAR PÉLDÁK

	\example bar_00.c	
	Teglalap rajzoló példa <br> 
	Három színes téglalapból egy zászlót rejzolunk.
	
	\example bar_01.c	
	Teglalap rajzoló példa <br> 
	Befestjük a teljes hátteret, majd több szürkeárnyalatú téglalapot rajzolunk, közös bal felsõ pontal.
	
*/

/**	CIRCLE PÉLDÁK

	\example circle_00.c	
	Kör rajzoló példa <br> 
	Két koncentrikus kört rajzolunk.
	
	\example circle_01.c	
	kör rajzoló példa <br> 
	Piros körvonalakból céltáblát rajzolunk.
	
*/

/**	FILLCIRCLE PÉLDÁK

	\example fillcircle_00.c	
	Kitöltött kört rajzoló példa <br> 
	Egy nagy zöld kör közepére egy kisebb pirosat teszünk.
	
	\example fillcircle_01.c	
	Kitöltött kört rajzoló példa <br> 
	Céltáblát rajzolunk kitöltött koncentrikus körökbõl.<br>
	Hogy látszódjanak a körök kívülrõl kezdjük és befelé haladva folyamatosan csokkentjük a zöld komponenst és növeljük a a pirosat.
*/

/**	A PICTURE modul példái

	\example drawx_00.c	
	Alappprogram<br>
	Ez töltõdik be alapértelmezésben!
	
	\example drawx_01.c	
	Fájlbol betöltünk egy bmp képet<br> 
	Figyeljünk arra, hogy jó legyen az elérési út!<br>
	Figyeljünk arra, hogy két backslash karaktert kell tenni a könyvtárak között.
	
	
	\example drawx_02.c	
	Kép betöltés a memóriába.<br> 
	A 8. sorban a pic0 az új képre fog mutatni, így innentõl ezzel a változóval azt érjük el.<br>
	A 9. sorban ki is próbájuk.
	
	A 7. sorban létrehozunk egy felszínre mutató változót.
	Majd a 14. sorban betöltjük a memóriába az új képet, és az mondjuk, hogy mutasson rá az ujkep mutató.
	A következõ sorban pedig kiirjuk!
	
	\example drawxmask_00.c	
	Maszkolás alapjai<br> 
	A képre meghatározozz maszk szinét nem másljuk át a nagy képre, így a keretet levágjuk és csak az objektumot fogjuk látni!
	
	\example drawxmask_01.c	
	Másik mask példa, amikor a rajzolatot határozzuk meg maskoklás színének!<br>
	Így a vörös háttéren at elefántnak csak a fehére fog látszani!
	
	\example drawxposmask_00.c	
	A képbõl kivágunk egy részletet és azt másoljuk.<br> 
	A maskolást is bemutatjuk ebben a példában.
	
	\example setmask_00.c	
	E maszkolás után már hívhatjuk a DrawPic() függvényt is mert a maskszín nélkül fog rajzolni!<br> 

*/

/**	FONTos PÉLDÁK

	\example dchar_00.c	
	A drawchar függvény.<br> 
	
	
	\example dchar_01.c	
	Az abc kiírása betünként<br> 
	

	\example dstring_00.c	
	Sztring kiirása a képernyõre<br> 
	
	\example dstring_01.c	
	Számot tartlamazó változó kiírása sztringként.<br> 
	Avagy bevezetõ az sprintf használatába.
	
	\example initfont_00.c	
	Új fontkészlet betöltése.<br> 
	Figyelem csak helyes elérési úttal mûködik!
	
	\example setfontcolor_00.c	
	Fontok színének megváltoztatása.<br> 
	
	
	\example changefont_00.c	
	Fontfészlet váltása<br> 
	
*/

/**	FONTos PÉLDÁK

	\example ksdl_kbhit_00.c	
	A tron játék egy egyszerû verziója<br>
	Itt nem lehet meghalni!
	
	
	\example getch_00.c	
	Beker egy betüt és annak értékétõl függõen rajzol ki egy pontot.<br> 
	
	
*/

/**	GETPIXEL -es példák

	\example getpixel_00.c	
	Lemásoljuk egy téglalap színét.
	
	
	\example getpixel_rgb_00.c	
	Fogjuk a LIGHTCYAN színü téglalpot és eljátszunk a színeivel. 
	
	
*/
/**	GETPIXEL -es példák

	\example getx_gety_00.c
	A getx() gety() függvények segtségével könnyen pozícionálunk a képernyõn.
	
	
*/

/**	Egerkezeles -es példák

	\example mouse_00.c
	Kiirjuk a kepernyore az eger struktúra adatait.
	
	\example mouse_01.c
	Tipikus gombos példa.
	
	
*/


	
/** \brief Ha a veztélés erre a sorra kerül akkor a megadott ideig várakozik a program
	\param ms a várkozás mértéke
	\ingroup SDL
	\code	SDL_Delay(1000); // 1 masodpercig var a program
	\endcode
*/	
/** \brief Billenytzû nyomvatartását imételt billentyûzetleütésnek érzékelhetjük e fv segítségével
	\param delay hány ms-ig várjon mielött elkezdi ismételt nyomásnak venni
	\param interval hány ms-ként vegye ismételt lenyomásnak
	

	\ingroup SDL

	A gyorsításhot a második paramétert kell csökkenteni.
	
	\code	SDL_EnableKeyRepeat(1,100); // alapértelmezésben már meg van hívva ezekkel a paraméterekkel
	\endcode
*/
/** \brief Az ablak címét és ikonját lehet vele beállítani

	

	\ingroup SDL

	Ha nem akarunk képet betenni akkor a második paraméter legyen NULL !
	
	\code	SDL_WM_SetCaption("Hello",NULL);
	\endcode
*/	
	
	/** \brief Az ablak címét és ikonját lehet vele beállítani
	\param title a címet tartamazó string
	\param icon az ikont tartalmazó kép elérési útja
	

	\ingroup SDL

	Ha nem akarunk képet betenni akkor a második paraméter legyen NULL !
	
	\code	SDL_WM_SetCaption("Hello",NULL);
	\endcode
*/

/** \brief Frissiteni lehet vele egy képet
	\param surface az az sdl felszín amit frissíteni akarunk (pl:screen)

	
	\ingroup SDL

	Frissíthetjük vele az alapképernyõegy területét, akkor ahsznos ha,<br>
	bar_nofrs() vagy paste() függvényt hasnáltunk!
	
	
	\code	SDL_UpdateRec(screen, 100, 100,100,100); // HASZNÁLD ÍGY
	\endcode
*/

/** \brief Képernyõ területet tudunk frissíteni vele.
	\param surface az az sdl felszín amit frissíteni akarunk (pl:screen)
	\param x		a terület bal felsõ sarkának x koordinátája a megjelenítõfelületen
	\param y		a terület bal felsõ sarkának y koordinátája a megjelenítõfelületen
	\param w		a frissítendõ terület szélessége
	\param h		a frissítendõ terület magassága
	\ingroup SDL

	Frissíthetjük vele az alapképernyõt, akkor ahsznos ha,<br>
	bar_nofrs() vagy paste() függvényt hasnáltunk!
	
	
	\code	SDL_Flip(scrren); // HASZNÁLD ÍGY
	\endcode
*/


