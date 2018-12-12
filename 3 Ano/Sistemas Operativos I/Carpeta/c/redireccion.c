#include <unistd.h> // write, close, dup
#include <fcntl.h> // open. O_WRONLY, O_CREAT, O_TRUNC 

void f() { write(1, "Hola mundo\n", 11); }

void redireccion() {
	int archivo = open("temp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	close(1); // Cierra la salida standard
	dup(archivo); // Duplica el descriptor en el primer lugar disponible
	close(archivo);
}

void main() {
	redireccion();
	f();
}
