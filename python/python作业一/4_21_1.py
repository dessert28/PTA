# 获取输入并去除首尾空格
inp = input().strip()

# 将输入的字符串分割成两个整数 m 和 n
m, n = map(int, inp.split())

# 初始化一个空列表来存储幸运数
number = []

# 遍历区间 [m, n] 中的每一个数字
for i in range(m, n + 1):
    # 检查是否是6的倍数
    if i % 6 == 0:
        number.append(i)
    else:
        # 检查是否有一位是6
        num = i
        while num > 0:
            if num % 10 == 6:
                number.append(i)
                break
            num //= 10

# 输出结果，每个数后面跟一个逗号
print(','.join(map(str, number)) + ',')
