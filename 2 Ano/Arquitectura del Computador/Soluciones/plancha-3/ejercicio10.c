// gcc ejercicio10.c guiwindows.c

#include <stdio.h>
#include "guindows.h"

task t1, t2, t3, taskmain;

void ft1(){
	double d;
	for(d=-1;;d+=0.001) {
		printf("t1: d=%f \t &d=%p\n", d, &d);
		TRANSFER(t1,t2);
	}
}

void ft2(){
	int i;
	for(i=0;i<10000;i++) {
		printf("t2: i=%d \t &i=%p\n", i, &i);
		TRANSFER(t2,t3);
	}
}

void ft3(){
	int i;
	for(i=0;i<5000;i++) {
		printf("t3: i=%d \t &i=%p\n", i, &i);
		TRANSFER(t3,t1);
	}
	TRANSFER(t3, taskmain);
}

int main(){
	stack(t1,ft1);
	stack(t2,ft2);
	stack(t3,ft3);
	TRANSFER(taskmain,t1);
	printf("\nLas pilas fueron creadas en el orden: t1, t2, t3.\n");
	printf("La direccion mas alta la tiene t3, luego t2 y finalmente t1.\n");
	printf("La diferencia entre cada pila es aproximadamente el tamaño de pila fijado.\n");
	return 0;
}
