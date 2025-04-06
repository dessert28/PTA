// 6-2 使用函数求阶乘和
// 分数 10
// 简单
// 作者 颜晖
// 单位 浙大城市学院
// 本题要求实现一个计算非负整数阶乘的简单函数，使得可以利用该函数，求1!+2!+...+n!的值。题目保证计算结果不超过双精度范围。

// 函数接口定义：
// double fact( int n );
// 其中n是用户传入的参数。如果n是非负整数，则该函数必须返回n的阶乘，否则返回0。

// 裁判测试程序样例：
// #include <stdio.h>

// double fact( int n );

// int main(void)
// {    
//     int i, n;
//     double sum; 

//     scanf("%d", &n);
//     sum = 0;
//     for(i = 1; i <= n; i++){
//         sum = sum + fact(i); 
//      }
//      printf("%.0f\n", sum);

//     return 0;
// }

// /* 请在这里填写答案 */
// 输入样例：
// 3
// 输出样例：
// 9
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

double fact(int n)
{
    long int temp=1;
    int i;
    for(i=1;i<=n;i++)
    {
        temp*=i;
    }
    // if(n<=0)
    //     temp=0;
    return temp;
}