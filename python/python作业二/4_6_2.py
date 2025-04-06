# 输入操作数1、运算符、操作数2
input_data = input().split()

# 将输入的操作数转换为整数
num1 = int(input_data[0])
operator = input_data[1]
num2 = int(input_data[2])

# 根据运算符进行相应的运算
if operator == '+':
    result = num1 + num2
elif operator == '-':
    result = num1 - num2
elif operator == '*':
    result = num1 * num2
elif operator == '/':
    if num2 != 0:
        result = num1 / num2
    else:
        result = "ERROR"
elif operator == '%':
    if num2 != 0:
        result = num1 % num2
    else:
        result = "ERROR"
else:
    result = "ERROR"

# 输出结果
print(result)
