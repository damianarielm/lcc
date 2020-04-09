#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void esquina(int n, int d, float c, float f, int x) {
    char cmd[200];

    sprintf(cmd,
            "(./rnorm %d %f %f && ./rnorm %d %f %f)" // Generamos los datos,
            "| pr -%d -t -s\", \""                   // los dividimos en columnas,
            "| sed 's/$/, %d/'",                     // y los clasificamos.
            n, f, c, n * (d - 1), 0.0, c, d, x);
    system(cmd);
}

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error de sintaxis. ");
        printf("Uso correcto: %s n d c.", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]) / 2;
    int d = atoi(argv[2]);
    float c = atof(argv[3]);

    esquina(n, d, c, 1.0, 1);
    esquina(n, d, c, -1.0, 0);

    return 0;
}
