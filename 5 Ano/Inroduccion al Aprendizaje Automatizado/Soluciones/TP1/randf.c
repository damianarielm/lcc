#include <stdlib.h>
#include "randf.h"

float randf(float min, float max) {
    float random = ((float) rand()) / (float) RAND_MAX;
    return min + random * (max - min);
}
