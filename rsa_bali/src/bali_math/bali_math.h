#ifndef __BALI_MATH_H
#define __BALI_MATH_H

unsigned long long pow_mod (unsigned long long a, unsigned long long d, unsigned long long n);
unsigned long powb2 (unsigned char e);
unsigned long long gcdExtended(unsigned long long e, unsigned long long totn, long long *d, long long *t);
unsigned long long AddMod(unsigned long long a, unsigned long long b, unsigned long long m);
unsigned long long SubMod(unsigned long long a, unsigned long long b, unsigned long long m);
unsigned long long Lshift32Mod(unsigned long long a, unsigned long long m);
unsigned long long MulMod(unsigned long long a, unsigned long long b, unsigned long long m);
unsigned long long PowMod(unsigned long long a, unsigned long long b, unsigned long long m);

#endif /* __BALI_MATH_H */
