

#include <stdlib.h>
#include <stdio.h>
 
 
/* a lista egy eleme: */
typedef struct ListaElem {
    int adat;               /* Maga az adat */
	float n;
    struct ListaElem *kov;  /* Pointer a következő elemre */
} ListaElem;
 
 
/* lista kiírása kiírása */
void lista_kiir(ListaElem *eleje) {
    ListaElem *p;
    for (p = eleje; p != NULL; p = p->kov)
        printf("%d ", p->adat);
    printf("\n");
}
 
/* Lista felszabadítása */
void lista_free(ListaElem *eleje) {
    ListaElem *p = eleje;
    /* Végigmegyünk a listán */
    while (p != NULL) {
        /* Ha csak simán azt mondanánk hogy free(p); akkor elveszne a következő */
        /* elemre a pointer, nem mondhatnánk azt hogy: p=p->kov;  */
        ListaElem *tmp = p->kov; /* Ezért eltároljuk a következő elem címét */
        free(p); /* Most már törölhetjük az adott elemet */
        p = tmp; /* Folytassuk a következőtől */
    }
}
 
/* Adat beszúrása a lista elejére */
ListaElem *lista_elejere_beszur(ListaElem *eleje, int mit, float mit2) {
    ListaElem *uj = (ListaElem *) malloc(sizeof(ListaElem)); /* Új elem */
    uj->adat = mit; /* Adat bemásolása */
	uj->n = mit2;   
 uj->kov = eleje; /* Az új elem után jön az eddigi lista (akkor is jó, ha üres volt eredetileg) */
    return uj; /* A lista eleje ez az elem lesz */
}
 
/* Adat beszúrása a lista végére */
ListaElem *lista_vegere_beszur(ListaElem *eleje, int mit) {
    ListaElem *uj = (ListaElem *) malloc(sizeof(ListaElem)); /* Új elem */
 
    uj->adat = mit; /* Adat bemásolása */
    uj->kov = NULL; /* Ez lesz a lista vége, ezért NULL a következő elem */
    if (eleje == NULL) {
        return uj; /* Ha üres a lista, akkor ez lesz az eleje */
    } else {
        ListaElem *p = eleje; /* Elmegyünk az utolsó elemig (aminek a pointere NULL pointer) */
        while (p->kov != NULL) p = p->kov;
        p->kov = uj; /* És hozzáfűzzük */
        return eleje;
    }
}
 
/* Lista hosszának kiszámolása */
int lista_hossz(ListaElem *eleje) {
    /* Végigmegyünk a listán és számoljuk az elemeket */
    int hossz = 0;
    ListaElem *p = eleje;
    while (p != NULL) {
        hossz++;
        p = p->kov;
    }
    return hossz;
}
 
/* Keresés a listában */
ListaElem *lista_keres(ListaElem *eleje, int mit) {
    ListaElem *p;
    for (p = eleje; p != NULL; p = p->kov)
        if (p->adat == mit)
            return p;
    return NULL;
}
 
 
/* főprogram */
int main(void) {
    ListaElem *eleje = NULL;

	eleje = lista_elejere_beszur(eleje,2,2.3);
	eleje = lista_elejere_beszur(eleje,3,2.4);
/* 
    eleje = lista_vegere_beszur(eleje, 66);
    eleje = lista_elejere_beszur(eleje, 55);
    eleje = lista_vegere_beszur(eleje, 77);
    eleje = lista_elejere_beszur(eleje, 44);
    eleje = lista_elejere_beszur(eleje, 33);
    eleje = lista_elejere_beszur(eleje, 22);
    eleje = lista_elejere_beszur(eleje, 11);
*/  
  lista_kiir(eleje);
    printf("\nHossz: %d\n", lista_hossz(eleje));
 
    ListaElem *tal = lista_keres(eleje, 44);
    if (tal != NULL)
        printf("%d\n", tal->adat);
    else
        printf("nincs ilyen\n");
 
    lista_free(eleje);
 
    return 0;
}

