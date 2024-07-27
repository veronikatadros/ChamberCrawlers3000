#include "headers/randomNumberGenerator.h"
#include <stdlib.h> // srand/rand

RandomNumberGenerator::RandomNumberGenerator(unsigned int seed) : seed{seed} {
    srand(seed);
}

RandomNumberGenerator::~RandomNumberGenerator() {}

int RandomNumberGenerator::randomNumber(int low, int high) {
    int range = high - low;
    if (range == 0) return low;
    return rand() % range + low;
}
