// C Program To Implement Brute Force Algorithm
#include <stdio.h>
#include <string.h>

// 返回子串 sub 在主串 str 中第 pos 个字符之后的位置，若不存在，返回 -1
// 时间复杂度为 O(n * m)
int bruteForceMatching(char str[], char sub[], int pos) {
    int STR_LENGTH = strlen(str);
    int SUB_LENGTH = strlen(sub);
    if (pos < 0 || pos > STR_LENGTH) {
        return -1;
    }
    int i = pos;
    int j = 0;
    while (i < STR_LENGTH && j < SUB_LENGTH) {
        // 两字母相等则继续，否则重新开始匹配
        if (str[i] == sub[j]) {
            i++;
            j++;
        } else {
            // i 退回到上次匹配首位的下一位
            i = i - j + 1;
            // j 退回子串 sub 的首位
            j = 0;
        }
    }
    // 如果 j 值大于等于子串 sub 的长度，表示匹配完成
    if (j >= SUB_LENGTH) {
        //返回第一个匹配的位置，由于下标从0开始，所以加上1
        return i - SUB_LENGTH + 1;
    } else {
        return -1;
    }
}

int main() {
    char str[] = "good google";
    char sub[] = "google";
    printf("%d \n", bruteForceMatching(str, sub, 0));
    return 0;
}