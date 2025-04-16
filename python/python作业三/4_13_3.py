def is_powerful_number(num):
    # 将数字转换为字符串以便逐位处理
    str_num = str(num)
    sum_of_powers = sum(int(digit) ** 5 for digit in str_num)
    return sum_of_powers == num

def find_powerful_numbers(n):
    results = []
    # 生成从1到10^n - 1的所有数字
    for i in range(1, 10**n):
        if is_powerful_number(i):
            results.append(i)
    return results

if __name__ == "__main__":
    n = int(input())
    powerful_numbers = find_powerful_numbers(n)
    for number in powerful_numbers:
        print(number)
