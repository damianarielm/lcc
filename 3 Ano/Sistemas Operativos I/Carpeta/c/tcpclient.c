// #include <sys/types.h>
// #include <sys/socket.h> 
// #include <netinet/in.h>

#include <stdio.h> // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // write, read, close
#include <string.h> // strlen
#include <arpa/inet.h> // socket, PF_INET_ SOCK_STREAM, AF_INET, connect, htons, inet_aton, sockaddr_in

#define PORT 5000 // /etc/services
typedef struct sockaddr* sad;

void error(char* s) { exit((perror(s),-1)); }

void main(int argc, char** argv) {
	int sock;
	struct sockaddr_in sin;
	char linea[1024];
	int cuanto;

	if (argc < 3) { printf("Parametros insuficientes. Uso correcto: %s ip mensaje\n", argv[0]); exit(-1); }
    
	// Crea el socket
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Error en la creacion del socket.\n");
    
	// Direccion
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	inet_aton(argv[1], &sin.sin_addr);
    
	// Conectamos
	if (connect(sock, (sad) &sin, sizeof(sin)) < 0) error("Error en la conexion.\n");
    
	// Sesion
	if (write(sock, argv[2], strlen(argv[2])) < 0) error ("Error en la escritura.\n");
	if ((cuanto = read(sock, linea, sizeof(linea))) < 0) error("Error en la lectura.\n");
    
	// Cerramos el socket
	close(sock);
}
