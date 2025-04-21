def sum(m, n):
    # 确保 m < n
    if m > n:
        return "Error: m should be less than or equal to n"
    
    # 计算从 m 到 n 的所有整数的和
    total = 0
    for i in range(m, n + 1):
        total += i
    return total
