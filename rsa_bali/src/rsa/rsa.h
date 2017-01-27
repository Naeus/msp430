#ifndef __RSA_H
#define __RSA_H

unsigned long long rsa_init(unsigned char e, unsigned long long *d);
unsigned long rsae3prime_gen(void);
void rsa_e(unsigned long long e, unsigned long long n, unsigned long long *outblock, unsigned char blocksiz, unsigned char *outmsg);
void rsa_d(unsigned long long d, unsigned long long n, unsigned long long *inblock, unsigned char blocksiz, unsigned char *inmsg);
void rsa_e_addr(unsigned long long e, unsigned long long n, unsigned long long *outblock, unsigned char address, unsigned char *outmsg);
void rsa_d_addr(unsigned long long d, unsigned long long n, unsigned long long *inblock, unsigned char *inmsg);

#endif /* __RSA_H */
