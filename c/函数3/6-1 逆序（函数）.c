// 6-1 逆序（函数）
// 分数 15
// 简单
// 作者 王跃萍
// 单位 东北石油大学
// 将一个含有n个元素的一维数组逆序存放。

// 函数接口定义：
// void inv(int  x[],int n);
// 其中x和n都是用户传入的参数，函数inv的功能是将x数组中的n个元素逆序存放。

// 裁判测试程序样例：
// #include <stdio.h>
// void inv(int x[],int n);
// int main()
// {
//  int i,a[100],n;
//  scanf("%d",&n);
//  for (i=0;i<n;i++)
//    scanf("%d",&a[i]);
//  inv(a,n);
//  for (i=0;i<n;i++)
//     printf("%4d",a[i]);
//  printf("\n");
//   return 0;
//  }

// /* 请在这里填写答案 */
// 输入样例：
// 5
// 1 2 3 4 5
// 输出样例：
//    5   4   3   2   1
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

void inv(int x[],int n)
{
    int temp;
    int i;
    for(i=0;i<n/2;i++)
    {
        temp=x[i];
        x[i]=x[n-i-1];
        x[n-i-1]=temp;
    }
    
}
