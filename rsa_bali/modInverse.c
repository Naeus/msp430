modInverse

function inverse(a, n)
    t := 0;     newt := 1;
    r := n;     newr := a;
    while newr ≠ 0
        quotient := r div newr
        (t, newt) := (newt, t - quotient * newt)
        (r, newr) := (newr, r - quotient * newr)
    if r > 1 then return "a is not invertible"
    if t < 0 then t := t + n
    return t
