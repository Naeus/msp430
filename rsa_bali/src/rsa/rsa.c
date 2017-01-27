#include "rsa.h"
#include "bali_math.h"
#include "32-bit_det_MR.h"
#include "parsing.h"
#include "bali_rand.h"

unsigned long long rsa_init(unsigned char e, unsigned long long *d) {//  returns d and n
  unsigned long p = rsae3prime_gen();
  unsigned long q = rsae3prime_gen();

  while (p == q) {  //  In order to prevent having both primes equal, this is very unlikely but possible
    p = rsae3prime_gen();   //  Change either one of the primes, p in this case
  }

  unsigned long long n = (unsigned long long) p * q;  //  casting may be unnecessary
  unsigned long long totn = (unsigned long long) (p - 1) * (q - 1);  //  casting may be unnecessary
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

unsigned long rsae3prime_gen(void) {
  unsigned long n = 0;
  while (!(miller_rabin(n))) {//Miller-Rabin test
  //while (!(try_div(n))) {//Trial Division test with predetermined primes < 16 bit DOESN'T FIT
    n = 6 * (357913942 + (prand(rand()) % 357913941)) - 1; //   357913941 = 715827883 - 357913942, the values to fit 32-bit exactly
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
