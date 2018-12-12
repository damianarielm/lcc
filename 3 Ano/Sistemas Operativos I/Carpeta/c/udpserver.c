// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

#include <stdio.h> // printf
#include <stdlib.h> // exit
#include <unistd.h> // close
#include <arpa/inet.h> // sockaddr_in, sock_len, PF_INET, SOCK_DGRAM, AF_INET, INADDR_ANY

#define PORT 5000 /* /etc/services */
typedef struct sockaddr *sad;

void error(char* s) { exit((perror(s),-1)); }

int main() {
	int sock;
	struct sockaddr_in sin;
	char linea[1024];
	int cuanto;
	socklen_t L;
    
	// Creamos el socket de conexion
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) error("Error en la creacion del socket.\n");
    
	// Direccion
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = INADDR_ANY;
    
	// Asignamos la direccion al socket
	if (bind(sock, (sad) &sin, sizeof(sin)) < 0) error("Error al asignar la direccion al socket.\n");
	L = sizeof(sin);
	if ((cuanto = recvfrom(sock, linea, sizeof(linea), 0, (sad) &sin, &L)) < 0) error("Error al recibir.\n");
	linea[cuanto] = 0;
	printf("Mensaje de (%s:%d)\n>> %s\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port), linea);
	linea[0]++;
	if (sendto(sock, linea, cuanto, 0, (sad) &sin, L) < 0) error("Error al enviar.\n");
    
	// Cerramos
	close(sock);
}
