# -*- coding: utf-8 -*-
"""
Created on Sat Mar 15 17:34:52 2025
7-3 zust-sy1-8求一元二次方程的实根
分数 10
作者 张银南
单位 浙江科技大学

从键盘输入一元二次方程的二次项到常数项的系数a,b,c（其中a!=0），计算并输出2个实根。若没有实根，输出“无实根！”。
输入格式:

输入一元二次方程的二次项到常数项的系数a,b,c
输出格式:

输出2个实根。若没有实根，输出“无实根！”。
输入样例1:

在这里给出一组输入。例如：

1,4,2

输出样例1:

在这里给出相应的输出。例如：

x1=-0.59,x2=-3.41

输入样例2:

在这里给出一组输入。例如：

3,6,9

输出样例2:

在这里给出相应的输出。例如：

无实根！

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
栈限制
8192 KB
@author: dessert
"""
x=input()
a,b,c=map(int, x.split(','))
dirt = b**2-4*a*c
if dirt<0:
    print('无实根！')
else:
    x1=(-b+dirt**0.5)/(2*a)
    x2=(-b-dirt**0.5)/(2*a)
    print('x1=%.2f,x2=%.2f'%(x1,x2))
