// 6-4 函数判断几位数
// 分数 10
// 简单
// 作者 王跃萍
// 单位 东北石油大学
// 从键盘输入一个正整数，求出它是几位数。

// 函数接口定义：
// int  data(int m)
// 其中m是用户传入的参数，该函数返回m是几位数。

// 裁判测试程序样例：
// #include <stdio.h>
// int  data(int m);
// int main()
// {
//  int n;
//   scanf("%d",&n);
//   printf("weishu  is:  %d\n",data(n));
//   return 0;
//  }

// /* 请在这里填写答案 */
// 输入样例：
// 123
// 输出样例：
// weishu  is:  3
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int data(int m)
{
    int num;
    num=m;
    int cnt=0;
    while(num!=0)
    {
        cnt++;
        num=num/10;
    }
    return cnt;
}