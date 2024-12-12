// 6-8 字符串查找
// 分数 15
// 入门
// 作者 风林
// 单位 包头师范学院
// 本题要求实现一个函数，在一个字符串中查找指定字符。

// 如果查找成功，返回字符首次出现的位置（从0算起）；如果查找失败，返回-1。

// 函数接口定义：
// int find ( char s[], char c );
// 参数s是一个字符串，c是查找的字符。函数返回查找的结果。

// 裁判测试程序样例：
// 本程序输入一个字符串，再输入查找的字符，输出查找结果。
// #include <stdio.h>
// #define N 1000

// int find ( char s[], char c );

// int main()
// {
//     char a[N],c;
//     gets(a);
//     c = getchar();
//     printf("%d\n",find(a,c));
//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例1：
// How are you!
// o
// 输出样例1：
// 1
// 输入样例2：
// How are you!
// k
// 输出样例2：
// -1
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

#include<string.h>
int find(char s[],char c)
{
    int i;
    int t=-1;
    for(i=0;i<strlen(s);i++)
    {
        if(s[i]==c)
        {
            t=i;
            break;
        }
    }
    return t;
}