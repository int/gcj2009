#!/usr/bin/python

def get():
    s = raw_input().strip()
    d = {}
    next = 0
    for x in s:
        if len(d) == 0: # start
            d[x] = 1
        elif x not in d:
            d[x] = next
            if next == 0:
                next += 2
            else:
                next += 1
    a = 0
    b = next
    if b < 2: # at least 2 base
        b = 2
    for x in s:
        a = a * b + d[x]
    return a

n = input()
for x in xrange(1, n + 1):
    print 'Case #%d: %d' % (x, get())
