//#include <gmpxx.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <omp.h>
#include <vector>

#define STEP_LIMIT 270 

typedef unsigned char radix_t; // should be smaller than unsigned int

class bigint {
  private:
    std::vector<radix_t> digits;
    radix_t radix;
  public:
    bigint(unsigned long long,radix_t);
    bigint& operator+=(bigint&);
    bigint& operator^(bigint&);
    operator std::string() const {
        std::stringstream base10digits;
        for (int i=digits.size();i>0;i--) {
            base10digits << digits[i];
        }
        return base10digits.str();
    }
};

bigint::bigint(unsigned long long i, radix_t r) : radix(r) { // I'll not hardcode radix to 10 for now...
    unsigned long long num = i;
    while (num>0) {
        this->digits.push_back(num%radix);
        num /= radix;
    }
    // these will end up LSD first, MSD last
}

bigint& bigint::operator+=(bigint& other) { // normal addition
    unsigned carry = 0,dig;
    for (size_t i=0; i<digits.size();i++) {
        dig = digits[i]+other.digits[i]+carry;
        digits[i] = dig%radix;
        carry = dig/radix;
    }
    return *this;
}


int main(int argc, char* argv[]) {
    
    bigint a(100,10);
    bigint b(300,10);

    std::cout<<std::string(a+=b)<<std::endl;
    
    /*
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
        if (steps<STEP_LIMIT+1 && steps>100) std::cout<<i+init<<","<<steps<<std::endl;
    }
    */
    return 0;
}
