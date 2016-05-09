#ifndef _BIGINT_H
#define _BIGINT_H

#include <string>
#include <vector>
typedef unsigned char radix_t; // should be smaller than unsigned int

class bigint {
  private:
    radix_t radix;
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
