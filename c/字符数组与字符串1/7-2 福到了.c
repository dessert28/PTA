// 7-2 福到了
// 分数 15
// 入门
// 作者 陈越
// 单位 浙江大学
// “福”字倒着贴，寓意“福到”。不论到底算不算民俗，本题且请你编写程序，把各种汉字倒过来输出。这里要处理的每个汉字是由一个 N × N 的网格组成的，网格中的元素或者为字符 @ 或者为空格。而倒过来的汉字所用的字符由裁判指定。

// 输入格式：
// 输入在第一行中给出倒过来的汉字所用的字符、以及网格的规模 N （不超过100的正整数），其间以 1 个空格分隔；随后 N 行，每行给出 N 个字符，或者为 @ 或者为空格。

// 输出格式：
// 输出倒置的网格，如样例所示。但是，如果这个字正过来倒过去是一样的，就先输出bu yong dao le，然后再用输入指定的字符将其输出。

// 输入样例 1：
// $ 9
//  @  @@@@@
// @@@  @@@ 
//  @   @ @ 
// @@@  @@@ 
// @@@ @@@@@
// @@@ @ @ @
// @@@ @@@@@
//  @  @ @ @
//  @  @@@@@
// 输出样例 1：
// $$$$$  $ 
// $ $ $  $ 
// $$$$$ $$$
// $ $ $ $$$
// $$$$$ $$$
//  $$$  $$$
//  $ $   $ 
//  $$$  $$$
// $$$$$  $ 
// 输入样例 2：
// & 3
// @@@
//  @ 
// @@@
// 输出样例 2：
// bu yong dao le
// &&&
//  & 
// &&&
// 代码长度限制
// 16 KB
// 时间限制
// 400 ms
// 内存限制
// 64 MB
// 栈限制
// 8192 KB

#include <stdio.h>
#include <string.h>

int main() {
    char replace_char;
    int N;
    scanf("%c %d", &replace_char, &N);
    getchar(); // 吸收换行符

    char grid[N][N];
    char reversed_grid[N][N];
    int is_symmetric = 1;

    // 读取网格数据
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%c", &grid[i][j]);
        }
        getchar(); // 吸收换行符
    }

    // 检查是否对称
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != grid[N-1-i][N-1-j]) {
                is_symmetric = 0;
                break;
            }
        }
        if (!is_symmetric) break;
    }

    // 输出结果
    if (is_symmetric) {
        printf("bu yong dao le\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[i][j] == '@') {
                    printf("%c", replace_char);
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    } else {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (grid[N-1-i][N-1-j] == '@') {
                    printf("%c", replace_char);
                } else {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}

