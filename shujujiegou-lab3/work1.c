#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100  // 定义字符串最大长度

// 字符串模式匹配函数（暴力匹配算法）

int patternMatch(char *s, char *t, int pos) {
    // 关键部分实现 - 暴力匹配算法
    int i = pos;  // 主串s的索引（从pos开始，pos>=1）
    int j = 1;    // 模式串t的索引（从1开始）
    int s_len = s[0];  // 主串长度存储在s[0]
    int t_len = t[0];  // 模式串长度存储在t[0]

    while (i <= s_len && j <= t_len) {
        // 当前字符匹配成功，两个索引都向后移动
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            // 匹配失败，主串回退到本趟开始位置的下一个字符，模式串回退到开头
            i = i - j + 2;  // i-j是本趟开始位置，+2到下一个位置
            j = 1;          // 模式串回退到第一个字符
        }
    }
    
    // 判断匹配是否成功
    if (j > t_len) {
        // 匹配成功，返回匹配起始位置（从1开始计数）
        return i - t_len;  // 计算匹配起始位置
    } else {
        // 匹配失败
        return -1;
    }
}

int main() {
    char s[MAX_SIZE]; 
    char t[MAX_SIZE]; 
    char temp_s[MAX_SIZE];  
    char temp_t[MAX_SIZE];  
    int position;
    int s_len, t_len;
    printf("请输入主字符串: ");
    gets(temp_s);  // 读取主字符串到临时数组
    printf("请输入模式串: ");
    gets(temp_t);  // 读取模式串到临时数组
    // 处理主串：s[0]存储长度，从s[1]开始存储字符
    s_len = strlen(temp_s);
    s[0] = s_len;  // 在s[0]中存储主串长度
    for (int i = 0; i < s_len; i++) {
        s[i + 1] = temp_s[i];  // 字符从位置1开始存储
    }
    // 处理模式串：t[0]存储长度，从t[1]开始存储字符
    t_len = strlen(temp_t);
    t[0] = t_len;  // 在t[0]中存储模式串长度
    for (int i = 0; i < t_len; i++) {
        t[i + 1] = temp_t[i];  // 字符从位置1开始存储
    }
    // 调用模式匹配函数
    position = patternMatch(s, t, 1); 
    // 输出结果
    if (position != -1) {
        printf("匹配成功！模式串在主串中的起始位置是: %d\n", position);  // 位置已经从1开始计数
    } else {
        printf("匹配失败！主串中不包含该模式串\n");
    }
    return 0;
}
