#!/usr/bin/python

def memo(func):
    cache = {}
    def f(*args):
        if args in cache:
            return cache[args]
        r = func(*args)
        cache[args] = r
        return r
    return f

# binomial coefficient aka choose(n, k)
@memo
def bino(n, k):
    if n < 0 or k > n: return 0
    if k == 0 or k == n: return 1
    return bino(n - 1, k - 1) + bino(n - 1, k)

def get():
    c, n = map(int, raw_input().strip().split())
    @memo
    def f(k): # expectation when already got k different kinds
        if k == c: return 0
        p = 1.0 / bino(c, n)
        e = 1.0 # this round
        x = 1 # x more new kinds
        while x <= n and k + x <= c:
            e += f(k + x) * bino(c - k, x) * bino(k, n - x) * p
            x += 1
        q = bino(k, n) * p # same state: no new more
        e /= 1 - q
        return e
    return f(0)

t = input()
for x in xrange(1, t + 1):
    print "Case #%d: %.8f" % (x, get())
