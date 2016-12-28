#ifndef __32-BIT_DET_MR_H
#define __32-BIT_DET_MR_H

extern const unsigned short P16[6552];

unsigned char miller_rabin (unsigned long n);
unsigned long long pow_mod (unsigned long long a, unsigned long long d, unsigned long long n);
unsigned long powb2 (unsigned char e);
unsigned long rsae3prime_gen(void);
unsigned long long gcdExtended(unsigned long long e, unsigned long long totn, long long *d, long long *t);
unsigned char try_div(unsigned long n);

#endif /* __32-BIT_DET_MR_H */
