//#include <gmpxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
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
    bigint& operator+=(bigint&); // normal additon
    bigint& operator++(); // base-10-digit-reversed addition
    operator std::string() const {
        std::stringstream base10digits;
        for (int i=digits.size()-1;i>=0;i--) {
            base10digits << (int)digits[i];
        }
        return base10digits.str();
    }
    bigint& operator=(bigint&);
    bigint operator+(int);
    bool is_palindrome();
};

bigint::bigint(unsigned long long i, radix_t r) : radix(r) { // I'll not hardcode radix to 10 for now...
    unsigned long long num = i;
    while (num>0) {
        this->digits.push_back(num%radix);
        num /= radix;
    }
    // these will end up LSD first, MSD last
}
bigint& bigint::operator++() { // reverse and add-to-self addition
    unsigned carry = 0,dig;
    size_t len = digits.size();
    std::vector<radix_t> result; result.resize(len);

    for (size_t i=0; i<len ;i++) {
        dig = digits[i]+digits[len-1-i]+carry;
        result[i] = dig%radix;
        carry = dig/radix;
    }
    if (carry !=0) {
       result.push_back((radix_t)carry);
    }
    digits = result;
    return *this;
}

bigint& bigint::operator=(bigint& other) {
    digits = other.digits;
    return *this;
}

bigint bigint::operator+(int num) { // assumes num < bigint
    unsigned carry = 0,dig;
    size_t len = digits.size();
    bigint result(num,radix);
    result.digits.resize(len);

    for (size_t i=0; i<len ;i++) {
        dig = digits[i]+result.digits[i]+carry;
        result.digits[i] = dig%radix;
        carry = dig/radix;
    }
    if (carry !=0) {
       result.digits.push_back((radix_t)carry);
    }
    return result;
}

bool bigint::is_palindrome() {
    size_t len = digits.size();
    for (size_t i=0; i < len/2+1; i++) {
        if (digits[i]!=digits[len-1-i]) return false;
    }
    return true;
}


int main(int argc, char* argv[]) {
    
    bigint init(std::stoull(argv[1]),10);
    int steps = 0;

    #pragma omp parallel for shared(init) private(steps)
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
