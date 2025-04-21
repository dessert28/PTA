weight=float(input())
height=float(input())
bmi=weight/height/height
print("%.2f"%bmi)
if bmi < 18.5:
    print("消瘦")
elif bmi > 24:
    print("超重")
else:
    print("正常")