#include <stdio.h>
#include <inttypes.h>

typedef uint8_t u8;

typedef struct{
	u8 db;
	float netto;
	float afa;
}data_0;

void beolvas(data_0 *in);
void brutto(float *ertek,data_0 adat);
void summ(float * summ_data, data_0 adat);

int main(int argc, int *argv[])
{
	data_0 adatka;
	float brutto_data = 0.0;
	float var_summ = 0;

	printf("Ird be az adatokat space-cel elvalasztva(db,ar,afa)\n");
	beolvas(&adatka);
//	scanf("%d %f %f",&adatka.db, &adatka.netto, &adatka.afa);
//	printf("Beirt adatok: %d, %.2f, %.2f\n",adatka.db,adatka.netto,adatka.afa);

	brutto(&brutto_data,adatka);
	printf("Brutto ertek: %.2f\n",brutto_data);
	summ(&var_summ,adatka);
	printf("Ossz ertek(brutto): %.4f\n",var_summ);
	return 0;
}

void summ(float * summ_data,data_0 adat){
	float ertek = 0;
	float afa_valos = adat.afa * 100;
	ertek = adat.db*adat.netto*(1+afa_valos);
	*summ_data = ertek;
	printf("Kesz az atalakitas\n"); 
}

void beolvas(data_0 *in){
	data_0 be;
	scanf("%d %f %f",&be.db,&be.netto,&be.afa);
	printf("Kesz a beolvasas\n Beolvasott szamok: %d, %.2f, %.2f\n",be.db,be.netto,be.afa);
	*in = be;
}

void brutto(float *ertek, data_0 adat){
	float afa_valos = adat.afa/100.0;
	printf("Afa_valos: %f\n",afa_valos);
	printf("%f\n",afa_valos*adat.netto);
	*ertek = adat.netto+afa_valos*adat.netto;
	printf("Conversio kesz\n");
}
