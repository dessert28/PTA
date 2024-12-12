// 6-4 一维数组：带回最小值的下标。
// 分数 10
// 入门
// 作者 苑丽红
// 单位 长春理工大学
// 主函数读入5个数并求最小值。要求通过函数fun返回最小值的下标来实现。

// 函数接口定义：
// 在这里描述函数接口。例如：
// int fun(int list[],int size)   ;
// list、size由主函数传入。其中size是数组元素个数。

// 裁判测试程序样例：
// 在这里给出函数被调用进行测试的例子。例如：

// #include "stdio.h"
// #define SIZE 5    

// int fun(int list[ ], int size)   ;

// int main()
// {
// int i , v[SIZE] ;
// for (i=0;i<SIZE;i++)
// {
//    scanf("%d", v+i );     
//  }     
// i=fun(v, SIZE);     
// printf("index=%d, min=%d", i,v[i] );
//  return 0;
// }

// /* 答题框你填写的答案被嵌入这里 */
// 输入样例：
// 18 -2 -5 70 9
// 输出样例：
// index=2,min=-5
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

int fun(int list[],int size)
{
    int i;
    int index=0;
    for(i=1;i<5;i++)
    {
        if(list[i-1]>list[i])
            index=i;
    }
    return index;
}