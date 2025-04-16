def print_pattern(n):
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            print(f"{min(i, j):4}", end="")
        print()

# 读取输入
n = int(input())

# 调用函数输出图案
print_pattern(n)
