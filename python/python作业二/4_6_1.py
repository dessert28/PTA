# 读取输入
T = int(input())
results = []

# 定义字符映射
hex_chars = "0123456789ABCDEF"

# 循环处理每组测试数据
for _ in range(T):
    n, k = map(int, input().split())
    original_n = n  # 保存原始的n值用于输出
    if n == 0:
        results.append(f"{original_n} 0")
        continue
    
    # 处理负数
    is_negative = n < 0
    if is_negative:
        n = -n
    
    # 转换为k进制
    converted = ""
    while n > 0:
        remainder = n % k
        converted = hex_chars[remainder] + converted
        n = n // k
    
    # 如果是负数，添加负号
    if is_negative:
        converted = "-" + converted
    
    # 保存结果
    results.append(f"{original_n} {converted}")

# 输出结果
for result in results:
    print(result)
