#ifndef __32-BIT_DET_MR_H
#define __32-BIT_DET_MR_H

extern const unsigned short P16[6552];

unsigned char miller_rabin (unsigned long n);
unsigned long rsae3prime_gen(void);
unsigned char try_div(unsigned long n);

#endif /* __32-BIT_DET_MR_H */
