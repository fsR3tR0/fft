#include "include.h"

typedef struct list{
        u8 data_u8;
        float data_f;
        struct list *next;
}list;

list *beszur_elore(list *l0, u8 mit1, float mit2);
void print_list(list *l0);
void list_free(list *l0);
void lenght_list(list *l0, u8 *var);

int main(int argc, char *argv[])
{
        list *l = NULL;
        printf("FFT lesz majd\n");
        u8 i = 1;
        float j = 1.2;
        u8 lght = 0;
	for(u8 i = 0; i < 10; i++){
		l = beszur_elore(l,i,j);
		j += 1.2;
	}
//	l = beszur_elore(l,2,3.4);
//	l = beszur_elore(l,3,0.0);
/*
        while(i < 12){
                l = beszur_elore(l,i,j);
                i++;
                j += 1.2;
        }
*/
        print_list(l);
        lenght_list(l, &lght);
        printf("Hossz: %d\n", lght);

        list_free(l);
        return 0;
}

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
        while(p != NULL){
          //      printf("{%d:%.2f}",p->data_u8, p->data_f);
		printf("{%d}",p->data_u8);
                p=p->next;
                printf("\n");
        }
}

void list_free(list *l0){
        list *p = l0;
        while(p != NULL){
                list *tmp = p->next;
                free(p);
                p = tmp;
	}
}