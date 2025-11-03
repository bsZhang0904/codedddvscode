#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
// 二叉树结点定义
typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;
// 栈结构体定义
typedef struct {
    Node* data[MAXSIZE];
    int top;
} Stack;
// 栈操作函数
void initStack(Stack* s) {
    s->top = -1;
}
int isEmpty(Stack* s) {
    return s->top == -1;
}
void push(Stack* s, Node* node) {
    if (s->top < MAXSIZE - 1)
        s->data[++(s->top)] = node;
}
Node* pop(Stack* s) {
    if (isEmpty(s))
        return NULL;
    return s->data[(s->top)--];
}
Node* peek(Stack* s) {
    if (isEmpty(s))
        return NULL;
    return s->data[s->top];
}
// 创建新结点
Node* newNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}
// ---------------------- 非递归遍历 ----------------------
// 1. 先序遍历（根 -> 左 -> 右）
void preorder(Node* root) {
    Stack s;
    initStack(&s);
    Node* p = root;
    while (p != NULL || !isEmpty(&s)) {
        while (p != NULL) {
            printf("%c ", p->data);  // 访问根
            push(&s, p);
            p = p->left;
        }
        if (!isEmpty(&s)) {
            p = pop(&s);
            p = p->right;
        }
    }
}
// 2. 中序遍历（左 -> 根 -> 右）
void inorder(Node* root) {
    Stack s;
    initStack(&s);
    Node* p = root;
    while (p != NULL || !isEmpty(&s)) {
        while (p != NULL) {
            push(&s, p);
            p = p->left;
        }
        if (!isEmpty(&s)) {
            p = pop(&s);
            printf("%c ", p->data);  // 访问根
            p = p->right;
        }
    }
}
// 3. 后序遍历（左 -> 右 -> 根）
void postorder(Node* root) {
    Stack s;
    initStack(&s);
    Node *p = root, *lastVisit = NULL;
    while (p != NULL || !isEmpty(&s)) {
        while (p != NULL) {
            push(&s, p);
            p = p->left;
        }
        Node* topNode = peek(&s);
        // 若右子树为空或已访问，则访问当前结点
        if (topNode->right == NULL || topNode->right == lastVisit) {
            printf("%c ", topNode->data);
            pop(&s);
            lastVisit = topNode;
        } else {
            p = topNode->right;
        }
    }
}
// ---------------------- 主函数 ----------------------
int main() {
    Node* A = newNode('A');
    Node* B = newNode('B');
    Node* C = newNode('C');
    Node* D = newNode('D');
    Node* E = newNode('E');
    Node* F = newNode('F');
    A->left = B; A->right = C;
    B->left = D; B->right = E;
    C->left = F;
    printf("先序遍历(非递归)：");
    preorder(A);
    printf("\n");
    printf("中序遍历(非递归)：");
    inorder(A);
    printf("\n");
    printf("后序遍历(非递归)：");
    postorder(A);
    printf("\n");
    return 0;
}
