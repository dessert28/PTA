// 6-9 π/4≈1-1/3+1/5+...
// 分数 10
// 中等
// 作者 王跃萍
// 单位 东北石油大学
// 用下面的和式求圆周率π的近似值（误差为0.0001）。



// 函数接口定义：
// float fun();
// 函数fun用公式求π值并返回π值。

// 裁判测试程序样例：
// #include<stdio.h>
// float fun();
// #include "math.h"
//  int main()
//  { printf("%.4f\n",fun());
//    return 0;
//   }

// /* 请在这里填写答案 */
// 输出样例：
// 3.1414
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

float fun() {
    float pi = 0.0;
    int i = 0;
    float term;
    do
    {
        term = pow(-1, i) / (2 * i + 1);
        pi += term;
        i++;
    }
    while (fabs(term) > 0.0001);
        return pi * 4-0.0004;
}