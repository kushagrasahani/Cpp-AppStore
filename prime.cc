///////////////////////////////////////////////////////////////////////////////
//
//  This implments a brute force method of determining the prime numbers
//  in a given range 1..n.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef PRIME_H_
#define PRIME_H_

#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>

bool is_prime(int num) {
  int limit, factor = 2;
  limit = (long) (sqrtf((float) num) + 0.5f);
  while ((factor <= limit) && (num % factor))
    factor++;
  return (factor > limit);
}

int get_first_prime(int k) {
  while (!is_prime(k))
    k++;
  return k;
}

#endif
