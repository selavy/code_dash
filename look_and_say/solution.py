#!/usr/bin/env python3

import sys

def look_and_say(s):
    ct = []
    curr = []
    for c in s:
        if not curr:
            curr.append(c)
        elif c == curr[-1]:
            curr.append(c)
        else:
            ct.append(curr)
            curr = [c]
    ct.append(curr)
    t = ""
    for a in ct:
        t += str(len(a)) + a[0]
    return t

if __name__ == '__main__':
    for line in sys.stdin:
        s = line.split()
        n = int(s[1])
        s = s[0]
        if s == '0' and n == 0:
            sys.exit(0)
        for i in range(0, n):
            s = look_and_say(s)
        print(s)
