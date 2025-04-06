// 6-5 求排列数
// 分数 10
// 入门
// 作者 颜晖
// 单位 浙大城市学院
// 本题要求实现一个计算阶乘的简单函数，使得可以利用该函数，根据公式P 
// n
// m
// ​
//  = 
// (n−m)!
// n!
// ​
//  算出从n个不同元素中取出m个元素（0<m≤n）的排列数。

// 函数接口定义：
// double fact( int n );
// 其中n是用户传入的参数，函数返回n的阶乘。

// 裁判测试程序样例：
// #include <stdio.h>

// double fact( int n );

// int main(void)
// {    
//     int m, n;
//     double result; 

//     scanf("%d%d", &m, &n);
//     if(m > 0 && n > 0 && m <= n){
//         result = fact(n)/fact(n-m);
//         printf("result = %.0f\n", result);    
//     }

//     return 0;
// }

// /* 请在这里填写答案 */
// 输入样例：
// 2 14
// 输出样例：
// 在这里给出相应的输出。例如：

// result = 182
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

double fact(int n)
{
    int i;
    long temp=1;
    for(i=2;i<=n;i++)
    {
        temp*=i;
    }
    return temp;
}