// 6-2 多项式求值
// 分数 15
// 入门
// 作者 陈越
// 单位 浙江大学
// 本题要求实现一个函数，计算阶数为n，系数为a[0] ... a[n]的多项式f(x)=∑ 
// i=0
// n
// ​
//  (a[i]×x 
// i
//  ) 在x点的值。

// 函数接口定义：
// double f( int n, double a[], double x );
// 其中n是多项式的阶数，a[]中存储系数，x是给定点。函数须返回多项式f(x)的值。

// 裁判测试程序样例：
// #include <stdio.h>

// #define MAXN 10

// double f( int n, double a[], double x );

// int main()
// {
//     int n, i;
//     double a[MAXN], x;
    
//     scanf("%d %lf", &n, &x);
//     for ( i=0; i<=n; i++ )
//         scanf("%lf", &a[i]);
//     printf("%.1f\n", f(n, a, x));
//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例：
// 2 1.1
// 1 2.5 -38.7
// 输出样例：
// -43.1
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

#include<math.h>
double f(int n,double a[],double x)
{
    double sum = 0.0;
    int i;
    for(i=0;i<=n;i++)
    {
        sum+=a[i]*pow(x,i);
    }
    return sum;
}