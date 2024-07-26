#include "headers/randomNumberGenerator.h"
#include <stdlib.h> // srand/rand

RandomNumberGenerator::RandomNumberGenerator(int seed) : seed{seed} {
    srand(seed);
}

RandomNumberGenerator::~RandomNumberGenerator() {}

int RandomNumberGenerator::randomNumber(int low, int high) {
    int range = high - low;
    return rand() % range + low;
}
