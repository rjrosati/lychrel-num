#include "bigint.h"
#include <sstream>

bigint::operator std::string() const {
    std::stringstream base10digits;
    for (int i=digits.size()-1;i>=0;i--) {
        base10digits << (int)digits[i];
    }
    return base10digits.str();
}

bigint::bigint(unsigned long long i, radix_t r) : radix(r) { // I'll not hardcode radix to 10 for now...
    unsigned long long num = i;
    while (num>0) {
        this->digits.push_back(num%radix);
        num /= radix;
    }
    // these will end up LSD first, MSD last
}
bigint& bigint::operator++() { // reverse and add-to-self addition
    radix_t carry = 0,dig;
    size_t len = digits.size();
    std::vector<radix_t> result; result.resize(len);

    for (size_t i=0; i<len ;i++) {
        dig = digits[i]+digits[len-1-i]+carry;
        result[i] = dig%radix;
        carry = dig/radix;
    }
    if (carry !=0) {
       result.push_back(carry);
    }
    digits = result;
    return *this;
}

bigint& bigint::operator=(bigint& other) {
    digits = other.digits;
    return *this;
}

bigint bigint::operator+(int num) {
    radix_t carry = 0,dig;
    size_t len = digits.size();
    bigint result(num,radix);
    result.digits.resize(len);

    for (size_t i=0; i<len ;i++) {
        dig = digits[i]+result.digits[i]+carry;
        result.digits[i] = dig%radix;
        carry = dig/radix;
    }
    if (carry !=0) {
       result.digits.push_back(carry);
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
