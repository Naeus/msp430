//*
//  a^d % n
unsigned long long pow_mod (unsigned long long a, unsigned long long d, unsigned long long n)
{
    unsigned long long result = 1;      // Initialize result

    a = a % n;  // Update a if it is more than or equal to n

    while (d > 0)
    {
        // If d is odd, multiply a with result
        if (d & 1)
            result = (result*a) % n;

        // d must be even now
        d = d>>1; // d = d/2
        a = (a*a) % n;
    }
    return result;
}
//*/

//  2^e under 32-bit, e>0
unsigned long powb2 (unsigned char e) {
  unsigned long result = 1;
  while (e != 0) {
    result = result<<1;
    e--;
  }
  return result;
}

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

// AddMod returns a + b (mod m).
unsigned long long AddMod(unsigned long long a, unsigned long long b, unsigned long long m) {
    a %= m;
    b %= m;
    if (a >= m-b) {
        return a - (m - b);
    }
    return a + b;
}

// SubMod returns a - b (mod m).
unsigned long long SubMod(unsigned long long a, unsigned long long b, unsigned long long m) {
    a %= m;
    b %= m;
    if (a < b) {
        return a + (m - b);
    }
    return a - b;
}

// Lshift32Mod returns 2^32 a (mod m).
unsigned long long Lshift32Mod(unsigned long long a, unsigned long long m) {
    a %= m;
    // Let A = 2^32 a. The desired result is A - q* m, where q* = [A/m].
    // Approximate q* from below by q = [A/(m+err)] for the err in (0, 2^32] such
    // that 2^32|m+err. The discrepancy is
    //
    // q* - q < A (1/m - 1/(m+err)) + 1 = A err/(m (m+err)) + 1
    //
    // A - q m = A - q* m + (q* - q) m < m + A err/(m+err) + m < 2 m + 2^64.
    //
    // We conclude that a handful of loop iterations suffice.
    unsigned long long m0 = m & 0xFFFFFFFF;
    unsigned long long m1 = m >> 32;
    unsigned long long q = a / (m1 + 1);
    unsigned long long q0 = q & 0xFFFFFFFF;
    unsigned long long q1 = q >> 32;
    unsigned long long p = q0 * m0;
    unsigned long long p0 = p & 0xFFFFFFFF;
    unsigned long long p1 = p >> 32;
    a -= p1 + q0*m1 + q1*m0 + ((q1 * m1) << 32);
    while (a > 0xFFFFFFFF) {
        p0 += m0;
        a -= m1;
    }
    return SubMod(a<<32, p0, m);
}

// MulMod returns a b (mod m).
unsigned long long MulMod(unsigned long long a, unsigned long long b, unsigned long long m) {

    unsigned long long a0 = a & 0xFFFFFFFF;
    unsigned long long a1 = a >> 32;
    unsigned long long b0 = b & 0xFFFFFFFF;
    unsigned long long b1 = b >> 32;
    unsigned long long p0 = a0 * b0;
    unsigned long long p1 = AddMod(a0*b1, a1*b0, m);
    unsigned long long p2 = a1 * b1;

    return AddMod(p0, Lshift32Mod(AddMod(p1, Lshift32Mod(p2, m), m), m), m);
}

// PowMod returns a^b (mod m), where 0^0 = 1.
unsigned long long PowMod(unsigned long long a, unsigned long long b, unsigned long long m) {
    unsigned long long r = 1 % m;
    while (b != 0) {
        if ((b & 1) != 0) {
            r = MulMod(r, a, m);
        }
        a = MulMod(a, a, m);
        b >>= 1;
    }
    return r;
}

/*    TEST
#include <stdio.h>

int main(void){
    unsigned long long a = 4294967189;
    unsigned long long b = 4294967231;
    unsigned long long m = 18446743979220271189;
    unsigned long long c = 0;

    c = PowMod(a, b, m);
    printf("%llu %llu %llu %llu", a, b, m, c);
}
*/
