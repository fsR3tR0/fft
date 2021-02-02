/*1.,
Structura 3 oldalaval megadott teglatest. Fuggveny ehhez, ami beolvas a
standard inputrol 3 ereteket, szokozokkel elvalasztva, terfat szamito fgv,
10 elemu tombot feltoltunk, kiirjuk aminek a terfogata kisebb mint 2.3
*/

#include <stdio.h>
#include <SDL.h>

typedef struct{
	float a, b, c;
} tegla;

void terfogat(tegla elem, float *eredmeny);
void beolvas(tegla *joker);

int main()
{
	float sum = 0;
	tegla bela;
//	bela.a = 3, bela.b = 3, bela.c = 3;
	printf("Irj be 3 adatot, float-t!\n");
	beolvas(&bela);
	terfogat(bela,&sum);
	printf("Az eredmeny: %.2f\n",sum);
	return 0;
}

void beolvas(tegla *joker){
	tegla tmp;
	scanf("%f %f %f",&tmp.a,&tmp.b,&tmp.c);
	printf("Beirt dolgok: %.2f, %.2f, %.2f \n",tmp.a,tmp.b,tmp.c);
	*joker = tmp;
//	return tmp;
	//na
}

void terfogat(tegla elem, float *eredmeny){
	*eredmeny = elem.a * elem.b * elem.c;
	printf("Kesz a conversio.\n");
}
