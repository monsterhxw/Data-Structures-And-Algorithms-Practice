#include <stdio.h>

// C program to implement iterative Binary Search
int binarySearchWithIterative(int arr[], int key, int low, int high) {
    while (low <= high) {
        int mid = (low + high) / 2;
        if (key == arr[mid]) {
            return mid;
        } else if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    //元素不在数组中
    return -1;
}

// C program to implement recursive Binary Search
int binarySearchWithRecursion(int arr[], int key, int low, int high) {
    // 元素不在数组中
    // 递归结束条件
    if (low > high) {
        return -1;
    }
    int mid = (low + high) / 2;
    if (key == arr[mid]) {
        return mid;
    } else if (key < arr[mid]) {
        return binarySearchWithRecursion(arr, key, low, mid - 1);
    } else {
        return binarySearchWithRecursion(arr, key, mid + 1, high);
    }
}

int main() {
    int arr[] = {1, 6, 8, 56, 67, 70, 89, 99, 101, 120};
    int n = sizeof(arr) / sizeof(arr[0]);
    int low = 0;
    int high = n - 1;
    int key = 120;
    int iterativeResult = binarySearchWithIterative(arr, key, low, high);
    (iterativeResult == -1) ? printf("Element is not present in array \n")
                            : printf("Element is present at index %d \n", iterativeResult + 1);
    int recursionResult = binarySearchWithRecursion(arr, key, low, high);
    (recursionResult == -1) ? printf("Element is not present in array \n")
                            : printf("Element is present at index %d \n", recursionResult + 1);
    return 0;
}