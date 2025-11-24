#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // 引入bool类型

#define MaxVertexNum 30

typedef int VertexType; 
typedef int InfoType;

// 邻接点结点类型
typedef struct ArcNode {
    int adjvex;               // 邻接点编号
    struct ArcNode *next;     // 下一个邻接点
} ArcNode;

// 表头结点类型
typedef struct Vnode {
    VertexType vertex;        // 顶点编号（1~n）
    ArcNode *firstedge;       // 边表头指针
} Vnode, AdjList[MaxVertexNum];

// 图类型
typedef struct {
    AdjList vertices;         
    int vexnum, arcnum;       // 顶点数、边数
} ALGraph;

// 定义栈元素类型
typedef int ElemType;

// 栈结构体
typedef struct {
    ElemType data[MaxVertexNum]; // 数据域
    int top;                     // 栈顶指针
} Stack;

void InitGraph(ALGraph *G, int n) {
    G->vexnum = n;
    G->arcnum = 0;
    for (int i = 1; i <= n; i++) {
        G->vertices[i].vertex = i;
        G->vertices[i].firstedge = NULL;
    }
}

void AddEdge(ALGraph *G, int u, int v) {
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = v;
    p->next = NULL;

    if (!G->vertices[u].firstedge)
        G->vertices[u].firstedge = p;
    else {
        ArcNode *q = G->vertices[u].firstedge;
        while (q->next) q = q->next;
        q->next = p;
    }

    ArcNode *p2 = (ArcNode *)malloc(sizeof(ArcNode));
    p2->adjvex = u;
    p2->next = NULL;

    if (!G->vertices[v].firstedge)
        G->vertices[v].firstedge = p2;
    else {
        ArcNode *k = G->vertices[v].firstedge;
        while (k->next) k = k->next;
        k->next = p2;
    }
}
void InitStack(Stack *S){
    S->top = -1;
}
// 判断栈是否为空
int StackEmpty(Stack S) {
    return S.top == -1;
}

// 入栈操作
void Push(Stack *S, ElemType e) {
    if (S->top < MaxVertexNum - 1) { // 防止溢出
        S->data[++(S->top)] = e;
    }
}

// 出栈操作
ElemType Pop(Stack *S) {
    if (!StackEmpty(*S)) {
        return S->data[(S->top)--];
    } else {
        printf("栈为空，无法出栈\n");
        return -1; // 错误码或异常处理
    }
}
void DFS_NonRecursive(ALGraph G, int v) {
    Stack S;
    InitStack(&S);
    bool visited[MaxVertexNum] = {false}; // 访问标记数组
    
    Push(&S, v); // 起始顶点入栈
    visited[v] = true;
    printf("%d ", v); // 打印起始顶点
    
    while (!StackEmpty(S)) {
        int current = Pop(&S); // 取栈顶元素并出栈
        ArcNode *p = G.vertices[current].firstedge;
        
        while (p) { // 遍历current的所有邻接点
            int adjVex = p->adjvex;
            if (!visited[adjVex]) { // 若未被访问过
                visited[adjVex] = true;
                printf("(%d -> %d) ", current, adjVex); // 输出边
                printf("%d ", adjVex); // 输出访问的顶点
                
                Push(&S, current); // 当前顶点再次入栈以备回溯
                Push(&S, adjVex); // 新顶点入栈
                break; // 退出循环，进入下一个顶点的探索
            }
            p = p->next;
        }
    }
}
int main() {
    int n, m;
    ALGraph G;
    printf("输入结点数 n(<=30)：");
    scanf("%d", &n);

    InitGraph(&G, n);

    printf("输入边数 m：");
    scanf("%d", &m);

    printf("输入每条边（u v）：\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        AddEdge(&G, u, v);
    }

    int start;
    printf("输入遍历起点：");
    scanf("%d", &start);

    printf("\n----- 非递归 DFS 遍历结果 -----\n访问序列：");
    DFS_NonRecursive(G, start);
    printf("\n");

    return 0;
}