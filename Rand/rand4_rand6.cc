#include <iostream>
#include <cstdlib> // 包含rand()和srand()
#include <ctime>
#include <vector>   // 包含time()

#define COUNT 10000

// 假设有一个rand4()函数，生成[1, 4]范围内的随机数
int rand4() {
    return rand() % 4 + 1;
}

// 使用rand4()实现rand6()
int rand6() {
    while (true) {
        // 生成[1, 16]范围内的随机数
        int num = (rand4() - 1) * 4 + rand4();
        // 如果落在[1, 6]范围内，直接返回
        if (num <= 6) {
            return num;
        }
        // 否则重新生成
    }
}

int main() {
    // 初始化随机数种子
    srand(static_cast<unsigned int>(time(nullptr)));

    std::vector<int> arr(7);

    // 测试rand6()
    for(int i=0;i<COUNT;i++) {
        int num = rand6();
        arr[num]++;
    }

    for(int i=0;i<6;i++) {
        std::cout<<"number1->"<< arr[i+1] <<std::endl;
    }

    return 0;
}