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

def readints(): return map(int, raw_input().strip().split())

def get():
    p, q = readints()
    id = [0] + readints() + [p + 1] # add two ends
    @memo
    def f(i, j): # best of [i..j]
        if i == j: return 0
        return min(f(i, k) + f(k + 1, j) + id[j+1] - id[i] - 2 for k in xrange(i, j))
    return f(0, q)
        
n = input()
for x in xrange(1, n + 1):
    print "Case #%d: %d" % (x, get())
