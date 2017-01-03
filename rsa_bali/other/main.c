//project needs to have all /src files

#include <msp430g2553.h>
#include "rsa.h"

#define E 3

int main(void) {

  // stop watchdog timer
  WDTCTL = WDTPW | WDTHOLD;
  // set up bit 0 of P1 as output
  P1DIR = BIT0+BIT6;
  // intialize bit 0 of P1 to 0
  P1OUT = 0x00;

  unsigned char outmsg[] = "A ,\'.bz";
  unsigned char blocksiz = sizeof(outmsg)/sizeof(outmsg[0]) + 2;
  unsigned long long outblock[10] = {0};	//somehow disrupts blocksiz when greater than 125 in size
  unsigned long long d = 0;
  unsigned long long n = 0;
  n = rsa_init(&d);
  rsa_e(E, n, outblock, blocksiz, outmsg);
  rsa_d(d, n, outblock, blocksiz, outmsg);

  // loop forever
  while (1) {


    // toggle bit 0 of P1
  	  P1OUT ^= BIT6;
	  if(1){
	  	  P1OUT ^= 0x01;
	  }
  }
}
