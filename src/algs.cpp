#include "path.h"
#include "algs.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

float randrange(float lower, float upper) {
    
    // std::cout << "generating rand, time=" << time(0) << std::endl;
    float length = upper - lower;
    float r = std::rand();
    // std::cout << "rand=" << r << std::endl;
    r = r / ((float)RAND_MAX);
    // std::cout << lower + (r * length) << std::endl;
    return lower + (r * length);
}
