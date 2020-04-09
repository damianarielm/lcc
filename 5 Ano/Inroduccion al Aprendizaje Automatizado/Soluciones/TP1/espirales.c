#include <stdio.h>  // printf
#include <stdlib.h> // srand
#include <math.h>   // M_PI
#include <time.h>   // time
#include "randf.h"  // randf

float espiral1(float angulo) {
    return angulo / (4 * M_PI);
}

float espiral2(float angulo) {
    return (angulo + M_PI) / (4 * M_PI);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Error de sintaxis. ");
        printf("Uso correcto: %s n.\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int n = atoi(argv[1]);

    float radios[n];
    float angulos[n];
    FILE* r = fopen("radios", "w");
    FILE* a = fopen("angulos", "w");

    for (int i = 0; i < n; i++) {
        float radio  = randf(0, 1);
        float angulo = randf(0, 2 * M_PI);

        if (i < n / 2) {
            if ((espiral1(angulo) < radio && radio < espiral2(angulo))
            || (espiral1(angulo) + 0.5 < radio && radio < espiral2(angulo) + 0.5)) {
                radios[i] = radio;
                angulos[i] = angulo;
            }
            else i--;
        } else {
            if (!((espiral1(angulo) < radio && radio < espiral2(angulo))
            || (espiral1(angulo) + 0.5 < radio && radio < espiral2(angulo) + 0.5))) {
                radios[i] = radio;
                angulos[i] = angulo;
            }
            else i--;
        }
    }

    for (int i = 0; i < n; i++) fprintf(r, "%f\n", radios[i]);
    for (int i = 0; i < n; i++) fprintf(a, "%f\n", angulos[i]);

    return 0;
}
