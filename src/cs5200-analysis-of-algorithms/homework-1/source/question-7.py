def gcd2(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, s, t = gcd2(b % a, a)
        return [g, t - (b // a) * s, s]