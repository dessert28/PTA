// 7-2 统计成绩2
// 分数 15
// 入门
// 作者 DS课程组
// 单位 临沂大学
// 给定N个学生的基本信息，包括学号（由12个数字组成的字符串）、姓名（长度小于20的不包含空白字符的非空字符串）、高等数学成绩、C语言程序设计成绩，成绩均为[0,100]区间内的整数，要求统计高等数学成绩及格的人数，并按输入顺序给出高等数学及格学生名单。

// 输入格式:
// 输入在一行中给出正整数N（≤10）。
// 随后N行，每行给出一位学生的信息，格式为“学号 姓名 高等数学成绩 C语言程序设计成绩”，中间以空格分隔。

// 输出格式:
// 首先在一行中输出高等数学及格人数，然后按照输入顺序，每行输出一位该成绩及格的学生的学号和姓名，间隔一个空格。

// 输入样例:
// 3
// 201410300106 wanyun 70 88
// 201618050322 zhangyu 59 60
// 201509210118 lixiao 80 80
// 输出样例:
// 2
// 201410300106 wanyun
// 201509210118 lixiao
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB
// 栈限制
// 8192 KB

#include<stdio.h>
#include<string.h>
struct student{
    char num[15];
    char name[20];
    int math;
    int c;
    
}shu[10];
int main()
{
    int n;
    scanf("%d",&n);
    int cnt=0;
    int i;
    for(i=0;i<n;i++)
    {
        getchar();
        scanf("%s %s %d %d",shu[i].num,shu[i].name,&shu[i].math,&shu[i].c);
        if(shu[i].math>=60)
            cnt++;
        
    }
    printf("%d\n",cnt);
    for(i=0;i<n;i++)
    {
        if(shu[i].math>=60)
        {
            printf("%s %s\n",shu[i].num,shu[i].name);
        }
    }
    return 0;
}