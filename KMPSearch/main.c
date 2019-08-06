// C Program To Implement KMP Search Algorithm
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void buildPrefixTable(char pattern[], int prefix[], int n) {
    // 设定 prefix table 的第一个元素为 0
    prefix[0] = 0;
    // len 表示为最长公共前后缀的长度
    int len = 0;
    // prefix table 的第一个元素为 0，所以 i 从 1 开始往后比较
    int i = 1;
    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefix[i] = len;
            i++;
        } else if (len > 0) {
            // len 大于 0 的情况，向左侧对（左斜对）len = prefix[len - 1]
            len = prefix[len - 1];
        } else {
            // len 为 0 的情况，将 prefix[i] 等于 0，i 加 1，继续往下移动
            prefix[i] = len;
            i++;
        }
    }
}

// prefix table 中的元素向前移动一位，并将第一个元素赋值为 -1
void movePrefixTable(int prefix[], int n) {
    int i;
    for (i = n - 1; i > 0; i--) {
        prefix[i] = prefix[i - 1];
    }
    prefix[0] = -1;
}

void kmpSearch(char text[], char pattern[]) {
    // 计算出 pattern 的长度
    int PATTERN_LENGTH = strlen(pattern);
    // 计算出 text 的长度
    int TEXT_LENGTH = strlen(text);
    // 初始化 prefix table
    int *prefix = malloc(sizeof(int) * PATTERN_LENGTH);
    // 建立 prefix table
    buildPrefixTable(pattern, prefix, PATTERN_LENGTH);
    // 将 prefix table 中的元素向前移动一位，并将第一个元素赋值为 -1
    movePrefixTable(prefix, PATTERN_LENGTH);
    int i = 0, j = 0;
    while (i < TEXT_LENGTH) {
        // 匹配到 j 的最后一位元素时并且 text[i] 等于 pattern[j] 相等时，证明整段字符匹配成功，打印出匹配完时的位置，继续往下匹配
        if (j == PATTERN_LENGTH - 1 && text[i] == pattern[j]) {
            printf("Found pattern begin at %d and end at %d \n", i - j + 1, i + 1);
            // 将 prefix table 数组中下标为 j 的值赋给 j，继续往后匹配，
            j = prefix[j];
        }
        // 若 text[i] 与 pattern[j] 两字符相等则继续往下走
        if (text[i] == pattern[j]) {
            i++;
            j++;
        } else {
            // 当 text[i] 与 pattern[j] 两字符不相等的时候，将 prefix table 数组中下标为 j 的值赋给 j
            j = prefix[j];
            // 当 j = -1，拿 pattern 数组的 -1 的位置来对准 i 的位置（把pattern 整体移动一格 就是 j + 1，同时移动 i + 1)
            if (-1 == j) {
                j++;
                i++;
            }
        }
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    char pattern[] = "ABABCABAA";
    char text[] = "ABABABCABAABABABAB";
    kmpSearch(text, pattern);
    return 0;
}