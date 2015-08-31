#include <gmpxx.h>
#include <stdio.h>
#include <iostream>

int main(void) {
    mpz_class x = 5001, y = 5002;
    std::cout<<x+y<<std::endl;
    return 0;
}
