#ifndef __PARSING_H
#define __PARSING_H

void rng_2_uc(unsigned char *r1, unsigned char *r2);
void encode(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz);
unsigned char decode(unsigned long long *inblock, unsigned char *inmsg);
void encode_address(unsigned char *outmsg, unsigned long long *outblock, unsigned char address);
unsigned char decode_address(unsigned long long *inblock, unsigned char *inmsg);
unsigned long long bc8to64(unsigned char *arr);
void bc64to8(unsigned long long a, unsigned char *arr);

#endif /* __PARSING_H */
