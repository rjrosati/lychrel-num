//#include <gmpxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <omp.h>

#include "bigint.h"

#define STEP_LIMIT 290 


int main(int argc, char* argv[]) {
    
    bigint init(std::stoull(argv[1]),10);
    int steps = 0;

    #pragma omp parallel for shared(init) private(steps) schedule(dynamic,1000)
    for (int i=0; i<1000000; i++) {
        bigint x = init+i;
        steps = 0;
        while (true) {
            if (x.is_palindrome()) break;
            ++x; // go deeper, reverse add self
            if (steps > STEP_LIMIT) break;
            steps++;
        }
        if (steps<STEP_LIMIT+1 && steps > 100) std::cout<<std::string(init+i)<<","<<steps<<","<<std::string(x)<<std::endl;
    }
    
    return 0;
}
