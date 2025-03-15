# -*- coding: utf-8 -*-
"""
Created on Sat Mar 15 17:36:22 2025
7-6 整数加减乘计算器
分数 10
作者 冯筠
单位 西北大学

本题目要求读入2个整数A和B和+，-，* 中的一个符号，计算加减乘的值。
输入格式:

输入在一行中给出2个绝对值不超过10000的整数A和B及 +、-、或 * 符号中的一个（每次运行只有一组输入）。
输出格式:

输出运算的值，如果不在三个符号之一，输出error
输入样例:

23+45

输出样例:

68

输入样例:

4-5

输出样例:

-1

输入样例:

3/2

输出样例:

error

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
flag = False
for i in range(len(x)):
    if x[i]=='+':
        a=int(x[:i])
        b=int(x[i+1:])
        print(a+b)
        flag=True
        break
    elif x[i]=='-':
        a=int(x[:i])
        b=int(x[i+1:])
        print(a-b)
        flag=True
        break
    elif x[i]=='*':
        a=int(x[:i])
        b=int(x[i+1:])
        print(a*b)
        flag=True
        break
if flag==False:
    print("error")










