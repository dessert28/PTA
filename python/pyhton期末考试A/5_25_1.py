# 导入必要的依赖项
def main():
    try:
        n = int(input())
        if not (0 <= n <= 10):
            print("输入的n必须在0到10之间。")
            return
        if n == 0:
            return
        # 计算每行的长度
        line_length = n * 2 + 1
        # 生成水平线
        horizontal = "+ " + ("- " * n) * n + "+"
        # 生成垂直线
        vertical = "|" + (" " * (n * 2)) + "|" * n
        # 打印田字格
        for i in range(line_length):
            if i % 2 == 0:
                print(horizontal)
            else:
                print(vertical)
    except ValueError:
        print("请输入一个整数。")

if __name__ == "__main__":
    main()
