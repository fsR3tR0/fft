#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

typedef uint8_t u8;
typedef struct ListaElem{
	u8 data;
	struct ListaElem *kov;
}ListaElem;

ListaElem *elore_beszur(ListaElem *eleje, int data);
void lista_kiir(ListaElem *eleje);

int main(int argc, int *argv[])
{
	ListaElem *eleje = NULL;
	int in_number = 0;

	for(u8 i = 1; i<12; i++){
		eleje = elore_beszur(eleje,i);
	}

	lista_kiir(eleje);

	printf("Irja be mit szeretne hozza adni: ");
	scanf("%d",&in_number);
	printf("%d \n",in_number);

	eleje = elore_beszur(eleje,in_number);
	lista_kiir(eleje);

	return 0;
}

ListaElem *elore_beszur(ListaElem *eleje, int data){
	ListaElem *uj = (ListaElem*)malloc(sizeof(ListaElem));
	uj->data = data;
	uj->kov = eleje;
	return uj;
}

void lista_kiir(ListaElem *eleje){
	ListaElem *p;
	printf("Adatok:");
	for(p = eleje; p != NULL; p = p->kov){
		printf(" %d", p->data);
	}
	printf("\n");
}

