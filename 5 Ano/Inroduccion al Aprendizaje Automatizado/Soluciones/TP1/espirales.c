#include <stdio.h>  // printf
#include <stdlib.h> // srand
#include <math.h>   // M_PI, pow
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

    int i = 0;
    while (i < n) {
        float x      = randf(-1.0, 1.0);
        float y      = randf(-1.0, 1.0);
        float radio  = sqrt(pow(x, 2) + pow(y, 2));
        float angulo = atan2(y, x);
        if (radio > 1) continue;

        int clase = i < n / 2;

        if ((espiral1(angulo) < radio && radio < espiral2(angulo))
        || (espiral1(angulo) + 0.5 < radio && radio < espiral2(angulo) + 0.5)
        || (espiral1(angulo) + 1.0 < radio && radio < espiral2(angulo) + 1.0)) {
            if (clase) { printf("%f, %f, %d\n", x, y, clase); i++; }
        } else if (!clase) {
            printf("%f, %f, %d\n", x, y, clase);
            i++;
        }
    }

    return 0;
}
