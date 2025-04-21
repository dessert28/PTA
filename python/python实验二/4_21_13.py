x,y=map(int,input().split())
n=int(input())
for i in range(n):
    a,b=map(int,input().split())
    if(a==0 or a==x or b==0 or b==y):
        print("On the Border")
    elif 0<a<x and 0<b<y:
        print("Inside")
    else:
        print("Outside")