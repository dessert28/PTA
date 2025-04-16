n = int(input())

# 前来查询的用户的性别和身高
for i in range(n):
    # 根据空格分割性别和身高
    gender, height = input().split(' ')
    # 根据性别计算出其情侣的最佳身高
    if gender == 'F':
        print(f'{float(height)*1.09:.2f}')
    elif gender == 'M':
        print(f'{float(height)/1.09:.2f}')

