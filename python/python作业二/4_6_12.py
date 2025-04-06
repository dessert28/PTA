xb=input()
zf=input()
index=0
flag=0
for i in zf:
    index+=1
    if xb==i:
        daan=index-1
        flag=1
if flag==1:
    print('index= %d'%daan)
else:
    print('Not Found')