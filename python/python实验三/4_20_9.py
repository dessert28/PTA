import sys
input_data = sys.stdin.read()
lines = input_data.splitlines()
for line in lines:
    if line.strip():
        a, b = map(int, line.split())
    print(a + b)
