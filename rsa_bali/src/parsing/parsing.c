//#include <stdio.h>

//static const unsigned char outmsg[] = "ABCDEFGH";

unsigned long * encode(unsigned char *outmsg)  { //  returns block

    //    ENCODING
    unsigned char blocksiz = (sizeof(outmsg) - 1) + 2;   //  8 + 2 for initialization
    unsigned long long r1;
    unsigned long long r2;
    static unsigned long outblock[blocksiz];

    //  0x00 28 51 46 <= block < 0x40000057000016AC
    r1 = ((prand(rand()) >> (8 * 7)) % (256 - 1)) + 1;
    r2 = prand(rand()) >> (8 * 7);

    outblock[0] = (unsigned long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[0] += (unsigned long) (2 ^ r2) << (8 * 2); //    # START XOR with [2]
    outblock[0] += (unsigned long) (0 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[0] += (unsigned long) r2 << (8 * 0); //  should be random [2]

    r1 = ((prand(rand()) >> (8 * 7)) % (256 - 1)) + 1;
    r2 = prand(rand()) >> (8 * 7);

    outblock[1] = (unsigned long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[1] += (unsigned long) (blocksiz ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
    outblock[1] += (unsigned long) (1 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[1] += (unsigned long) r2 << (8 * 0); //  should be random [2]

    unsigned char i;
    for (i = 2; (i < blocksiz); i++) {
      r1 = ((prand(rand()) >> (8 * 7)) % (256 - 1)) + 1;
      r2 = prand(rand()) >> (8 * 7);

      outblock[i] = (unsigned long) r1 << (8 * 3); //  01 + should be random [1]
      outblock[i] += (unsigned long) (outmsg[i-2] ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
      outblock[i] += (unsigned long) (i ^ r1) << (8 * 1); // block # XOR with [1]
      outblock[i] += (unsigned long) r2 << (8 * 0); //  should be random [2]

    }

    return outblock;
}



//    DECODING
/*
unsigned char * decode(unsigned long *inmsg) {

  unsigned char blk[blocksiz];

  for (unsigned long i = 2; (i < blocksiz); i++) {

    blk[i] = (unsigned char) (((block[i] >> (8 * 2)) ^ block[i]) & 0x000000FF);
    //blk[i] += (unsigned char) (((block[i] << (8 * 2)) ^ block[i]) & 0x0000FF00);
    //printf("\n%u", blk[i]);

  }
}

*/

/*
printf("\n%c", outmsg[1]);
printf("\n%u", sizeof(outmsg));
printf("\n%lu", block[0]);
*/
