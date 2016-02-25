#include "math.h"
#include <cstdlib>


double rnd(double min, double max) {
    return min + double(std::rand()) / RAND_MAX * (max - min);
}

int rand(int max, int min) {
    if (max - min == 0) { return min; }
    return min + std::rand() % (max - min);
}

