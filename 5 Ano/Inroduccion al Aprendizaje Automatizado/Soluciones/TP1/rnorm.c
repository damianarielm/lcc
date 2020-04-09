#include <stdio.h>  // printf
#include <stdlib.h> // srand
#include <math.h>   // pow
#include <time.h>   // time
#include "randf.h"  // randf

float dnorm(float x, float mu, float sigma) {
    float max = 1 / (sqrt(2 * M_PI) * sigma);
    return max * exp((-1/(2 * pow(sigma, 2))) * pow(x - mu, 2));
}

int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Error de sintaxis. ");
        printf("Uso correcto: %s n mu sigma.\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int n = atoi(argv[1]);
    float mu = atof(argv[2]);
    float sigma = atof(argv[3]);

    for (int i = 0; i < n; i++) {
        float x = randf(mu - 5 * sigma, mu + 5 * sigma);
        float y = randf(0, dnorm(mu, mu, sigma));

        if (y < dnorm(x, mu, sigma)) printf("%f\n", x);
        else i--;
    }

    return 0;
}
