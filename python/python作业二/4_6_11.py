x, n = map(int, input().split())
for i in range(n + 1):
    print("pow({},{}) = {}".format(x, i, pow(x, i)))