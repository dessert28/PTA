// 6-7 使用函数求素数和
// 分数 15
// 简单
// 作者 张高燕
// 单位 浙大城市学院
// 本题要求实现一个判断素数的简单函数、以及利用该函数计算给定区间内素数和的函数。

// 素数就是只能被1和自身整除的正整数。注意：1不是素数，2是素数。

// 函数接口定义：
// int prime( int p );
// int PrimeSum( int m, int n );
// 其中函数prime当用户传入参数p为素数时返回1，否则返回0；函数PrimeSum返回区间[m, n]内所有素数的和。题目保证用户传入的参数m≤n。

// 裁判测试程序样例：
// #include <stdio.h>
// #include <math.h>

// int prime( int p );
// int PrimeSum( int m, int n );
    
// int main()
// {
//     int m, n, p;

//     scanf("%d %d", &m, &n);
//     printf("Sum of ( ");
//     for( p=m; p<=n; p++ ) {
//         if( prime(p) != 0 )
//             printf("%d ", p);
//     }
//     printf(") = %d\n", PrimeSum(m, n));

//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例：
// -1 10
// 输出样例：
// Sum of ( 2 3 5 7 ) = 17
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int prime(int p)
{
    int i;
    int index = 1;
    for(i=2;i<p;i++)
    {
        if(p%i==0){
            index=0;
            break;
        }
    }
    if(p<=1)
        index=0;
    if(p==2)
        index=1;
    return index;
}
int PrimeSum(int m,int n)
{
    int i,j;
    int sum=0;
    for(i=m;i<=n;i++)
    {
        if(prime(i))
            sum+=i;
    }
    return sum;
}