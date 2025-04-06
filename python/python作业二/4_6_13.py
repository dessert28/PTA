n=int(input())
longest=''
for i in range(n):
    s=input()
    if len(s)>len(longest):
        longest =s
print("The longest is:",longest)