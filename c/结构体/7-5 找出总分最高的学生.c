// 7-5 找出总分最高的学生
// 分数 10
// 简单
// 作者 C课程组
// 单位 浙江大学
// 给定N个学生的基本信息，包括学号（由5个数字组成的字符串）、姓名（长度小于10的不包含空白字符的非空字符串）和3门课程的成绩（[0,100]区间内的整数），要求输出总分最高学生的姓名、学号和总分。

// 输入格式：
// 输入在一行中给出正整数N（≤10）。随后N行，每行给出一位学生的信息，格式为“学号 姓名 成绩1 成绩2 成绩3”，中间以空格分隔。

// 输出格式：
// 在一行中输出总分最高学生的姓名、学号和总分，间隔一个空格。题目保证这样的学生是唯一的。

// 输入样例：
// 5
// 00001 huanglan 78 83 75
// 00002 wanghai 76 80 77
// 00003 shenqiang 87 83 76
// 10001 zhangfeng 92 88 78
// 21987 zhangmeng 80 82 75
// 输出样例：
// zhangfeng 10001 258
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB
// 栈限制
// 8192 KB

#include<stdio.h>
struct student{
    char name[10];
    char number[5];
    int a,b,c;
    int sum;
}stu[10];
int main()
{
    int n,i,j;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s %s %d %d %d",stu[i].number,stu[i].name,&stu[i].a,&stu[i].b,&stu[i].c);
        stu[i].sum=stu[i].a+stu[i].b+stu[i].c;
    }
    for(j=i=0;i<n;i++)
    {
        if(stu[j].sum<stu[i].sum)
            j=i;
    }
    printf("%s %s %d",stu[j].name,stu[j].number,stu[j].sum);
    return 0;
}