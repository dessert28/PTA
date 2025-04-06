id_card = input()
if len(id_card) != 18:
    print('输入的身份证号位数错')
else:
    gender = int(id_card[16])
    if gender % 2 == 0:
        print('女')
    else:
        print('男')
    birth = id_card[6:14]
    year = birth[0:4]
    month = birth[4:6]
    day = birth[6:8]
    print(f'出生于{year}年{month}月{day}日')