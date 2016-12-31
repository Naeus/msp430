#include <iostream>
using namespace std;



// AddMod returns a + b (mod m).
unsigned long long AddMod(unsigned long long a, unsigned long long b, unsigned long long m){
    a %= m;
    b %= m;
    if (a >= m-b) {
        return a - (m - b);
    }
    return a + b;
}

// SubMod returns a - b (mod m).
unsigned long long SubMod(unsigned long long a, unsigned long long b, unsigned long long m){
    a %= m;
    b %= m;
    if (a < b) {
        return a + (m - b);
    }
    return a - b;
}

// Lshift32Mod returns 2^32 a (mod m).
unsigned long long Lshift32Mod(unsigned long long a, unsigned long long m){

    unsigned long long m0;
    unsigned long long m1;
    unsigned long long q;
    unsigned long long q0;
    unsigned long long q1;
    unsigned long long p;
    unsigned long long p0;
    unsigned long long p1;
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
    m0 = m & 0xFFFFFFFF;
    m1 = m >> 32;
    q = a / (m1 + 1);
    q0 = q & 0xFFFFFFFF;
    q1 = q >> 32;
    p = q0 * m0;
    p0 = p & 0xFFFFFFFF;
    p1 = p >> 32;
    a -= p1 + q0*m1 + q1*m0 + ((q1 * m1) << 32);
    for (a > 0xFFFFFFFF) {
        p0 += m0;
        a -= m1;
    }
    return SubMod(a<<32, p0, m);
}

// MulMod returns a b (mod m).
unsigned long long MulMod(unsigned long long a, unsigned long long b, unsigned long long m){
    a0 = a & 0xFFFFFFFF;
    a1 = a >> 32;
    b0 = b & 0xFFFFFFFF;
    b1 = b >> 32;
    p0 = a0 * b0;
    p1 = AddMod(a0*b1, a1*b0, m);
    p2 = a1 * b1;
    return AddMod(p0, Lshift32Mod(AddMod(p1, Lshift32Mod(p2, m), m), m), m);
}

// PowMod returns a^b (mod m), where 0^0 = 1.
unsigned long long PowMod(unsigned long long a, unsigned long long b, unsigned long long m){
    r = 1 % m;
    for (b != 0) {
        if ((b & 1) != 0) {
            r = MulMod(r, a, m);
        }
        a = MulMod(a, a, m);
        b >>= 1;
    }
    return r;
}

/*
unsigned long long randUint64(){
    return uint64(rand.Uint32()) | (uint64(rand.Uint32()) << 32)
}
*/


int main(void){
    unsigned long long a = 2147483693;
    unsigned long long b = 2147483777;
    unsigned long long m = 4294967279 * 4294967291;
    unsigned long long c = 0;

    c = PowMod(a, b, m);

    /*

    var biga, bigb, bigm, actual, bigmul, expected big.Int
    for i := 1; true; i++ {
        a := randUint64()
        b := randUint64()
        m := randUint64()
        biga.SetUint64(a)
        bigb.SetUint64(b)
        bigm.SetUint64(m)
        actual.SetUint64(MulMod(a, b, m))
        bigmul.Mul(&biga, &bigb)
        expected.Mod(&bigmul, &bigm)
        if actual.Cmp(&expected) != 0 {
            panic(fmt.Sprintf("MulMod(%d, %d, %d): expected %s; got %s", a, b, m, expected.String(), actual.String()))
        }
        if i%10 == 0 {
            actual.SetUint64(PowMod(a, b, m))
            expected.Exp(&biga, &bigb, &bigm)
            if actual.Cmp(&expected) != 0 {
                panic(fmt.Sprintf("PowMod(%d, %d, %d): expected %s; got %s", a, b, m, expected.String(), actual.String()))
            }
        }
        if i%100000 == 0 {
            println(i)
        }
    }

    */
}
