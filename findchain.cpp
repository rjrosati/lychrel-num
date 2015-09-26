#include <gmpxx.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <omp.h>


#define STEP_LIMIT 270 

int main(int argc, char* argv[]) {
    mpz_class x = 0, y, steps = 0,init;
    
    init.set_str(argv[1],10);

   #pragma omp parallel for shared(init) private(x,y,steps)
    for (int i=0; i<1000000; i++) {
        x = i+init;
        std::string x_str = x.get_str();
        std::reverse(x_str.begin(), x_str.end());
        steps = 0;
        while (true) {
            y.set_str(x_str,10);
            if (x == y) break;
            // std::cout<<x<<","<<steps<<std::endl;
            x += y;
            if (steps > STEP_LIMIT) break;
            steps++;
            x_str = x.get_str();
            std::reverse(x_str.begin(), x_str.end());
        }
        if (steps<STEP_LIMIT+1 && steps>100) std::cout<<i+init<<","<<steps<<","<<x_str<<std::endl;
    }

    return 0;
}
