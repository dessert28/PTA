// 6-3 计算区间上所有正整数的和
// 分数 10
// 简单
// 作者 陈波
// 单位 山东理工大学
// 本题要求编写一个函数，计算闭区间[m,n]上所有正整数的和。
// 例如闭区间[-3,5]上正整数的和是15，则该函数应该返回15。

// 函数接口定义：
// int Sum_Int(int m,int n);
// 其中 m 和 n 都是用户传入的参数， m 和 n 的值不超过int型的范围。函数须返回闭区间上所有正整数的和。

// 裁判测试程序样例：
// #include <stdio.h>
// int Sum_Int(int m,int n);
// int main()
// {
//     int m,n,sum;
//     scanf("%d%d",&m,&n);
//     sum=Sum_Int(m,n);
//     printf("%d\n",sum);
//     return 0;
// }
// /* 请在这里填写答案 */
// 输入样例：
// -10 20

// 输出样例：
// 210

// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int Sum_Int(int m,int n)
{
    if(m<0)
        m=0;
    int d=n-m;
    int sum = 0;
    int i;
    for(i=0;i<=d;i++)
    {
        sum+=m+i;
    }
    return sum;
}