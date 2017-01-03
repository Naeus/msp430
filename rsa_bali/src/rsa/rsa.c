#include "rsa.h"
#include "bali_math.h"
#include "32-bit_det_MR.h"
#include "parsing.h"

#define E 3

unsigned long long rsa_init(unsigned long long *d) {//  returns d and n
  unsigned long p = rsae3prime_gen();
  unsigned long q = rsae3prime_gen();
  unsigned long long n = (unsigned long long) p * q;
  unsigned long long totn = (unsigned long long) (p - 1) * (q - 1);
  long long s, t;
  d = gcdExtended(E, totn, &s, &t);

  if (s < 0) {
    d = s + totn;
  }

  else  {
    d = s;
  }
  return n;
}

void rsa_e(unsigned long long e, unsigned long long n, unsigned long long *outblock, unsigned char blocksiz, unsigned char *outmsg) {// returns outblock
  encode(outmsg, outblock, blocksiz);
  unsigned char i = 0;
  for (i=0; i<blocksiz; i++) {
    outblock[i] = PowMod(outblock[i], e, n);
  }
}

void rsa_d(unsigned long long d, unsigned long long n, unsigned long long *inblock, unsigned char blocksiz, unsigned char *inmsg) {// returns inmsg
  unsigned char i = 0;
  for (i=0; i<blocksiz; i++) {
    inblock[i] = PowMod(inblock[i], d, n);
  }
  decode(inblock, inmsg);
}
