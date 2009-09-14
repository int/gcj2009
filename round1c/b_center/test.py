#!/usr/bin/python

from math import sqrt

def get():
    n = input()
    num = [0] * 6
    for i in xrange(n):
        s = raw_input().strip().split()
        num = map(lambda x: num[x] + int(s[x]), xrange(6))
    x, y, z, vx, vy, vz = num
    a = vx**2 + vy**2 + vz**2
    b = 2 * (vx * x + vy * y + vz * z)
    c = x**2 + y**2 + z**2 # >= 0
    t = 0 # a is zero --> vx vy vz all are zeros --> b is zero
    if a: t = -b / (2.0 * a)
    if t < 0: t = 0
    d = a * t**2 + b * t + c
    if d < 0: d = 0
    return (sqrt(d) / n, t)

n = input()
for x in xrange(1, n + 1):
    d, t = get()
    print "Case #%d: %.8f %.8f" % (x, d, t)
