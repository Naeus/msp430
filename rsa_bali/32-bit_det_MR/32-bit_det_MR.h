#ifndef __32-BIT_DET_MR_H
#define __32-BIT_DET_MR_H

unsigned char miller_rabin (unsigned long n);
unsigned long long pow_mod (unsigned long long a, unsigned long long d, unsigned long long n);
unsigned long powb2 (unsigned char e);
unsigned long rsaprime_gen (unsigned long e);
unsigned long gcd (unsigned long a, unsigned long b);

#endif /* __32-BIT_DET_MR_H */
