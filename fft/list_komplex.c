#include "list_komplex.h"

list_komplex *komp_beszur_elore(list_komplex *lk, float mit1, float mit2){
        list_komplex *uj = (list_komplex*)malloc(sizeof(list_komplex));
        uj -> data_Re = mit1;
        uj -> data_Im = mit2;
        uj -> next = lk;

        return uj;
}

void print_komplex(list_komplex *lk){

}

