// 7-1 查找指定字符
// 分数 15
// 入门
// 作者 颜晖
// 单位 浙江大学
// 本题要求编写程序，从给定字符串中查找某指定的字符。

// 输入格式：
// 输入的第一行是一个待查找的字符。第二行是一个以回车结束的非空字符串（不超过80个字符）。

// 输出格式：
// 如果找到，在一行内按照格式“index = 下标”输出该字符在字符串中所对应的最大下标（下标从0开始）；否则输出"Not Found"。

// 输入样例1：
// m
// programming
// 输出样例1：
// index = 7
// 输入样例2：
// a
// 1234
// 输出样例2：
// Not Found
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB
// 栈限制
// 8192 KB

#include<stdio.h>
#include<string.h>
int main()
{
    char m,a[99];
    int w,i;
    scanf("%c",&m);
    getchar();
    gets(a);
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]==m)
            w=i;
        else
            w=10000;
    }
    if(w==10000)
        printf("Not Found");
    else
        printf("index = %d",w);
    return 0;
}