a, b = map(int, input().split())
sum_square = 0
if a <= b:
    for num in range(a, b + 1):
        sum_square += num ** 2
else:
    for num in range(b, a + 1):
        sum_square += num ** 2
print(sum_square)