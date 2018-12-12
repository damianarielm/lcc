// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>

#include <stdio.h> // printf, perror
#include <stdlib.h> // exit
#include <unistd.h> // read, write, close
#include <arpa/inet.h> // sockaddr_in, socket, PF_INET, SOCK_STREAM, AF_INET, INADDR_ANY, htons, bind, listen, accept, inet_ntoa, ntohs 

#define PORT 5000 // /etc/services
typedef struct sockaddr *sad;

void error(char* s) { exit((perror(s),-1)); }

void main() {
	int sock, sock1;
	struct sockaddr_in sin, sin1;
	char linea[1024];
	int cuanto;
	socklen_t L;
    
	// Creamos el socket de conexion
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) error("Error en la creacion del socket.\n");
    
	// Direccion
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = INADDR_ANY;
    
	// Asignamos la direccion al socket
	if (bind(sock, (sad) &sin, sizeof(sin)) < 0) error("Error al asignar la direccion al socket.\n");
    
	// Avisamos que escucharemos con sock
	if (listen(sock,5) < 0) error("Error al escuchar en el socket.\n");
    
	// Esperamos conexion
	L = sizeof(sin1);
	if ((sock1 = accept(sock, (sad) &sin1, &L)) < 0) error("Error esperandio la conexion.\n");
	printf("Mensaje de (%s:%d)\n", inet_ntoa(sin1.sin_addr), ntohs(sin1.sin_port));
    
	// Tratamos la sesion
	if ((cuanto = read(sock1, linea, sizeof(linea))) < 0) error("Error de lectura.\n");
	linea[cuanto] = 0;
	printf(">> %s\n", linea);
	linea[0]++;
	if (write(sock1, linea, cuanto) < 0) error("Error de escritura.\n");
    
	// Cerramos la sesion
	close(sock1);
    
	 // Cerramos la conexion
	close(sock);
}
