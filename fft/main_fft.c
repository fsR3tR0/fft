#include "include.h"

typedef struct list{
        u8 data_u8;
        float data_f;
        struct list *next;
}list;

typedef struct list_komplex{
	float data_Re;
	float data_Im;
}list_komplex;

//list fuggvenyek
list *beszur_elore(list *l0, u8 mit1, float mit2);
list *beszur_hatra(list *l0, u8 mit1, float mit2);
void keres(list *l0, u8 mit1, float mit2);
void list_delete_last(list *l0);
void print_list(list *l0);
void list_free(list *l0);
void lenght_list(list *l0, u8 *var);

//list komplex fuggvenyek
list_komplex *komp_beszur_elore(list_komplex *lk, float mit1, float mit2);
void print_komplex(list_komplex *lk);

int main(int argc, char *argv[])
{
        list *l = NULL;
        u8 i = 1;
        float j = 1.2;
        u8 lght = 0;

	printf("=============\n");
        printf("FFT lesz majd\n");
	printf("=============\n\n");

	for(u8 i = 0; i < 10; i++){
		l = beszur_elore(l,i,j);
		j += 1.2;
	}
        print_list(l);
        lenght_list(l, &lght);
        printf("Hossz: %d\n", lght);

	j = 56.5;
	for(u8 i = 100; i > 90; i--){
		l = beszur_hatra(l, i, j);
		j += 2.4;
	}
        print_list(l);
        lenght_list(l, &lght);
        printf("Hossz: %d\n", lght);

	keres(l,200,23.4);

        list_free(l);
        return 0;
}

list_komplex *komp_beszur_elore(list_komplex *lk, float mit1, float mit2){

}
void print_komplex(list_komplex *lk);


list *beszur_hatra(list *l0, u8 mit1, float mit2){
	list* uj = (list*)malloc(sizeof(list));
	uj->data_u8 = mit1;
	uj->data_f = mit2;
	uj->next = NULL;

	if(l0 == NULL){
		return uj;
	}else{
		list *p = l0;
		while(p->next != NULL)
			p = p->next;
		p->next = uj;
		return l0;
	}
}

void keres(list *l0, u8 mit1, float mit2){
	list *p = l0;

	while(p != NULL){
		if(p->data_u8 == mit1){
			printf("Egesz benne van: %d\n", p->data_u8);
			p = NULL;
			break;
		}else{
			p = p->next;
		}
		if(p == NULL)
			printf("Nincs benne.\n");
	}
}

void list_delete_last(list *l0);

void lenght_list(list *l0, u8 *var){
        list *p = l0;
        u8 len = 0;
        while(p != NULL){
                len++;
                p = p->next;
        }
        *var = len;
}

list *beszur_elore(list *l0, u8 mit1, float mit2){
        list *uj = (list*)malloc(sizeof(list));
        uj->data_u8 = mit1;
	uj->data_f = mit2;
        uj->next = l0;

        return uj;
}

void print_list(list *l0){
        list *p = l0;
	u8 db = 0;
        while(p != NULL){
        	 printf("{%d:%.2f} ",p->data_u8, p->data_f);
		//printf("{%d}",p->data_u8);
                p=p->next;
       		db++;
		if(db == 5){
			printf("\n");
			db = 0;
		}
	 }
	printf("\n");
}

void list_free(list *l0){
        list *p = l0;
        while(p != NULL){
                list *tmp = p->next;
                free(p);
                p = tmp;
	}
}
