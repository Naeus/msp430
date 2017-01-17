#ifndef __PARSING_H
#define __PARSING_H

void encode(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz);
unsigned char decode(unsigned long long *inblock, unsigned char *inmsg);
void encode_address(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz, unsigned char address);
unsigned char decode_address(unsigned long long *inblock, unsigned char *inmsg);

#endif /* __PARSING_H */
