import math
def factors(x):
    y=int(math.sqrt(x))
    for i in range(2,y+1):
       if (x %i ==0):
            print(i,end=' ');
            factors(x//i)
            break
       else:
           print(x,end=' ')
    return
factors(18)