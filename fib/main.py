import sys

class Solver():
    def __init__(self):
        self._s = [0,1]
    def solve(self, n):
        if n >= len(self._s):
            for i in range(len(self._s), n+1):
                self._s.append(self._s[i-1] + self._s[i-2])
        return self._s[n]
            
s = Solver()
for line in sys.stdin:
    print(s.solve(int(line)))
