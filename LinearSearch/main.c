// C program to Implement Linear Search Algorithm.
#include <stdio.h>

int linearSearch(int arr[], int n, int key) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}

int optimizedLinearSearch(int arr[], int n, int key) {
    int i;
    // 判断 key 是否等于待查找数组的中的第一个元素，若等于则返回下标 0，不等于则将 key 赋值给 arr[0]
    if (arr[0] == key) {
        return 0;
    }
    // 设置 a[0] 为哨兵
    arr[0] = key;
    i = n - 1;
    while (arr[i] != key) {
        i--;
    }
    if (i == 0) {
        return -1;
    }
    return i;
}

int main() {
    // 待查找数组的指针
    int arr[5] = {2, 5, 6, 3, 4};
    // 待查找数组中的元素个数
    int n = sizeof(arr) / sizeof(arr[0]);
    // 查找关键字
    int key = 4;
    // 普通顺序查找实现
    int result = linearSearch(arr, n, key);
    (result == -1) ? printf("Element is not present in array")
                   : printf("Element is present at index %d", result + 1);

    printf("\n");
    // 优化顺序查找算法实现
    int optimizationResult = optimizedLinearSearch(arr, n, key);
    (optimizationResult == -1) ? printf("Element is not present in array")
                               : printf("Element is present at index %d", optimizationResult + 1);
    return 0;
}