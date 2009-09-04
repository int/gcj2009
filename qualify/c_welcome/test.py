#!/usr/bin/python

import sys

sys.setrecursionlimit(500 * 30)
def memo(func):
    cache = {}
    def f(*args):
        if args in cache:
            return cache[args]
        r = func(*args)
        cache[args] = r
        return r
    return f

def doit(t):
    a = "welcome to code jam";
    b = raw_input().strip()
    @memo
    def f(n, m): 
        if n == -1: return 1
        if n < 0 or m < 0: return 0
        r = f(n, m - 1)
        if a[n] == b[m]:
            r += f(n - 1, m - 1)
            r %= 10000
        return r
    print 'Case #%d: %04d' % (t, f(len(a) - 1, len(b) - 1))

N = input()
for x in xrange(N):
    doit(x + 1)
