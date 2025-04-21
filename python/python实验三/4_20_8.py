list2 = []
while 1:
    n=int(input())
    if n<0:
        break
    list2.append(n)
if len(list2)==0:
    print("没有学生")
else:
    ave=sum(list2)/len(list2)
    list1=[]
    for i in list2:
        if i<60:
            list1.append(i)
        fail=len(list1)
    print("平均分={:.2f},不及格人数={}".format(ave,fail))