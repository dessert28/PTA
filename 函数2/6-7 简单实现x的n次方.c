// 6-7 简单实现x的n次方
// 分数 10
// 入门
// 作者 颜晖
// 单位 浙大城市学院
// 本题要求实现一个计算x 
// n
//  （n≥0）的函数。

// 函数接口定义：
// double mypow( double x, int n );
// 函数mypow应返回x的n次幂的值。题目保证结果在双精度范围内。

// 裁判测试程序样例：
// #include <stdio.h>

// double mypow( double x, int n );

// int main()
// {
//     double x;
//     int n;

//     scanf("%lf %d", &x, &n);
//     printf("%f\n", mypow(x, n));

//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例：
// 0.24 4
// 输出样例：
// 0.003318
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

double mypow(double x,int n)
{
    double num=x;
    int i;
    for(i=1;i<n;i++)
    {
        num*=x;
    }
    if(n==0)
        num=1;
    return num;
}