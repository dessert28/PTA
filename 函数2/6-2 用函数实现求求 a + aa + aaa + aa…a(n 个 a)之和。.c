// 6-2 用函数实现求求 a + aa + aaa + aa…a(n 个 a)之和。
// 分数 15
// 入门
// 作者 xcf
// 单位 长春理工大学
// 用函数实现求求 a + aa + aaa + aa…a(n 个 a)之和。 

// 函数接口定义：
// int fun(int a,int n);
// 。

// 裁判测试程序样例：
// 在这里给出函数被调用进行测试的例子。例如：
// #include <stdio.h>

// int fun(int a,int n);

// int main()
// {

//     int a,n;
//     scanf("%d %d",&a,&n);
//     printf("%d", fun(a,n));

//   return 0;

// }

// /* 请在这里填写答案 */
// 输入样例：
// 在这里给出一组输入。例如：

// 2 3
// 输出样例：
// 在这里给出相应的输出。例如：

// 246
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int fun(int a,int n)
{
    int i;
    int temp=a;
    int sum = a;
    for(i=1;i<n;i++)
    {
        temp=temp*10+a;
        sum+=temp;
    }
    return sum;
}