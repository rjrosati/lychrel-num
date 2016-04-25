#ifndef _BIGINT_H
#define _BIGINT_H

#include <string>
#include <vector>
typedef unsigned char radix_t; // should be smaller than unsigned int

class bigint {
  private:
    std::vector<radix_t> digits;
    radix_t radix;
  public:
    bigint(unsigned long long,radix_t);
    bigint& operator+=(bigint&); // normal additon
    bigint& operator++(); // base-10-digit-reversed addition
    operator std::string() const;
    bigint& operator=(bigint&);
    bigint operator+(int);
    bool is_palindrome();
};
#endif
