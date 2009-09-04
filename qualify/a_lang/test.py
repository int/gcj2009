#!/usr/bin/python

import re

l, d, n = map(lambda x: int(x), raw_input().strip().split())
words = []
for x in xrange(d):
    words.append(raw_input().strip())
for x in xrange(n):
    p = raw_input().strip()
    a = re.compile('\(')
    p = a.sub('[', p)
    a = re.compile('\)')
    p = a.sub(']', p)
    p = '^' + p + '$'
    p = re.compile(p)
    count = 0
    for w in words:
        if p.match(w):
            count += 1
    print 'Case #%d: %d' % (x + 1, count)
