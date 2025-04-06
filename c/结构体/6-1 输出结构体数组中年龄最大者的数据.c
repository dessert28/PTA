// 6-1 输出结构体数组中年龄最大者的数据
// 分数 10
// 简单
// 作者 王跃萍
// 单位 东北石油大学
// 给定程序中，函数fun的功能是：将形参std所指结构体数组中年龄最大者的数据作为函数值返回，并在主函数中输出。

// 函数接口定义：
// struct student fun(struct student  std[], int  n);
// 其中 std 和 n 都是用户传入的参数。 函数fun的功能是将含有 n 个人的形参 std 所指结构体数组中年龄最大者的数据作为函数值返回。

// 裁判测试程序样例：
// #include <stdio.h>

// struct student
// {char  name[10];
//  int  age;
// };
// struct student fun(struct student  std[], int  n);
// int main()
// {
// struct student std[5]={"aaa",17,"bbb",16,"ccc",18,"ddd",17,"eee",15  };
// struct student  max;
// max=fun(std,5);
// printf("\nThe result:\n");
// printf("\nName : %s,   Age :  %d\n", max.name,max.age);
// return 0;
//  }


// /* 请在这里填写答案 */
// 输出样例：

// The result:

// Name : ccc,   Age :  18
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

struct student fun(struct student std[],int n)
{
    int max=0,i;
    for(i=0;i<n;i++)
    {
        if(std[i].age>std[max].age)
            max=i;
    }
    return std[max];
}