#include<stdio.h>
#include <stdlib.h>
typedef struct Node {
    int id;           // 编号（从1开始）
    int password;     // 密码
    struct Node* next;
} Node;
Node* createNode(int id, int password) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("内存分配失败！\n");
        exit(1);
    }
    newNode->id = id;
    newNode->password = password;
    newNode->next = NULL;
    return newNode;
}// 创建新节点
Node* createCircularList(int n, int passwords[]) {
    if (n == 0) return NULL;
    Node* head = createNode(1, passwords[0]);
    Node* current = head;
    for (int i = 1; i < n; i++) {
        current->next = createNode(i + 1, passwords[i]);
        current = current->next;
    }
    current->next = head;  // 形成环
    return head;
}// 构建循环链表
void josephus(int n, int passwords[], int m) {
    Node* list = createCircularList(n, passwords);
    Node* current = list;
    Node* prev = NULL;
    printf("出列顺序为：");
    while (current != NULL && n > 0) {
        // 如果当前链表只剩一个人
        if (current->next == current) {
            printf("%d", current->id);
            free(current);
            break;
        }
        // 找到报数起点前一个节点，以便删除 current
        // 移动 m-1 步（因为起始点也算一步）
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        // 此时 current 是要删除的人
        printf("%d ", current->id);
        // 更新 m 为当前人的密码
        m = current->password;
        // 删除 current 节点
        Node* toDelete = current;
        if (prev == NULL) { // 第一次还没设置 prev
            // 找到尾部指向 current 的前驱
            Node* temp = current;
            while (temp->next != current) {
                temp = temp->next;
            }
            prev = temp;
        }
        prev->next = current->next;
        current = current->next;
        free(toDelete);
        n--;
    }
    printf("\n");
}// 打印出列顺序
int main() {
    int n;
    int m;
    printf("请输入人数 n（≤30）: ");
    scanf("%d", &n);
    if (n <= 0 || n > 30) {
        printf("人数必须在 1 到 30 之间！\n");
        return 1;
    }
    int* passwords = (int*)malloc(n * sizeof(int));
    printf("请输入 %d 个人的密码（正整数）:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &passwords[i]);
    }
    printf("请输入初始报数上限 m: ");
    scanf("%d", &m);
    josephus(n, passwords, m);
    free(passwords);
    return 0;
}