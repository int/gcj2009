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

def readints(): return map(lambda x: int(x), raw_input().strip().split())

def get():
    p, q = readints()
    id = [0] + readints() + [p + 1] # add two ends
    seg = [id[x] - id[x - 1] - 1 for x in xrange(1, len(id))]
    @memo
    def s(i, j):
        if i == j: return seg[i]
        return seg[i] + s(i + 1, j) + 1
    @memo
    def f(i, j): # best of [i..j]
        if i == j: return 0
        return min(f(i, k) + f(k + 1, j) + s(i, j) - 1 for k in xrange(i, j))
    return f(0, len(seg) - 1)
        
n = input()
for x in xrange(1, n + 1):
    print "Case #%d: %d" % (x, get())
