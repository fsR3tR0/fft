/** \file ksdl.h
	\brief  Az  alapvet� in�cilaz�c�s, illetve billety�zetkezel� f�ggv�nyeket tartalmazza.
	\author gerg�

	Ebben a f�jlban tal�lhat�k a azok a f�ggv�nyek melyek seg�ts�g�vel a <br> 
	fel lehet in�cializ�lni a KSDL-t, illetve az alapvet� billenty�beolvas�s�i rutinok kaptak itt helyet<br> 
*/

/**	\defgroup ALAP		ALAP		Az alapvet� in�cilaz�c�s, illetve billety�zetkezel� f�ggv�nyeket tartalmazza.

	\defgroup PICTURE	PICTURE	A k�pek kezel�s�vel kapcsolatos f�ggv�nyeket �s v�ltoz�kat tartalmazza.

	\defgroup GEOM	GEOM	A geometriai modul alapvet� rajzol�f�ggv�nyeket tartalmaz.

	\defgroup FONT		FONT	A bmpfontk�szletek haszn�lat�t biztos�t� f�ggv�nyeket tartalmazza.

	\defgroup COLORS	COLORS	Sz�nek konstansait  tal�lhatj�tok itt!
	
	\defgroup	MOUSE	MOUSE		Az eg�rkezel�shez sz�ks�ges f�ggv�nyek �s a mouse strukt�ra.
	
	\defgroup	SDL	SDL		Az SDL f�ggv�nyek le�r�sa (MINDEN ami SDL_ -el kezd�dik)
*/

/** A PI �rt�k�t a legegyszer�bb �gy konstansal megadni.
*/
#define PI 3.1415926535897932384626433832795f
#include <math.h>

/**	Alap�rtelmezett SDL felsz�n.

	Ez a felsz�n jelenik meg a k�perny�n.
	Majdnem minden KSDL f�ggv�ny ezt haszn�lja rajzol�fel�letk�nt. 
	Az SDL-ben mi is hozhatunk l�tre felsz�neket, �gy tudunk rajzolni az egyikre, m�g a m�sikat megjelen�tj�k, illetve
	az el�re bet�lt�tt k�pek �s fontok egy el�re elk�sz�tett hasonl� felsz�nben vannak elt�rolva.
*/

SDL_Surface *screen;    // Globalis valtozo  (strukturapointer) ennek segitsegevel
                        // lehet elerni a grafikus feluletet

