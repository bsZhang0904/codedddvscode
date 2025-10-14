#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 100
// 栈结构定义
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;
// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}
// 判断栈是否为空
bool isEmpty(Stack *s) {
    return s->top == -1;
}
// 判断栈是否已满
bool isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}
// 入栈操作
bool push(Stack *s, char ch) {
    if (isFull(s)) {
        printf("栈已满！\n");
        return false;
    }
    s->data[++(s->top)] = ch;
    return true;
}
// 出栈操作
bool pop(Stack *s, char *ch) {
    if (isEmpty(s)) {
        return false;
    }
    *ch = s->data[(s->top)--];
    return true;
}
// 获取栈顶元素
bool getTop(Stack *s, char *ch) {
    if (isEmpty(s)) {
        return false;
    }
    *ch = s->data[s->top];
    return true;
}
// 检查括号是否匹配
bool checkBrackets(char *expression) {
    Stack s;
    initStack(&s);
    
    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];
        
        // 如果是左括号，压入栈中
        if (ch == '(' || ch == '[') {
            if (!push(&s, ch)) {
                return false; // 栈满
            }
        }
        // 如果是右括号
        else if (ch == ')' || ch == ']') {
            char topChar;
            
            // 栈为空，遇到右括号不合法
            if (!getTop(&s, &topChar)) {
                return false;
            }
            
            // 检查括号是否匹配
            if ((ch == ')' && topChar == '(') || 
                (ch == ']' && topChar == '[')) {
                // 匹配成功，弹出栈顶元素
                pop(&s, &topChar);
            } else {
                // 括号不匹配
                return false;
            }
        }
    }
    return isEmpty(&s);
}
// 过滤字符串，只保留括号字符
void filterBrackets(char *input, char *output) {
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '(' || input[i] == ')' || 
            input[i] == '[' || input[i] == ']') {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}
void check() {
    char input[100];
    char filtered[100];
    
    printf("\n括号检查(输入q退出)\n");
    printf("==============================\n");
    
    while (1) {
        printf("\n请输入括号序列: ");        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }        
        // 去除换行符
        input[strcspn(input, "\n")] = '\0';
        // 检查是否退出
        if (strcmp(input, "q") == 0) {
            break;
        }
        
        // 检查输入是否合法
        bool validInput = true;
        for (int i = 0; input[i] != '\0'; i++) {
            if (!(input[i] == ' ' || input[i] == '(' || input[i] == ')' || 
                input[i] == '[' || input[i] == ']')) {
                validInput = false;
                break;
            }
        }        
        if (!validInput) {
            printf("错误：输入只能包含圆括号、方括号和空格！\n");
            continue;
        }        
        // 过滤空格
        filterBrackets(input, filtered);        
        // 检查匹配
        if (checkBrackets(filtered)) {
            printf("结果: ✓ 匹配\n");
        } else {
            printf("结果: ✗ 此串括号匹配不合法\n");
        }
    }
}
int main(){
    check();
    return 0;
}