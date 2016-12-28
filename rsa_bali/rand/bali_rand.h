#ifndef __RAND_H
#define __RAND_H

/* LCG constants */
#define M 1664525                               // Multiplier
#define I 1013904223                                // Increment

unsigned long rand(void);
unsigned long prand(unsigned long state);

#endif /* __RAND_H */
