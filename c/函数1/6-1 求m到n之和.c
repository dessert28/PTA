// 6-1 求m到n之和
// 分数 10
// 入门
// 作者 张高燕
// 单位 浙大城市学院
// 本题要求实现一个计算m~n（m<n）之间所有整数的和的简单函数。

// 函数接口定义：
// int sum( int m, int n );
// 其中m和n是用户传入的参数，保证有m<n。函数返回的是m~n之间所有整数的和。

// 裁判测试程序样例：
// #include <stdio.h>

// int sum(int m, int n);

// int main()
// {    
//     int m, n;

//     scanf("%d %d", &m, &n);
//     printf("sum = %d\n", sum(m, n));
    
//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例：
// -5 8
// 输出样例：
// sum = 21
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int sum(int m,int n)
{
    int i;
    int sum = 0;
    for(i=m;i<=n;i++)
    {
        sum+=i;
    }
    return sum;
}