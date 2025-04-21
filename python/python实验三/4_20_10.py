while True:
    line = input()
    a, b = map(int, line.split())
    if a == 0 and b == 0:
        break
    print(a + b)
