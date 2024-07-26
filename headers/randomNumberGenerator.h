#ifndef RANDOM_NUM_H
#define RANDOM_NUM_H
#include <sys/types.h> // getpid
#include <unistd.h>
using namespace std;

class RandomNumberGenerator {
    public:
        unsigned seed;
        static int randomNumber(int low, int high);

        RandomNumberGenerator(int seed = getpid());
        virtual ~RandomNumberGenerator();
};

#endif