/**	Ebben a strukt�r�ban t�rol�dik minden eg�r inform�ci�.
	\ingroup MOUSE
	
*/
struct PATKANY{
	/** \brief  Az eg�r x koordin�t�ja az utols� lenyom�s pillanat�ban.*/
    int xbut;
	/** \brief  Az eg�r y koordin�t�ja az utols� lenyom�s pillanat�ban.*/
	int ybut;
	/** \brief  Az eg�r x koordin�t�ja az a jelen pillanatban.*/
    int xnow;
	/** \brief  Az eg�r y koordin�t�ja az a jelen pillanatban.*/
	int ynow;
	/** \brief  Az eg�r x koordin�t�j�nak v�ltoz�sa az utols� lek�rdez�shez k�pest.*/
    int xrel;
	/** \brief  Az eg�r y koordin�t�j�nak v�ltoz�sa az utols� lek�rdez�shez k�pest.*/
	int yrel;
	/** \brief  A lenyomott gomb azonos�t�ja 
	1 - bal 2 - k�z�ps� 3 - jobb<br>
	4 - wheel up 5 - wheel down
	 */
    int button;
	int state;
	int type;
	/** \brief  A lenyom�s ideje - a program elind�t�s�t�l  eltelt milisecundomok sz�ma*/
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


/** \brief L�trehoz egy ablakot a megadott felbont�ssal
	\param w az ablak sz�less�g�t adja meg pixelben
	\param h az ablak magass�g�t adja meg pixelben
	\return null�val t�r vissza ha nem �tk�z�tt hib�ba, egy�bk�nt a visszat�r�si �rt�k 1

	\ingroup ALAP

	In�cializ�lja a SDL vide� szegmens�t, majd l�trehoz egy w x h m�ret� 32 bit-es szinm�lys�g� ablakot!<br>
	Extra : szoftveres fel�letet k�sz�t, ami egy kicsit lass�v� teheti rendszert, ugyanakkor minden k�r�lm�ny k�z�tt m�k�dik, ezt az�rt
	�rom le mert a b�trabbak �ttehetik HW_SURFACE -is a SetVideomode() f�ggv�nyt!
	
	\since 5.0 Beker�lt egy SDL_EnableKeyRepeat(1,100); f�ggv�nyh�v�s, �gy a folyamatos nyomvatart�st �gy �rz�keli
	mintha 100 ms-enk�nt le�t�tt�nk volna azt a billenty�t.
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
        printf("Nem tudom beall�tani %ix%i felbontast: %s\n",w,h, SDL_GetError());
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

/** \brief L�trehoz egy ablakot a megadott felbont�ssal, v�laszthat� hardvers �s szoftveres gyors�t�s, v�laszthat� fullscreen m�d
	\param w az ablak sz�less�g�t adja meg pixelben
	\param h az ablak magass�g�t adja meg pixelben
	\param FULL ha az �rt�ke nem nulla akkor teljes k�perny�s m�dban indul a program
	\param HWpSW  ha az �rt�ke nem nulla akkor hardveres gyors�t�st haszn�l SDL a rajzol�soz
	\return null�val t�r vissza ha nem �tk�z�tt hib�ba, egy�bk�nt a visszat�r�si �rt�k 1

	\ingroup ALAP


	In�cializ�lja a SDL vide� szegmens�t, majd l�trehoz egy w x h m�ret� 32 bit-es szinm�lys�g� ablakot!<br>
	Be�ll�that� a hardveres gyors�t�s �s a teljesk�poerny�s m�d! <br>
	FONTOS - a ksdl_init()  helyett lehet haszn�lni (Nem k�telez�)!!!
	
	\code	ksdl_init_extra(i1024,768,1,1);
	\endcode
	
	\since 0.6
	
	\warning  5.0 Beker�lt egy SDL_EnableKeyRepeat(1,100); f�ggv�nyh�v�s, �gy a folyamatos nyomvatart�st �gy �rz�keli
	mintha 100 ms-enk�nt le�t�tt�nk volna azt a billenty�t.
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
        printf("Nem tudom beall�tani %ix%i felbontast: %s\n",w,h, SDL_GetError());
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


/** \brief Lek�rdezi egy pixel sz�n�t
	\param x a lek�rdezett pixel x koordin�t�ja
	\param y a lek�rdezett pixel y koordin�t�ja
	\return a k�v�nt sz�nnel t�r vissza, �sszehasonl�that� a COLORS konstansokkal

	\ingroup ALAP

	A f�ggv�ny seg�ts�g�vel megtudhatjuk, hogy az adott ter�leten milyen sz�n� a pixel!
	
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

/** \brief Lek�rdezi egy pixel sz�n�t, de rgb �sszetev�nk�nt.
	\param x a lek�rdezett pixel x koordin�t�ja
	\param y a lek�rdezett pixel y koordin�t�ja
	\param r annak a v�ltoz�nak a c�me amelybe a piros sz�n�sszetev� m�rt�k�t szeretn�nk tenni (0-256) sz�m lesz!
	\param g annak a v�ltoz�nak a c�me amelybe a z�ld sz�n�sszetev� m�rt�k�t szeretn�nk tenni (0-256) sz�m lesz!
	\param b annak a v�ltoz�nak a c�me amelybe a k�k sz�n�sszetev� m�rt�k�t szeretn�nk tenni (0-256) sz�m lesz!
	\ingroup ALAP

	A f�ggv�ny seg�ts�g�vel megtudhatjuk, hogy az adott ter�leten milyen sz�n� a pixel!
	FIGYELEM a f�ggv�ny c�meket v�r az utols� 3 param�ter�ben (tess�k haszn�lni a c�mk�pz� & oper�tort), 
	az�rt kell c�mekkel dolgozni mert a f�ggv�ny csak egy �rt�kkel t�rhet vissza �s nek�nk itt 3-ra van sz�ks�g�nk!
	
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




/** \brief Meg�ll�tja a program fut�s�t �s v�rakozik egy billenty� le�t�s�re, majd annak ASCII k�dj�val visszat�r.
	\return	A visszat�r�si �rt�k a lenyomott billenty� ASCII k�dja.
	\ingroup ALAP

	A f�ggv�ny seg�ts�g�vel karaktert k�rhet�nk be a billenty�zetr�l, madj a programunk azt vizsg�lva haladhat tov�bb.
	<br> 10 ms-k�nt megvizsg�lja, hogy t�rt�nt-e billenty�zet esem�ny, ha igen akkor visszaadja f�programnak a billenyt� ASCII k�dj�t, majd az folyatatja fut�s�t.
	<br>EXTRA:	minden vizsg�latkor friss�ti a k�perny�tartalmat, �s vizsg�lja az exit esem�nyt!

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







/** \brief Megvizsg�ja a billenyt�zetmem�ria tartalm�t, �s ha volt le�t�s akkor annak ASCII k�dj�val t�r vissza, ha nem volt akkor nulla �rt�kkel!
	\return	A visszat�r�si �rt�k a lenyomott billenty� ASCII k�dja, ha nem volt lenyomott billenty� akkor nulla.
	\ingroup ALAP

	A f�ggv�ny arra alkamas, hogy �gy k�rj�nk be billenty�t, hogy nem �ll�tjuk meg a programot, mint a ksdl_getch()-val tenn�nk, �gy egy anim�ci� folyamatos futat
	�s csak akkor avatkozunk be, volt billenty�zet le�t�s.
	<br>10 ms-k�nt megvizsg�lja, hogy t�rt�nt-e billenty�zet esem�ny, ha igen akkor a f�program folyatatja fut�s�t. 
	<br>EXTRA:	minden vizsg�latkor friss�ti a k�perny�tartalmat, �s vizsg�lja az exit esem�nyt!
	
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








/** \brief Meg�ll�tja a program fut�s�t �s v�rakozik egy billenty� le�t�s�re.

	\ingroup ALAP

	10 ms-k�nt megvizsg�lja, hogy t�rt�nt-e billenty�zet esem�ny, ha igen akkor a f�program folyatatja fut�s�t. 
	<br>EXTRA:	minden vizsg�latkor friss�ti a k�perny�tartalmat, �s vizsg�lja az exit esem�nyt!
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





/**	\brief Inicializ�lja az alapvet� fontk�szletet

	\ingroup FONT

	Bet�lti az alapvet� fontk�szleteket a data/font k�nyvt�rb�l.
	Ha nem adta meg helyesen a data k�nyvt�r el�r�si �tj�t, a program nem fog m�k�dni!
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

/** \brief Lek�rdezi egy k�p (felsz�n) sz�less�g�t
	\param surface annak az sdl felsz�nnek a neve amelynek a meretere vagyunk kivancsiak ( elefant, ship,screen )
	\ingroup ALAP

	A f�ggv�ny seg�ts�g�vel megtudhatjuk, a megadott felsz�n sz�less�g�t.
	FIGYELEM ha az alap ablakra vagyunk k�v�ncsiak akkor screen-t kell megadni param�terk�nt!!!
	
	\since 0.6 
	\include	getx_gety_00.c	
*/
int getx(SDL_Surface *surface)
{
return    surface->w;   // visszater az adott felszin szelessegevel
}

/** \brief Lek�rdezi egy k�p (felsz�n) magass�g�t
	\param surface annak az sdl felsz�nnek a neve amelynek a m�ret�re vagyunk k�v�ncsiak ( elefant, ship,screen )
	\ingroup ALAP

	A f�ggv�ny seg�ts�g�vel megtudhatjuk, a megadott felsz�n magass�g�t.
	FIGYELEM ha az alap ablakra vagyunk k�v�ncsiak akkor screen-t kell megadni param�terk�nt!!!
	
	\since 0.6 
	\include	getx_gety_00.c	
*/
int gety(SDL_Surface *surface)
{
return     surface->h; // visszater az adott felszin magassagaval
}

/** \brief Firssiti a mouse strukt�ra adatait, az eg�r ektu�lis inform�ci�ival.
	\ingroup MOUSE

	A mosuse strukt�r�ban t�rol�dnak az eg�rrel kacpcsolatos inform�ci�k.
	A f�ggv�ny h�v�sa ut�n, ha volt �j, eddig le nem kezelt gombnyom�s akkor annak �rt�keivel t�lti fel a k�vetkez� v�ltoz�kat:<br>
	mouse.xnow  - az eg�r x koordin�t�ja <br>
	mouse.ynow  - a eg�r y koordin�t�ja <br>
	mouse.xrel   -  az el�z� vizsg�latt�l m�rt  x koordin�t�ja <br>
	mouse.yrel   -  a lenyom�s hely�nek y koordin�t�ja <br>
	mouse.time  - a vizsg�lat id�pillanata (a program elind�t�s�t�l eltelt milsecundumok sz�ma) <br>
	
	\include	mouse_00.c	
	
	Figyelem ha nem volt �j esem�ny akkor a strukt�ra tagjai nem friss�lnek!
	
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


/** \brief Firssiti a mouse strukt�ra adatait, az utols� lenyom�s adataival.
	\return Igaz �rt�kkel t�r vissza ha volt uj gombesem�ny.
	\ingroup MOUSE

	A mosuse strukt�r�ban t�rol�dnak az eg�rrel kacpcsolatos inform�ci�k.
	A f�ggv�ny h�v�sa ut�n, ha volt �j, eddig le nem kezelt gombnyom�s akkor annak �rt�keivel t�lti fel a k�vetkez� v�ltoz�kat:<br>
	mouse.xbut  - a lenyom�s hely�nek x koordin�t�ja <br>
	mouse.ybut  - a lenyom�s hely�nek y koordin�t�ja <br>
	mouse.button  - a lenyomott gomb azonos�t�ja (0,1,2,3,4,5) <br>
	mouse.time  - a lenyom�s id�pillanata (a program elind�t�s�t�l eltelt milsecundumok sz�ma) <br>
	
	\include	mouse_00.c
	
	FONTOS - nezzetek meg a mosue_01.c -t is!
	Figyelem ha nem volt �j esem�ny akkor a strukt�ra tagjai nem friss�lnek!
	
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


/*! \mainpage Ksdl le�r�s


	
Elk�sz�lt a V0.7 !
  
A r�gen v�rt eg�rkezel�s v�gre meg�rkezett!

A modulok c�msz� al�l k�nnyed�n el lehet indulni!

Fontos : elk�sz�lt a 0.7-os v�ltozat a k�db�l, a projekt templateb�l el�g a 0.3-as azt nem kell �jratelep�teni!

<br>


\section 	download  Telep�t�s �s let�lt�s
Telep�t�s a wiki lapr�l!    <A href="http://wiki.mai.kando.hu/index.php/Sdl/download#A_KSDL_telep.C3.ADt.C3.A9se"> WIKI-KSDL telep�t�se.</A>

<A href="http://mai.kando.hu/downloads/ksdl-v0.7.zip"> KSDL-V0.6 let�lt�se.</A>

<A href="http://mai.kando.hu/downloads/ksdl.chm"> CHM let�lt�se.</A>

<br>
\section news �jdons�gok a V0.7-ben

<br>
\subsection Eg�r Eg�rkezel�s 
<br>
Az eg�rkezl�s v�gre el�rhet�v� v�lt, egyenl�re
k�t f�ggv�nnyel �s egy strukt�r�va.
A mouse strukt�ra t�rolja az eg�r adait mely a k�t f�ggv�ny<br>
getbutton();<br>
getmotion();<br>
hat�s�ra friss�l!

<br><br>

\subsection SAFEMOD SAFEMOD
�j opci�k�nt a SAFEMOD konstansal defini�l�s�val be lehet �ll�tani a ,
hogy ne t�ltse be az alap�rtelmezett k�peket �s fontk�szleteket.
�gy ha el�rhetetlenek, (m�s oprenszer, rossz el�r�si �t) akkor is
haszn�lhat� a rendszer. <br>
<br>
Haszn�lata: a proram elej�n a m�sik define al�  be kell �rni a k�v sort:<br>
##define SAFEMOD<br>
<br>
FONTOS ha ezt haszn�lj�tok akkor az alap p�daprogram nem fog menni,<br>
mert a DrawPic(elephant,100,100); az elefant k�pet hasznalana amit most nem toltunk be.

<br><br>



\section news �jdons�gok a V0.6-ban

<br>
\subsection chm CHM - AZAZ help from�tum
<br>
Jelen dokument�ci� el�ret� chm form�tumban is!<br>
N�zz�tek meg, �gy webkapcsolat n�lk�l is haszn�lhat� a help!<br>
<A href="http://mai.kando.hu/downloads/ksdl.chm"> CHM let�lt�se.</A><br>
A men�ben m�g gondok vannak a magyar �kezetekkel!<br>

\subsection nuwfuncbase �j f�ggv�nyek az ALAP modulban
N�h�ny �j f�ggv�ny seg�ti a felhaszn�l�t a munk�ban: <br><br>
ksdl_init_extra() - Lehet�v� v�lik, teljes k�perny�s program �r�sa valamint hardveres gyors�t�s haszn�lata (a ksdl_init() helyett lehet haszn�lni) <br><br>
getx() - Megmondja egy k�p vagy az ablak v�zszintes �s m�ret�t pixelekben. <br><br>
gety() - Megmondja egy k�p vagy az ablak f�gg�leges �s m�ret�t pixelekben. <br><br>
getpixel() - Egy pixel sz�n�t tudjuk vele meg�lap�tani. <br><br>
getpixel_rgb() - Egy pixel sz�n�t kapjuk meg R,G,B k�l�n v�ltoz�kban. <br><br>
<br>

\subsection nuwfuncpic �j f�ggv�nyek a PICTURE modulban
cut() - Ter�let kiv�g�sa �s felsz�nre elyez�se. <br><br>
paste() - K�p beilleszt�se friss�t�s n�lk�l. <br><br>
move() - Anim�ci� megval�s�t�sa. <br><br>

<br>

\subsection nuwdoc Dokument�ci�
Le�rtam n�h�ny SDL f�ggv�nyt, ezeket �rdemes haszn�lni
SDL_EnableKeyRepeat() - billenty� ism�tl�s <br><br>
SDL_WM_SetCaption() - ablak c�mbe�ll�t�s<br><br>
SDL_WM_IconifyWindow() - ikoniz�l�s<br><br>
SDL_Delay() - k�sleltet�s<br><br>
SDL_Flip() - ikoniz�l�s<br><br>
SDL_UpdateRect() - ikoniz�l�s<br><br>
<br>




\author Gerg�
*/

/**	PIXEL P�LD�K

	\example pixel_00.c	
	Pixel p�lda <br> 
	A k�t putpixel f�ggv�nyt haszn�lva kirajzolunk egy egy pontot.
	
	\example pixel_01.c	
	Pixel p�lda <br> 
	Egy forciklus seg�ts�g�vel v�zszintes vonalakat h�zunk!<br>
	Gyakorl�sk�nt csin�lj�tok meg f�gg�legesre!
		
	\example pixel_02.c	
	Pixel p�lda <br> 
	Egym�sba �gyazott ciklusp�r seg�ts�g�vel n�gyzet alak� ter�letet t�lt�nk fel.

	\example pixel_03.c	
	Pixel p�lda <br> 
	Felt�ltj�k a teljes k�perny�t egym�sba �gyazott ciklusp�r seg�ts�g�vel.
	
*/

/**	LINE P�LD�K
	\example line_00.c	
	Vonal rajzol� p�lda,<br> 
	ebben  a programban csak egy feh�r vonalat rajzolunk, k�t pont k�z�tt.
	
	\example line_01.c	
	Vonal rajzol� p�lda,<br> 
	ebben  a programban  a line_rgb() seg�ts�g�vel rajzolunk t�bb sz�nes vonalat.
	
	\example line_02.c	
	Vonal rajzol� p�lda,<br> 
	ebben  a programban k�t egym�snak szembeford��tott legyez�t rajzolunk,<br>
	�gy muttava meg a for ciklus �s line f�ggv�nyek �sszekapcsol�s�t.
*/



/**	BAR P�LD�K

	\example bar_00.c	
	Teglalap rajzol� p�lda <br> 
	H�rom sz�nes t�glalapb�l egy z�szl�t rejzolunk.
	
	\example bar_01.c	
	Teglalap rajzol� p�lda <br> 
	Befestj�k a teljes h�tteret, majd t�bb sz�rke�rnyalat� t�glalapot rajzolunk, k�z�s bal fels� pontal.
	
*/

/**	CIRCLE P�LD�K

	\example circle_00.c	
	K�r rajzol� p�lda <br> 
	K�t koncentrikus k�rt rajzolunk.
	
	\example circle_01.c	
	k�r rajzol� p�lda <br> 
	Piros k�rvonalakb�l c�lt�bl�t rajzolunk.
	
*/

/**	FILLCIRCLE P�LD�K

	\example fillcircle_00.c	
	Kit�lt�tt k�rt rajzol� p�lda <br> 
	Egy nagy z�ld k�r k�zep�re egy kisebb pirosat tesz�nk.
	
	\example fillcircle_01.c	
	Kit�lt�tt k�rt rajzol� p�lda <br> 
	C�lt�bl�t rajzolunk kit�lt�tt koncentrikus k�r�kb�l.<br>
	Hogy l�tsz�djanak a k�r�k k�v�lr�l kezdj�k �s befel� haladva folyamatosan csokkentj�k a z�ld komponenst �s n�velj�k a a pirosat.
*/

/**	A PICTURE modul p�ld�i

	\example drawx_00.c	
	Alappprogram<br>
	Ez t�lt�dik be alap�rtelmez�sben!
	
	\example drawx_01.c	
	F�jlbol bet�lt�nk egy bmp k�pet<br> 
	Figyelj�nk arra, hogy j� legyen az el�r�si �t!<br>
	Figyelj�nk arra, hogy k�t backslash karaktert kell tenni a k�nyvt�rak k�z�tt.
	
	
	\example drawx_02.c	
	K�p bet�lt�s a mem�ri�ba.<br> 
	A 8. sorban a pic0 az �j k�pre fog mutatni, �gy innent�l ezzel a v�ltoz�val azt �rj�k el.<br>
	A 9. sorban ki is pr�b�juk.
	
	A 7. sorban l�trehozunk egy felsz�nre mutat� v�ltoz�t.
	Majd a 14. sorban bet�ltj�k a mem�ri�ba az �j k�pet, �s az mondjuk, hogy mutasson r� az ujkep mutat�.
	A k�vetkez� sorban pedig kiirjuk!
	
	\example drawxmask_00.c	
	Maszkol�s alapjai<br> 
	A k�pre meghat�rozozz maszk szin�t nem m�sljuk �t a nagy k�pre, �gy a keretet lev�gjuk �s csak az objektumot fogjuk l�tni!
	
	\example drawxmask_01.c	
	M�sik mask p�lda, amikor a rajzolatot hat�rozzuk meg maskokl�s sz�n�nek!<br>
	�gy a v�r�s h�tt�ren at elef�ntnak csak a feh�re fog l�tszani!
	
	\example drawxposmask_00.c	
	A k�pb�l kiv�gunk egy r�szletet �s azt m�soljuk.<br> 
	A maskol�st is bemutatjuk ebben a p�ld�ban.
	
	\example setmask_00.c	
	E maszkol�s ut�n m�r h�vhatjuk a DrawPic() f�ggv�nyt is mert a masksz�n n�lk�l fog rajzolni!<br> 

*/

/**	FONTos P�LD�K

	\example dchar_00.c	
	A drawchar f�ggv�ny.<br> 
	
	
	\example dchar_01.c	
	Az abc ki�r�sa bet�nk�nt<br> 
	

	\example dstring_00.c	
	Sztring kiir�sa a k�perny�re<br> 
	
	\example dstring_01.c	
	Sz�mot tartlamaz� v�ltoz� ki�r�sa sztringk�nt.<br> 
	Avagy bevezet� az sprintf haszn�lat�ba.
	
	\example initfont_00.c	
	�j fontk�szlet bet�lt�se.<br> 
	Figyelem csak helyes el�r�si �ttal m�k�dik!
	
	\example setfontcolor_00.c	
	Fontok sz�n�nek megv�ltoztat�sa.<br> 
	
	
	\example changefont_00.c	
	Fontf�szlet v�lt�sa<br> 
	
*/

/**	FONTos P�LD�K

	\example ksdl_kbhit_00.c	
	A tron j�t�k egy egyszer� verzi�ja<br>
	Itt nem lehet meghalni!
	
	
	\example getch_00.c	
	Beker egy bet�t �s annak �rt�k�t�l f�gg�en rajzol ki egy pontot.<br> 
	
	
*/

/**	GETPIXEL -es p�ld�k

	\example getpixel_00.c	
	Lem�soljuk egy t�glalap sz�n�t.
	
	
	\example getpixel_rgb_00.c	
	Fogjuk a LIGHTCYAN sz�n� t�glalpot �s elj�tszunk a sz�neivel. 
	
	
*/
/**	GETPIXEL -es p�ld�k

	\example getx_gety_00.c
	A getx() gety() f�ggv�nyek segts�g�vel k�nnyen poz�cion�lunk a k�perny�n.
	
	
*/

/**	Egerkezeles -es p�ld�k

	\example mouse_00.c
	Kiirjuk a kepernyore az eger strukt�ra adatait.
	
	\example mouse_01.c
	Tipikus gombos p�lda.
	
	
*/


	
/** \brief Ha a vezt�l�s erre a sorra ker�l akkor a megadott ideig v�rakozik a program
	\param ms a v�rkoz�s m�rt�ke
	\ingroup SDL
	\code	SDL_Delay(1000); // 1 masodpercig var a program
	\endcode
*/	
/** \brief Billenytz� nyomvatart�s�t im�telt billenty�zetle�t�snek �rz�kelhetj�k e fv seg�ts�g�vel
	\param delay h�ny ms-ig v�rjon miel�tt elkezdi ism�telt nyom�snak venni
	\param interval h�ny ms-k�nt vegye ism�telt lenyom�snak
	

	\ingroup SDL

	A gyors�t�shot a m�sodik param�tert kell cs�kkenteni.
	
	\code	SDL_EnableKeyRepeat(1,100); // alap�rtelmez�sben m�r meg van h�vva ezekkel a param�terekkel
	\endcode
*/
/** \brief Az ablak c�m�t �s ikonj�t lehet vele be�ll�tani

	

	\ingroup SDL

	Ha nem akarunk k�pet betenni akkor a m�sodik param�ter legyen NULL !
	
	\code	SDL_WM_SetCaption("Hello",NULL);
	\endcode
*/	
	
