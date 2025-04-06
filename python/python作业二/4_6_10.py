month, jzxnum = map(int, input().split())
if month >= 7 and month <= 9:
    if jzxnum >= 20:
        rebate = 10
    else:
        rebate = 5
else:
    if jzxnum >= 20:
        rebate = 20
    else:
        rebate = 10
print(rebate)