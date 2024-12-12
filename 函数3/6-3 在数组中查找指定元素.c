// 6-3 在数组中查找指定元素
// 分数 10
// 入门
// 作者 张泳
// 单位 浙大城市学院
// 本题要求实现一个在数组中查找指定元素的简单函数。

// 函数接口定义：
// int search( int list[], int n, int x );
// 其中list[]是用户传入的数组；n（≥0）是list[]中元素的个数；x是待查找的元素。如果找到

// 则函数search返回相应元素的最小下标（下标从0开始），否则返回−1。

// 裁判测试程序样例：
// #include <stdio.h>
// #define MAXN 10

// int search( int list[], int n, int x );
    
// int main()
// {
//     int i, index, n, x;
//     int a[MAXN];

//     scanf("%d", &n);
//     for( i = 0; i < n; i++ )
//         scanf("%d", &a[i]);
//     scanf("%d", &x);
//     index = search( a, n, x );
//     if( index != -1 )
//         printf("index = %d\n", index);
//     else
//         printf("Not found\n");
            
//     return 0;
// }

// /* 你的代码将被嵌在这里 */
// 输入样例1：
// 5
// 1 2 2 5 4
// 2
// 输出样例1：
// index = 1
// 输入样例2：
// 5
// 1 2 2 5 4
// 0
// 输出样例2：
// Not found
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB


int search(int list[],int n,int x)
{
    int i;
    int t=-1;
    for(i=0;i<n;i++)
    {
        if(list[i]==x){
            t=i;
            break;}
    }
    return t;
}


