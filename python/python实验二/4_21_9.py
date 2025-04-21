x=input().split( )
y=len(x)
z=0
for i in x:
    z+=len(i)
print("%d,%.2f"%(y,z/y))