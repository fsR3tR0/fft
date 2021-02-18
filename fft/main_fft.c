#include "include.h"
#include "list.h"

int main(int argc, char *argv[])
{
        list *l = NULL;
        u8 i = 1;
        float j = 1.2;
        u8 lght = 0;
	FILE *fp;
	char buffer[100];
	u8 i_f = 0;

	fp = fopen("test.log","rt");
	if(fp == NULL){
		perror("Sikertelen file nyitas.\n");
		return -1;
	}else{
		printf("Sikeres file nyitas\n");
	}

	fgets(buffer,100,fp);
	while(buffer[i_f] != '\0'){
		printf("%c",buffer[i_f]);
		i_f++;
	}
	printf("%s", buffer);

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

	list_delete_last(l);
	print_list(l);
	lenght_list(l, &lght);
        printf("Hossz: %d\n", lght);

        list_free(l);
        return 0;
}
