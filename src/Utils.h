#ifndef UTILS_H_
#define UTILS_H_

// System includes
#include <cstdlib>
#include <ctime>

class Utils
{

public:
    static void initRamdom(void)
    {
        srand(time(NULL));
    }

    static int pickRandom(int min, int max)
    {
        return rand() % (max - min + 1) + min;
    }
};

#endif /* UTILS_H_ */
