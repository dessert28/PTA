// 7-3 打印杨辉三角
// 分数 15
// 简单
// 作者 徐镜春
// 单位 浙江大学
// 本题要求按照规定格式打印前N行杨辉三角。

// 输入格式：
// 输入在一行中给出N（1≤N≤10）。

// 输出格式：
// 以正三角形的格式输出前N行杨辉三角。每个数字占固定4位。

// 输入样例：
// 6
// 输出样例：
//         1
//        1   1
//       1   2   1
//      1   3   3   1
//     1   4   6   4   1
//    1   5  10  10   5   1
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB
// 栈限制
// 8192 KB

#include<stdio.h>
int main()
{
    int n;
    int a[11][11];
    a[0][0]=0;
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        for(int k=0;k<n-i-1;k++)
        {
            printf(" ");
        }
        for(int j=0;j<=i;j++)
        {
            if(i==j)
                a[i][j]=1;
            else if(j==0)
                a[i][j]=1;
            else
                a[i][j]=a[i-1][j-1]+a[i-1][j];
            printf("%4d",a[i][j]);
            if(i==j)
                printf("\n");
        }
    }
    
}



