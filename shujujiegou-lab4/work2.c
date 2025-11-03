#include <stdio.h>
#include <stdlib.h>
// 定义二叉树结点结构体
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;
// 创建新结点
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
// 凹入表形式横向打印二叉树
// 参数：root 当前结点，space 当前缩进量
void printTree(Node* root, int space) {
    if (root == NULL)
        return;

    // 每一层的缩进间距
    int COUNT = 5;
    space += COUNT;

    // 先打印右子树（在上方）
    printTree(root->right, space);

    // 打印当前结点前的空格
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%c\n", root->data);

    // 再打印左子树（在下方）
    printTree(root->left, space);
}
int main() {
    Node* A = newNode('A');
    Node* B = newNode('B');
    Node* C = newNode('C');
    Node* D = newNode('D');
    Node* E = newNode('E');
    Node* F = newNode('F');
    A->left = B; A->right = C;
    B->right = D; E->right = F;
    C->left = E;
    // 打印二叉树
    printf("按凹入表形式横向打印二叉树:\n");
    printTree(A, 0);
    return 0;
}
