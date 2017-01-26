#include <msp430g2553.h>
#include "rsa.h"
#include "parsing.h"

#define E 3
#define BLOCKSIZE 4

int main(void) {

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // set up bit 0 of P1 as output
  P1DIR = BIT0+BIT6;
  // intialize bit 0 of P1 to 0
  P1OUT = 0x00;

  //	test 64 to 8 and 8 to 64 bit conversion
  /*
  unsigned long long testconv = 0x0123456789ABCDEF;
  unsigned char testconvarr[8] = {0};
  testconv = 0xFEDCBA9876543210;
  bc64to8(testconv, testconvarr);
  testconv = bc8to64(testconvarr);
  */
  //	end of test


  //	rsa initialization
  unsigned long long d = 0;
  unsigned long long n = 0;
  n = rsa_init(E, &d);	//	returns n and d for a given e
  unsigned char key[9] = {0};
  key[0] = E;
  bc64to8(n, key+1);
  n = 0;
  n = bc8to64(key+1);


  //	rsa test

  //  encrypt
  unsigned char outmsg[] = ',';
  unsigned long long outblock[BLOCKSIZE] = {0};
  unsigned char address = 39;
  rsa_e_addr(E, n, outblock, address, outmsg);

  unsigned char i;
  unsigned char buff[32] = {0};
  for (i = 0; i < 4; i++) {
    bc64to8(outblock[i], (buff + (8 * i)));
  }

  //  decrypt

  outblock[0] = {0};
  outblock[1] = {0};
  outblock[2] = {0};
  outblock[3] = {0};
  for (i = 0; i < 4; i++) {
    outblock[i] = bc8to64((buff + (8 * i)));
  }

  outmsg[0] = 65;
  rsa_d_addr(d, n, outblock, outmsg);

  //	rsa test end


  // loop forever
  while (1) {


    // toggle bit 0 of P1
  	  P1OUT ^= BIT6;
	  if(1){
	  	  P1OUT ^= 0x01;
	  }
  }
}
