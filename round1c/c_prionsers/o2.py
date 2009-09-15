#!/usr/bin/python

def readints(): return map(int, raw_input().strip().split())

def get():
    p, q = readints()
    id = [0] + readints() + [p + 1] # add two ends
    q += 1
    f = [[p * q] * q for x in xrange(q)]
    for x in xrange(q): f[x][x] = 0
    r = [[x] * q for x in xrange(q)]
    for len in xrange(2, q+1):
        for i in xrange(0, q-len+1):
            j = i+len-1
            #print i,j
            for k in xrange(r[i][j-1], r[i+1][j] + 1):
                if k < i or k >= j: continue
                t = f[i][k] + f[k+1][j] + id[j+1] - id[i] - 2
                if t < f[i][j]:
                    f[i][j] = t
                    r[i][j] = k
    return f[0][q-1]

n = input()
for x in xrange(1, n + 1):
    print "Case #%d: %d" % (x, get())
