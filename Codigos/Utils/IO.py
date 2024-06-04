import sys
inputs = sys.stdin.read().splitlines() # make Python I/O faster

n = int(inputs[0])

ln = 1 # set current line = 0

for _ in range(n):
	a, b = map(int, inputs[ln].split())
	ln += 1
	print(a + b)