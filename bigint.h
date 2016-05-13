#ifndef _BIGINT_H
#define _BIGINT_H

#include <string>
#include <vector>
typedef unsigned char radix_t; // should be smaller than unsigned int
#define RADIX 10
class bigint {
  private:
    radix_t radix;
    constexpr static radix_t m10[20] = {0,1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9};
    constexpr static radix_t q10[20] = {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1};
    std::vector<radix_t> tmp;
  public:
    std::vector<radix_t> digits;
    bigint(unsigned long long,radix_t);
    bigint& operator+=(bigint&); // normal additon
    bigint& operator++(); // base-10-digit-reversed addition
    operator std::string() const;
    bigint& operator=(const bigint&);
    bigint operator+(const int);
    bigint operator+(const bigint&);
    bool is_palindrome();
    void resolve_carries();
    void remove_leading_zero();
};
#endif
