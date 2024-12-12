// 6-8 二维数组中最大值
// 分数 10
// 简单
// 作者 王跃萍
// 单位 东北石油大学
// 求出二维数组中的最大元素值。

// 函数接口定义：
//  int max_value(m,n,array);
// 函数max_value的功能是求m行n列二维数组array的最大值并返回最大值。

// 裁判测试程序样例：
// #include <stdio.h>
//  int max_value(m,n,array);
// int main()
// {
//  int a[3][4]={{1,3,5,7},{2,4,6,8},{15,17,34,12}};
//  printf("max value is %d\n", max_value(3,4,a));
// return 0;
//  }
// /* 请在这里填写答案 */
// 输出样例：
// max value is 34
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

 int max_value(int m,int n,int array[][4])
{
    int i,j;
    int maxnum=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(array[i][j]>maxnum)
                maxnum=array[i][j];
        }
    }
    return maxnum;
}