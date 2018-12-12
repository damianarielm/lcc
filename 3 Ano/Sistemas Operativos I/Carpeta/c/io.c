#include <stdio.h> // printf
#include <unistd.h> // write, lseek, close
#include <fcntl.h> // open, O_RDWR, O_CREAT, O_TRUNC

void main() {
	int archivo, i;
	double d;
	archivo = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0666);

	// Escribe 10 dobles en temp
	for (i = d = 0; i < 10; i++, d += 0.1) write(archivo, &d, sizeof(d));

	// Lee los 10 dobles al reves
	lseek(archivo, -sizeof(d), SEEK_END);
	for (i = 0; i < 10; i++) {
		read(archivo, &d, sizeof(d));
		printf("%f\n", d);
		lseek(archivo, -2*sizeof(d), SEEK_CUR);
	}

	close(archivo);
}
