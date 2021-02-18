#ifndef LIST_KOMPLEX_H_
#define LIST_KOMPLEX_H_

#include "include.h"

typedef struct list_komplex{
        float data_Re;
        float data_Im;
        struct list_komplex *next;
}list_komplex;

list_komplex *komp_beszur_elore(list_komplex *lk, float mit1, float mit2);
void print_komplex(list_komplex *lk);

#endif //LIST_KOMPLEX_H_
