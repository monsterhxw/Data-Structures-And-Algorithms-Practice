// C program to implement interpolation search
#include <stdio.h>

int interpolationSearch(int arr[], int key, int low, int high) {
    // 元素不在数组中
    // 递归结束条件
    if (low > high) {
        return -1;
    }
    // 插值的计算公式
    int mid = low + (key - low) / (arr[high] - arr[low]) * (high - low);
    if (key == arr[mid]) {
        return mid;
    } else if (key < arr[mid]) {
        return interpolationSearch(arr, key, low, mid - 1);
    } else {
        return interpolationSearch(arr, key, mid + 1, high);
    }
}

int main() {
    int arr[] = {1, 6, 8, 56, 67, 70, 89, 99, 101, 120};
    int n = sizeof(arr) / sizeof(arr[0]);
    int low = 0;
    int high = n - 1;
    int key = 1;
    int result = interpolationSearch(arr, key, low, high);
    (result == -1) ? printf("Element is not present in array \n")
                   : printf("Element is present at index %d \n", result + 1);
    return 0;
}