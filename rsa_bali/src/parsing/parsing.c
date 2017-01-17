#include "bali_rand.h"
#include "parsing.h"
void encode(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz)  { //  returns block

    //    ENCODING
    unsigned char r1 = 0xFF;
    unsigned char r2 = 0xFF;
    unsigned long r = 0x00;
    //  0x00 28 51 46 <= block[i] < 0x40000057000016AC

    r = prand(rand());
    r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
    r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
    r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

    outblock[0] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[0] += (unsigned long long) (2 ^ r2) << (8 * 2); //    # START XOR with [2]
    outblock[0] += (unsigned long long) (0 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[0] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    r = prand(rand());
    r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
    r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
    r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

    outblock[1] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[1] += (unsigned long long) (blocksiz ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
    outblock[1] += (unsigned long long) (1 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[1] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    unsigned char i;
    for (i = 2; (i < blocksiz); i++) {

      r = prand(rand());
      r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
      r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
      r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

      outblock[i] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
      outblock[i] += (unsigned long long) (outmsg[i-2] ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
      outblock[i] += (unsigned long long) (i ^ r1) << (8 * 1); // block # XOR with [1]
      outblock[i] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    }
}

//    DECODING
//*
unsigned char decode(unsigned long long *inblock, unsigned char *inmsg) { //returns inmsg
  unsigned char numeration;
  numeration = ((inblock[1] & 0x00000000FF000000) >> (8 * 3)) ^ ((inblock[1] & 0x000000000000FF00) >> (8 * 1));

  if (numeration != 1) {
    return 0;
  }

  unsigned char blocksiz = (inblock[1] & 0x00000000000000FF) ^ ((inblock[1] & 0x0000000000FF0000) >> (8 * 2));

  //inblock[i] = (inblock[i] & 0x000000FF) ^ ((inblock[i] & 0x00FF0000) >> (8 * 2))
  unsigned char i;
  for (i = 2; (i < blocksiz); i++) {
    numeration = ((inblock[i] & 0x00000000FF000000) >> (8 * 3)) ^ ((inblock[i] & 0x000000000000FF00) >> (8 * 1));
    if (numeration != i) {
      return 0;
    }
    inmsg[i- 2] = (unsigned char) ((inblock[i] & 0x00000000000000FF) ^ ((inblock[i] & 0x0000000000FF0000) >> (8 * 2)));  //  BUG on second part inblock[1] should be inblock[i]?
  }
  return 1;
}

void encode_address(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz, unsigned char address)  { //  returns outblock

    //    ENCODING
    unsigned char r1 = 0xFF;
    unsigned char r2 = 0xFF;
    unsigned long r = 0x00;
    //  0x00 28 51 46 <= block[i] < 0x40000057000016AC

    r = prand(rand());
    r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
    r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
    r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

    outblock[0] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[0] += (unsigned long long) (2 ^ r2) << (8 * 2); //    # START XOR with [2]
    outblock[0] += (unsigned long long) (0 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[0] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    r = prand(rand());
    r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
    r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
    r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

    outblock[1] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[1] += (unsigned long long) (blocksiz ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
    outblock[1] += (unsigned long long) (1 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[1] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    r = prand(rand());
    r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
    r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
    r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

    outblock[2] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
    outblock[2] += (unsigned long long) (address ^ r2) << (8 * 2); //    address to be sent
    outblock[2] += (unsigned long long) (2 ^ r1) << (8 * 1); // block # XOR with [1]
    outblock[2] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    unsigned char i;
    for (i = 3; (i < blocksiz); i++) {

      r = prand(rand());
      r1 = (unsigned char) ((r & 0xFF000000) >> (8 * 3));
      r1 = (r1 % 255) + 1;  // making sure that r1 is greater than 1
      r2 = (unsigned char) ((r & 0x00FF0000) >> (8 * 2));

      outblock[i] = (unsigned long long) r1 << (8 * 3); //  01 + should be random [1]
      outblock[i] += (unsigned long long) (outmsg[i-3] ^ r2) << (8 * 2); //    # of blocks to come XOR with [2]
      outblock[i] += (unsigned long long) (i ^ r1) << (8 * 1); // block # XOR with [1]
      outblock[i] += (unsigned long long) r2 << (8 * 0); //  should be random [2]

    }
}

unsigned char decode_address(unsigned long long *inblock, unsigned char *inmsg) { //returns inmsg
  unsigned char numeration;
  numeration = ((inblock[1] & 0x00000000FF000000) >> (8 * 3)) ^ ((inblock[1] & 0x000000000000FF00) >> (8 * 1));

  if (numeration != 1) {
    return 0;
  }

  unsigned char blocksiz = (inblock[1] & 0x00000000000000FF) ^ ((inblock[1] & 0x0000000000FF0000) >> (8 * 2));

  unsigned char i;
  for (i = 3; (i < blocksiz); i++) {
    numeration = ((inblock[i] & 0x00000000FF000000) >> (8 * 3)) ^ ((inblock[i] & 0x000000000000FF00) >> (8 * 1));
    if (numeration != i) {
      return 0;
    }
    inmsg[i - 3] = (unsigned char) ((inblock[i] & 0x00000000000000FF) ^ ((inblock[i] & 0x0000000000FF0000) >> (8 * 2)));
  }
  return 1;
}
