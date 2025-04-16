def find_3721_numbers(a, b):
    result = []
    for num in range(a, b + 1):
        if num % 3 == 2 and num % 7 == 1:
            result.append(num)
    return result

# 读取输入
T = int(input())
for _ in range(T):
    a, b = map(int, input().split())
    result = find_3721_numbers(a, b)
    if result:
        print(" ".join(map(str, result)))
    else:
        print("none")
