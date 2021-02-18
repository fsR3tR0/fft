#ifndef LIST_H_
#define LIST_H_

#include "include.h"

typedef struct list{
        u8 data_u8;
        float data_f;
        struct list *next;
}list;

list *beszur_elore(list *l0, u8 mit1, float mit2);
list *beszur_hatra(list *l0, u8 mit1, float mit2);
void keres(list *l0, u8 mit1, float mit2);
void list_delete_last(list *l0);
void print_list(list *l0);
void list_free(list *l0);
void lenght_list(list *l0, u8 *var);

#endif //LIST_H_
