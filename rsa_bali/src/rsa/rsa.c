#include "bali_math.h"
#include "32-bit_det_MR.h"
#include "parsing.h"

#define E 3

void rsa_e(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz) {
  encode(outmsg, outblock, blocksiz);
  unsigned long p = rsae3prime_gen();
  unsigned long q = rsae3prime_gen();
  unsigned long long n = (unsigned long long) p * q;
  unsigned long long totn = (unsigned long long) (p - 1) * (q - 1);
  long long s, t;
  unsigned long long d = gcdExtended(E, totn, &s, &t);

  if (s < 0) {
    d = s + totn;
  }

  else  {
    d = s;
  }

  //ct[1] = PowMod(blocks[1], E, n);
  //*
  unsigned char i = 0;
  for (i=0; i<blocksiz; i++) {
    outblock[i] = PowMod(outblock[i], E, n);
    //pt[i] = PowMod(ct[i], d, n);
  }
}
