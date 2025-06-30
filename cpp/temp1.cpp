#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;  // 读取输入的 n

    // 确保 n 在 1 到 10 的范围内
    if (n >= 1 && n <= 10) {
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= n; j++) {
                std::cout << j;
            }
            std::cout << std::endl;  // 每行结束后添加换行符
        }
    } else {
        std::cout << "输入的 n 必须在 1 到 10 之间" << std::endl;
    }

    return 0;
}
