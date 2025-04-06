s = input()
num_str = ''
for c in s:
    if c.isdigit():
        num_str += c
print(int(num_str))