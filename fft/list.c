#include "list.h"

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

void list_delete_last(list *l0){
        list *p = l0;

        while((p->next)->next != NULL){
                p = p->next;
        }
        list *fr = p->next;
        p->next = NULL;
        free(fr);
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
        if(db != 0)
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

