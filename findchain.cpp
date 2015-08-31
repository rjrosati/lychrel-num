#include <gmpxx.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>

int main(int argc, char* argv[]) {
    mpz_class x = 0, y, steps = 0;
    

    for (mpz_class i = 0; i < 1e9; i++) {
        x.set_str(argv[1],10);
        std::string x_str = argv[1];
        std::reverse(x_str.begin(), x_str.end());
        while (true) {
            y.set_str(x_str,10);
            if (x == y) break;
            std::cout<<x<<","<<steps<<std::endl;
            x += y;
            if (steps > 330) break;
            steps++;
            x_str = x.get_str();
            std::reverse(x_str.begin(), x_str.end());
        }
        if (steps>200) std::cout<<x<<","<<steps<<std::endl;
    }

    return 0;
}
