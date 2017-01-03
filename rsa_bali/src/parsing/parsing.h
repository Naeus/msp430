#ifndef __PARSING_H
#define __PARSING_H

void encode(unsigned char *outmsg, unsigned long long *outblock, unsigned char blocksiz);
unsigned char decode(unsigned long long *inblock, unsigned char *inmsg);

#endif /* __PARSING_H */
