# -*- coding: utf-8 -*-
"""
Created on Sat Mar 15 17:38:31 2025
7-10 zust-sy6-4产生数字B个A
分数 10
作者 张银南
单位 浙江科技大学

输入2个正整数A和B，1<=A<=9, 1<=B<=10,产生数字AA...A,一共B个A。
输入格式:

在一行中输入A和B，逗号隔开。
输出格式:

另一行中输出AAA..A，一共B个A
输入样例:

在这里给出一组输入。例如：

3,6

输出样例:

在这里给出相应的输出。例如：

333333

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
for i in range(len(x)):
    if x[i]==',':
        a=int(x[:i])
        b=int(x[i+1:])
for i in range(b):
    print(a,end="")