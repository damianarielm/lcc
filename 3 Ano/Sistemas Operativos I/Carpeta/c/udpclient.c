// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

#include <stdio.h> // printf, 
#include <stdlib.h> // exit
#include <string.h> // NULL, strlen
#include <unistd.h> // close
#include <arpa/inet.h> // sockaddr_in, PF_INET, SOCK_DGRAM, AF_INET

#define PORT 5000 // /etc/services
typedef struct sockaddr *sad;

void error(char* s) { exit((perror(s),-1)); }

void main(int argc, char** argv) {
	int sock;
	struct sockaddr_in sin;
	char linea[1024];
	int cuanto;
    
	if (argc < 3) { printf("Parametros insuficientes. Uso correcto: %s ip mensaje.\n", argv[0]); exit(-1); }

	// Crea el socket
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) error("Error en la creacion del socket.\n");
    
	// Direccion
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	inet_aton(argv[1], &sin.sin_addr);
    
	// Mandamos y recibimos
	if (sendto(sock, argv[2], strlen(argv[2]), 0, (sad) &sin, sizeof(sin)) < 0) error("Error al enviar.\n");
	if ((cuanto = recvfrom(sock, linea, sizeof(linea), 0, NULL, NULL)) < 0) error("Error al recibir.\n");
	linea[cuanto] = 0;
    
	// Cerramos
	close(sock);
}
