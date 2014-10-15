#!/usr/bin/env python3.4

import sys

curr = 1
total_wrong = 0
arithmetic = 0
geometric = 0

def check_geometric(series, n, line):
    global geometric
    global total_wrong
    global curr
    geometric = geometric + 1
    wrong = []
    for i in range(1, len(series)):
        c = series[i-1]*n
        if series[i] != c:
            wrong.append((series[i],c))
            series[i] = c
    nw = len(wrong)
    total_wrong += nw
    result = str(curr) + '. Line ' + str(line) + ': geometric: ' + str(len(series)) + ' terms, ' + str(nw)
    curr += 1
    if nw == 0:
        result += ' errors'
        print(result)
        return
    elif nw == 1:
        result += ' error'
    else:
        result += ' errors'

    result_sz = []
    for w in wrong:
        result_sz.append(' ' + str(w[0]) + ': ' + str(w[1]))
    result += ':'
    result += ','.join(result_sz)
    print(result)

def check_arithmetic(series, n, line):
    global arithmetic
    global total_wrong
    global curr
    arithmetic = arithmetic + 1
    wrong = []
    for i in range(1, len(series)):
        c = series[i-1] + n
        if series[i] != c:
            wrong.append((series[i],c))
            series[i] = c
    nw = len(wrong)
    total_wrong += nw
    result = str(curr) + '. Line ' + str(line) + ': arithmetic: ' + str(len(series)) + ' terms, ' + str(nw)
    curr += 1
    if nw == 0:
        result += ' errors'
        print(result)
        return
    elif nw == 1:
        result += ' error'
    else:
        result += ' errors'
    result_sz = []
    for w in wrong:
        result_sz.append(' ' + str(w[0]) + ': ' + str(w[1]))
    result += ':' + ','.join(result_sz)
    print(result)

def check_series(series, line):
    d1 = series[1] - series[0]
    d2 = series[2] - series[1]
    if d1 == d2:
        check_arithmetic(series, d1, line)
    m1 = series[1] / series[0]
    m2 = series[2] / series[1]
    if m1 == m2:
        check_geometric(series, int(m1), line)

if __name__ == '__main__':
    series = []
    num_sz = ""
    linenum = 0
    l = 0
    for line in sys.stdin:
        linenum += 1
        for c in line:
            if c.isdigit():
                if not series:
                    l = linenum
                num_sz += c
            elif c == '\n':
                continue
            elif num_sz:
                series.append(int(num_sz))
                num_sz = ""
            if c == '.':
                if not series:
                    continue
                check_series(series, l)
                num_sz = ""
                series = []

    print('Total of', arithmetic, 'arithmetic and', geometric, 'geometric progressions, total of', total_wrong,'errors.')

                
                


