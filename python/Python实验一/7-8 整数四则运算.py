# -*- coding: utf-8 -*-
"""
Created on Sat Mar 15 17:37:22 2025
7-8 整数四则运算
分数 10
作者 mjye
单位 北京师范大学珠海校区

编写程序，计算两个正整数 A 和 B 的和、差、积、商并输出。
输入格式:

输入两行，
第一行一个整数 A，
第二行一个整数 B。
输出格式:

输出4行，按照格式“A 运算符 B = 结果”顺序输出和、差、积、商。（注意这里的商是整除的结果）
输入样例:

3
2

输出样例:

3 + 2 = 5
3 - 2 = 1
3 * 2 = 6
3 / 2 = 1

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

x=int(input())
y=int(input())
print("%d + %d = %d"%(x,y,x+y))
print("%d - %d = %d"%(x,y,x-y))
print("%d * %d = %d"%(x,y,x*y))
print("%d / %d = %d"%(x,y,x/y))
