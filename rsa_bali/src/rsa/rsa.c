#include "rsa.h"
#include "bali_math.h"
#include "32-bit_det_MR.h"
#include "parsing.h"

unsigned long long rsa_init(unsigned char e, unsigned long long *d) {//  returns d and n
  unsigned long p = rsae3prime_gen();
  unsigned long q = rsae3prime_gen();
  unsigned long long n = (unsigned long long) p * q;
  unsigned long long totn = (unsigned long long) (p - 1) * (q - 1);
  long long s, t;
  *d = gcdExtended(e, totn, &s, &t);

  if (s < 0) {
    *d = s + totn;
  }

  else  {
    *d = s;
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
  i = decode(inblock, inmsg); //  FIXED BUG inblock is being sent to decode as ull, but needs to be ul
}

void rsa_e_addr(unsigned long long e, unsigned long long n, unsigned long long *outblock, unsigned char address, unsigned char *outmsg) {// returns outblock
  encode_address(outmsg, outblock, address);
  unsigned char i = 0;
  for (i=0; i<4; i++) {
    outblock[i] = PowMod(outblock[i], e, n);
  }
}

void rsa_d_addr(unsigned long long d, unsigned long long n, unsigned long long *inblock, unsigned char *inmsg) {// returns inmsg
  unsigned char i = 0;
  for (i=0; i<4; i++) {
    inblock[i] = PowMod(inblock[i], d, n);
  }
  i = decode_address(inblock, inmsg); //  FIXED BUG inblock is being sent to decode as ull, but needs to be ul
}

//	rsa test
/*
unsigned char outmsg[] = "A ,\'.bz";
unsigned char blocksiz = sizeof(outmsg)/sizeof(outmsg[0]) + 2;
unsigned long long outblock[10] = {0};	//somehow disrupts blocksiz when greater than 125 in size
rsa_e(E, n, outblock, blocksiz, outmsg);

outmsg[0] = 65;
outmsg[1] = 65;
outmsg[2] = 65;
outmsg[3] = 65;
outmsg[4] = 65;
outmsg[5] = 65;
outmsg[6] = 65;
rsa_d(d, n, outblock, blocksiz, outmsg);
*/
//	rsa test end
