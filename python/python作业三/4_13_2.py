def sushu(x):
    if x==2: return True
    if x%2==0 or x==1: return False
    n=3
    while n*n<=x:
        if x%n==0: return False
        n+=2
    return True
 
def gdbh(n):
    # if n==4:
    #     print('4=2+2')
    #     return
    for i in range(1,n,2):
        if sushu(i) and sushu(n-i):
            print("{}={}+{}".format(n,i,n-i),sep='')
            return
n=int(input())
gdbh(n)
 