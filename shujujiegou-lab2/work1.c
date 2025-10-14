#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef struct 
{
    int* base;
    int* top;
    int stacksize;
} SqStack;

// 初始化栈
int InitStack(SqStack *S) {
    S->base = (int *)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!S->base) {
        return 0; // 内存分配失败
    }
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

// 入栈操作
int Push(SqStack *S, int e) {
    // 如果栈满，增加容量
    if (S->top - S->base >= S->stacksize) {
        S->base = (int *)realloc(S->base, 
                    (S->stacksize + STACKINCREMENT) * sizeof(int));
        if (!S->base) {
            return 0; // 内存分配失败
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *(S->top) = e;
    S->top++;
    return 1;
}

// 出栈操作
int Pop(SqStack *S, int *e) {
    // 判断栈是否为空
    if (S->top == S->base) {
        return 0;
    }
    S->top--;
    *e = *(S->top);    
    return 1;
}

int tenzhuaneight(int a) {
    SqStack q;
    int c;
    if (a == 0) {
        printf("十进制0的八进制是: 0\n");
        return 0; 
    }    
    if (!InitStack(&q)) {
        printf("栈初始化失败！\n");
        return -1;
    }    
    int b = a;
    printf("转换过程：\n");
    printf("--------------------------------\n");    
    while (b != 0) {
        c = b % 8;
        printf("%d\t\t%d\t\t%d\n", b, b/8, c);
        Push(&q, c);
        b = b / 8;
    } 
    printf("\n八进制的结果是: ");
    while (q.top != q.base) {
        Pop(&q, &c);
        printf("%d", c);
    }
    printf("\n");
    
    free(q.base);
    return 0;
}

int main() {
    int num;
    printf("十进制转八进制转换\n");
    printf("请输入一个非负十进制整数: ");
    
    if (scanf("%d", &num) != 1 || num < 0) {
        printf("错误：请输入有效的非负整数！\n");
        return 1;
    }
    
    printf("\n开始转换十进制数 %d 为八进制...\n\n", num);
    tenzhuaneight(num);
    
    return 0;
}