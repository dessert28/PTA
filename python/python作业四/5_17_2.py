ages = []
male_count = 0
while True:
    line = input()
    if line == "":
        break
    info = line.split()
    gender = info[1]
    age = int(info[2])
    ages.append(age)
    if gender == "男":
        male_count += 1

average_age = sum(ages) / len(ages) if ages else 0
print(f"平均年龄是{average_age:.2f} 男性人数是{male_count}")