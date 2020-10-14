#ifndef KEYPRODUCING_H
#define KEYPRODUCING_H
#include "Int.h"

int first_prime_list[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                          31, 37, 41, 43, 47, 53, 59, 61, 67,
                          71, 73, 79, 83, 89, 97, 101, 103,
                          107, 109, 113, 127, 131, 137, 139,
                          149, 151, 157, 163, 167, 173, 179,
                          181, 191, 193, 197, 199, 211, 223,
                          227, 229, 233, 239, 241, 251, 257,
                          263, 269, 271, 277, 281, 283, 293,
                          307, 311, 313, 317, 331, 337, 347, 349};

Int *power(Int *x, Int *y, Int *p);

int miillerTest(Int *d, Int *n);

int isPrime(Int *n, int k);

int LowLevelTest(Int *num);

Int *BigPrime(int k);
#endif