#include <stdio.h>

void hello();

int main(){
	char in = 0;
	printf("Elsoke helo helo\n");
	printf("Irj be egy szamot!\n");
	scanf("%d",&in);
	printf("Szam: %d",in);
	
	hello();
	return 0;
}

void hello(){
	printf("Ez egy function!");
}
