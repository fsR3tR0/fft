#include <stdio.h>
#include <inttypes.h>
#include <sys/wait.h>

typedef uint8_t u8;
typedef unsigned char uch;

void csere(u8 *mit,u8 mire);
void sor();

int main()
{
	u8 a = 0, b_in = 0;

	printf("Ird be 'a'erteket\n ");
	scanf("%d",&a);
//	sor();
	printf("Az 'a' erteke: %d\n",a);
	printf("Ird be mire szeretned cserelni\n");
	scanf("%d",&b_in);
//	sor();
	printf("Beirt 'b' erteke: %d",b_in);
	sor();
	csere(&a,b_in);
//	sor();
	printf("Az 'a' erteke: %d, a 'b' erteke: %d",a,b_in);
	sor();
//	system('clear');
	return 0;
}

void csere(u8* mit, u8 mire){
	*mit = mire;
	printf("Csere megtortent!\n");
}

void sor(){
	printf("\n");
}
