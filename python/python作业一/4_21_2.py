# 读取输入并处理
input_data = input().split()
gender = int(input_data[0])
father_height = float(input_data[1])
mother_height = float(input_data[2])

# 检查父母身高范围是否在 [1.0, 3.0] 之间
if 1.0 <= father_height <= 3.0 and 1.0 <= mother_height <= 3.0:
    if gender == 1:  # 男孩
        height = (father_height + mother_height) / 2 * 1.08
    else:           # 女孩
        height = (father_height * 0.923 + mother_height) / 2
    print(f"{height:.3f}")
else:
    print("父亲或母亲的身高不在有效范围内")
