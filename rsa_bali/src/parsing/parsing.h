#ifndef __PARSING_H
#define __PARSING_H

void encode(unsigned char *outmsg, unsigned long *outblock, unsigned char blocksiz);
unsigned char decode(unsigned long *inblock, unsigned char *inmsg);

#endif /* __PARSING_H */
