#include <stdio.h>
#include <stdlib.h>
// 二叉树节点结构体定义
typedef struct BiTNode {
    char data;               // 节点数据
    struct BiTNode *lchild;  // 左子树指针
    struct BiTNode *rchild;  // 右子树指针
} BiTNode, *BiTree;
// 全局变量，用于跟踪输入字符串的当前位置
int index_input = 0;
// 递归建立二叉树（先序遍历方式）
// 使用空格字符表示空节点
void CreateBiTree(BiTree *T, char *input) {
    // 读取当前字符
    char ch = input[index_input++];
    
    // 如果遇到空格字符，表示该节点为空
    if (ch == ' ') {
        *T = NULL;
    } else {
        // 创建新节点
        *T = (BiTree)malloc(sizeof(BiTNode));
        if (!*T) {
            printf("内存分配失败！\n");
            exit(1);
        }
        // 先序遍历：先处理根节点
        (*T)->data = ch;
        // 递归创建左子树
        CreateBiTree(&(*T)->lchild, input);
        // 递归创建右子树
        CreateBiTree(&(*T)->rchild, input);
    }
}
// 先序遍历（递归）
void PreOrderTraverse(BiTree T) {
    if (T != NULL) {
        printf("%c", T->data);  // 访问根节点
        PreOrderTraverse(T->lchild);  // 递归遍历左子树
        PreOrderTraverse(T->rchild);  // 递归遍历右子树
    }
}
// 中序遍历（递归）
void InOrderTraverse(BiTree T) {
    if (T != NULL) {
        InOrderTraverse(T->lchild);  // 递归遍历左子树
        printf("%c", T->data);  // 访问根节点
        InOrderTraverse(T->rchild);  // 递归遍历右子树
    }
}
// 后序遍历（递归）
void PostOrderTraverse(BiTree T) {
    if (T != NULL) {
        PostOrderTraverse(T->lchild);  // 递归遍历左子树
        PostOrderTraverse(T->rchild);  // 递归遍历右子树
        printf("%c", T->data);  // 访问根节点
    }
}
// 释放二叉树内存
void DestroyBiTree(BiTree *T) {
    if (*T != NULL) {
        DestroyBiTree(&(*T)->lchild);  // 递归释放左子树
        DestroyBiTree(&(*T)->rchild);  // 递归释放右子树
        free(*T);  // 释放当前节点
        *T = NULL; // 避免野指针
    }
}
int main() {
    BiTree T = NULL;
    char input[100];
    printf("请输入二叉树的先序遍历序列（使用空格表示空节点）：\n");
    printf("例如：ABC  DE G  F   （注意空格表示空节点）\n");
    gets(input);  // 读取用户输入    
    // 重置输入索引
    index_input = 0;   
    // 建立二叉树
    CreateBiTree(&T, input);   
    // 先序遍历并输出结果
    printf("\n先序遍历结果：");
    PreOrderTraverse(T);
    printf("\n");   
    // 中序遍历并输出结果
    printf("中序遍历结果：");
    InOrderTraverse(T);
    printf("\n");   
    // 后序遍历并输出结果
    printf("后序遍历结果：");
    PostOrderTraverse(T);
    printf("\n");    
    // 释放内存
    DestroyBiTree(&T);   
    system("pause");
    return 0;
}