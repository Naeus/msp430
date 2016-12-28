// C program to demonstrate working of extended
// Euclidean Algorithm
#include <stdio.h>

// C function for extended Euclidean Algorithm
unsigned long long gcdExtended(unsigned long long e, unsigned long long totn, long long *s, long long *t)
{
    // Base Case
    if (e == 0)
    {
        *s = 0;
        *t = 1;
        return totn;
    }

    long long s1, t1; // To store results of recursive call
    unsigned long long gcd = gcdExtended(totn%e, e, &s1, &t1);

    // Update d and t using results of recursive
    // call
    *s = t1 - (totn/e) * s1;
    *t = s1;
    return gcd;
}

// Driver Program
int main()
{
    long long d, t;
    unsigned long long e = 3;
    unsigned long long p = 3143576531;
    unsigned long long q = 2645098367;
    unsigned long long totn = 0;
    totn = (p - 1) * (q - 1);
    //totn = 43;

    unsigned long long g = gcdExtended(e, totn, &d, &t);

    if (d < 0) {
      d += totn;
    }
    printf("gcd(%llu, %llu) = %llu, d = %lld, t = %lld\n\n\n",
           e, totn, g, d, t);
    return 0;
}
