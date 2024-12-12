// 6-2 计算两点之间的距离
// 分数 10
// 入门
// 作者 吕生荣
// 单位 内蒙古师范大学
// 编写一个函数，计算两点A(x1,y1)，B(x2,y2)之间的距离。计算两点距离的公式如下：

// dis=sqrt((x1−x2)∗(x1−x2)+(y1−y2)∗(y1−y2))

// 函数接口定义：
// double dist(point A,point B) ;
// A和B是坐标系中的两个点，每个点包括横坐标x和纵坐标y。

// 裁判测试程序样例：
// #include <stdio.h>
// #include <math.h>
// typedef struct point point;
// struct point{
//     int x,y;//x是点的横坐标,y是点的纵坐标 
// };
// double dist(point A,point B) ;
// int main(){
//     point A,B;
//     double dis;
//     scanf("%d%d%d%d",&A.x ,&A.y ,&B.x,&B.y);
//     dis=dist(A,B);
//     printf("%.2f\n",dis) ;
//     return 0;
// }

// /* 请在这里填写答案 */
// 输入样例：
// 在这里给出一组输入。例如：

// 0 0 1 1
// 输出样例：
// 在这里给出相应的输出。例如：

// 1.41
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB

double dist(point A,point B)
{
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}