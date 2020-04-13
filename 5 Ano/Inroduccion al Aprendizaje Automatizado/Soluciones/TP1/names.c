#include <stdio.h>  // printf
#include <stdlib.h> // system

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error de sintaxis. ");
        printf("Uso correcto: %s d nombre1 tipo1 ... nombred tipod.", argv[0]);
        return 1;
    }

    char cmd[200];

    // Imprimimos el encabezado.
    sprintf(cmd, "echo '0, 1\n'");
    system(cmd);

    // Imprimimos las variables.
    for (int i = 0; i < argc - 1; i += 2) {
        sprintf(cmd, "echo '%s: %s.'", argv[i + 1], argv[i + 2]);
        system(cmd);
    }

    return 0;
}
