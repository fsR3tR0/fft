#ifndef LIST_H_
#define LIST_H_

#include "include.h"

typedef struct list{
        u8 data_u8;
        float data_f;
        struct list *next;
}list;

typedef struct list_komplex{
        float data_Re;
        float data_Im;
        struct list_komplex *next;
}list_komplex;

//list *beszur_elore(list *l0, u8 mit1, float mit2);

#endif //LIST_H_
