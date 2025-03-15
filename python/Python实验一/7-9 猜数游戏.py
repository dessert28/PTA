# -*- coding: utf-8 -*-
"""
Created on Sat Mar 15 17:37:55 2025
7-9 猜数游戏
分数 10
作者 mjye
单位 北京师范大学珠海校区

猜数字游戏：计算机随机产生一个区间 [1,100] 的整数，用户输入一个数对其进行猜测，程序对其与随机产生的被猜数进行比较，并提示大了（Too Big）、小了（Too Small），还是相等（ You Win!）。如果相等，则表示猜中，立即结束程序。如果超过 8 次都没有猜中，则提示  Game Over!，并结束程序。
提示：

计算机产生的随机数调用 random 库。为了方便调试，固定随机数种子为 1，这样，每一次随机生成的数都是相同的。参考下列代码生成一个区间 [1,100] 的随机整数。

random.seed(1)
randnum = random.randint(1, 100)

输入格式:

输入 8 行，每行给出一个用户的输入。
输出格式:

每次在一行中输出相应的猜测结果，如果猜中，输出 You Win! ，并立即结束程序，不需要判断剩余的输入；如果 8 次没有猜中，则输出 Game Over! ，并结束程序。
输入样例:

56
25
12
20
16
18
17
89

输出样例:

Too Big
Too Big
Too Small
Too Big
Too Small
You Win!

样例解释

每一行输入的数和随机生成的数比较，输出是大还是小。
输入第6个数18时，刚好和随机生成的数相同，猜中之后直接结束程序，剩余第7行和第8行不需要处理，所以也没有输出。
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

import random
i=0
while i<8:
    x=int(input())
    random.seed(1)
    y=random.randint(1,100)
    if x==y:
        print("You Win!")
        break
    elif x<y:
        print("Too Small")
    elif x>y:
        print("Too Big")
    i+=1
else:
    print("Game Over!")