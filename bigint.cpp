#include "bigint.h"
#include <sstream>
constexpr radix_t bigint::m10[20];
constexpr radix_t bigint::q10[20];

bigint::operator std::string() const {
    std::stringstream base10digits;
    for (int i=digits.size()-1;i>=0;i--) {
        base10digits <<(int)digits[i];
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

void bigint::remove_leading_zero() {
    if (digits[digits.size()-1] == 0 ) {
        digits.erase(digits.end() - 1);
    }
}

void bigint::resolve_carries() {
    // sometimes I might want to improperly set a digit > radix for convenience
    // this function will resolve these pending carries
    radix_t carry=0;
    for (size_t i=0; i<digits.size(); i++) {
        digits[i] += carry;
        carry = digits[i]/radix;
        digits[i] %= radix;
    }
    while (carry != 0) {
        digits.push_back(carry%radix);
        carry /= radix;
    } // just in case I need more than one extra digit.
}

bigint& bigint::operator=(const bigint& other) {
    digits = other.digits;
    return *this;
}

bigint bigint::operator+(int num) {
    bigint result = bigint(num,radix);
    return *this+result;
}

bigint bigint::operator+(const bigint& other) {
    const bigint *big   = digits.size() > other.digits.size() ? this : &other;
    const bigint *small = digits.size() > other.digits.size() ? &other : this;
    bigint result = *big;

    radix_t dig,carry = 0;
    for (size_t i=0; i<small->digits.size();i++) {
        dig = big->digits[i] + small->digits[i]+carry;
        result.digits[i] = dig%radix;
        carry = dig/radix;
    }
    for (size_t j = small->digits.size(); j < big->digits.size(); j++) {
        dig = big->digits[j] + carry;
        result.digits[j] = dig%radix;
        carry = dig/radix;
        if (carry == 0)
            break;
        // rest of result's digits are already big's
    }
    if (carry != 0)
        result.digits.push_back(carry);

    return result;
}