	/** \brief Az ablak c�m�t �s ikonj�t lehet vele be�ll�tani
	\param title a c�met tartamaz� string
	\param icon az ikont tartalmaz� k�p el�r�si �tja
	

	\ingroup SDL

	Ha nem akarunk k�pet betenni akkor a m�sodik param�ter legyen NULL !
	
	\code	SDL_WM_SetCaption("Hello",NULL);
	\endcode
*/

/** \brief Frissiteni lehet vele egy k�pet
	\param surface az az sdl felsz�n amit friss�teni akarunk (pl:screen)

	
	\ingroup SDL

	Friss�thetj�k vele az alapk�perny�egy ter�let�t, akkor ahsznos ha,<br>
	bar_nofrs() vagy paste() f�ggv�nyt hasn�ltunk!
	
	
	\code	SDL_UpdateRec(screen, 100, 100,100,100); // HASZN�LD �GY
	\endcode
*/

/** \brief K�perny� ter�letet tudunk friss�teni vele.
	\param surface az az sdl felsz�n amit friss�teni akarunk (pl:screen)
	\param x		a ter�let bal fels� sark�nak x koordin�t�ja a megjelen�t�fel�leten
	\param y		a ter�let bal fels� sark�nak y koordin�t�ja a megjelen�t�fel�leten
	\param w		a friss�tend� ter�let sz�less�ge
	\param h		a friss�tend� ter�let magass�ga
	\ingroup SDL

	Friss�thetj�k vele az alapk�perny�t, akkor ahsznos ha,<br>
	bar_nofrs() vagy paste() f�ggv�nyt hasn�ltunk!
	
	
	\code	SDL_Flip(scrren); // HASZN�LD �GY
	\endcode
*/


