// #include <unistd.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <sys/select.h>
// #include <netinet/in.h> 
// #include <time.h>

#include <stdlib.h> // exit
#include <stdio.h> // printf, fprintf
#include <string.h> // memcpy, strlen
#include <arpa/inet.h> // socklen_t, PF_INET, SOCK_DGRAM, AF_INET, INADDR_MY, inet_aton, inet_ntoa

typedef struct sockaddr *sad;

void error(char *s) { exit((perror(s), -1)); }

#define MAX(x,y) ((x)>(y)?(x):(y))

void main(int argc, char **argv) {
	int sock, maxm1, cuanto;
	char linea[1024];
	struct sockaddr_in sin;
	socklen_t l;
	fd_set in, in_orig;

	if(argc != 2) { fprintf(stderr, "Uso: %s port\n", argv[0]); exit(-1); }

	// Creamos el socket
	if((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) error("Error en la creacion del socket.\n");

	// Direccion
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi(argv[1]));
	sin.sin_addr.s_addr = INADDR_ANY;

	// Asignamos la direccion al socket
	if(bind(sock, (sad) &sin, sizeof(sin)) < 0) error("Error al asignar la direccion al socket.\n");

	FD_ZERO(&in_orig);
	FD_SET(0, &in_orig);
	FD_SET(sock, &in_orig);
	maxm1 = MAX(0, sock) + 1;

	printf("Uso: puerto:ip:mensaje\n");
	while(1) { // Ciclo vital
		printf(">> "); fflush(stdout);
		memcpy(&in, &in_orig, sizeof(in));

		if(select(maxm1, &in, NULL, NULL, NULL) < 0) error("select");

		if(FD_ISSET(0, &in)) {
			char *p;
			fgets(linea, sizeof linea, stdin);
			linea[strlen(linea) - 1] = 0;

			// Suponemos que tiene la forma port:ipaddr:mensaje
			p = strtok(linea, ":");
			sin.sin_family = AF_INET;
			sin.sin_port = htons(atoi(p));
			p = strtok(NULL, ":");
			inet_aton(p, &sin.sin_addr);
			p = strtok(NULL, ":");

			if(sendto(sock, p, strlen(p), 0, (sad)&sin, sizeof(sin)) < 0) error("Error al enviar.\n");
		}

		if(FD_ISSET(sock, &in)) {
			l = sizeof(sin);
			if((cuanto = recvfrom(sock, linea, sizeof(linea), 0, (sad) &sin, &l)) < 0) error("Error al recibir.\n");
			linea[cuanto] = 0;
			printf("Mensaje de (%s:%d)\n>> [%s]\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), linea);
		}
	}
}
