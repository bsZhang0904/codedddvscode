#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxVertexNum 30

// 边结点
typedef struct ArcNode {
    int adjvex;               // 邻接点编号
    struct ArcNode *next;     // 指向下一个邻接点
} ArcNode;

// 顶点结点
typedef struct VNode {
    int vertex;               // 顶点编号（1 ~ n）
    ArcNode *firstedge;       // 指向第一条出边
} VNode, AdjList[MaxVertexNum];

// 有向图结构
typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

// 队列结构（用于 BFS）
typedef struct {
    int data[100];
    int front, rear;
} Queue;

// 初始化队列
void InitQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

bool QueueEmpty(Queue Q) {
    return Q.front == Q.rear;
}

void EnQueue(Queue *Q, int x) {
    Q->data[++(Q->rear)] = x;
}

int DeQueue(Queue *Q) {
    return Q->data[++(Q->front)];
}

// 初始化有向图（顶点编号从 1 开始）
void InitGraph(ALGraph *G, int n) {
    G->vexnum = n;
    G->arcnum = 0;
    for (int i = 1; i <= n; i++) {
        G->vertices[i].vertex = i;
        G->vertices[i].firstedge = NULL;
    }
}

// 添加有向边 u -> v（尾插法）
void AddEdge(ALGraph *G, int u, int v) {
    ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
    p->adjvex = v;
    p->next = NULL;

    if (G->vertices[u].firstedge == NULL) {
        G->vertices[u].firstedge = p;
    } else {
        ArcNode *q = G->vertices[u].firstedge;
        while (q->next != NULL) {
            q = q->next;
        }
        q->next = p;
    }
    G->arcnum++;
}

// 递归 DFS
int visitedDFS[MaxVertexNum];
void DFS(ALGraph G, int v) {
    visitedDFS[v] = 1;
    printf(" %d ", v);

    ArcNode *p = G.vertices[v].firstedge;
    while (p) {
        int w = p->adjvex;
        if (!visitedDFS[w]) {
            //printf("(%d -> %d) ", v, w);   // DFS 生成树边
            DFS(G, w);
        }
        p = p->next;
    }
}

// BFS
void BFS(ALGraph G, int start) {
    bool visited[MaxVertexNum] = {false};
    Queue Q;
    InitQueue(&Q);

    visited[start] = true;
    printf("%d ", start);
    EnQueue(&Q, start);

    while (!QueueEmpty(Q)) {
        int u = DeQueue(&Q);
        ArcNode *p = G.vertices[u].firstedge;
        while (p != NULL) {
            int w = p->adjvex;
            if (!visited[w]) {
                visited[w] = true;
                printf("%d ", w);
                EnQueue(&Q, w);
            }
            p = p->next;
        }
    }
}

// 主函数
int main() {
    int n, m;
    ALGraph G;

    printf("输入有向图的结点数 n(<=30)：");
    scanf("%d", &n);
    InitGraph(&G, n);

    printf("输入弧数 m：");
    scanf("%d", &m);

    printf("输入每条有向边（u v），表示 u -> v：\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            AddEdge(&G, u, v);
        }
    }

    int start;
    printf("输入遍历起点：");
    scanf("%d", &start);

    if (start < 1 || start > n) {
        printf("起点无效！\n");
        return 1;
    }

    // DFS 遍历
    bool visited[MaxVertexNum] = {false};
    printf("\n----- DFS 遍历结果（递归，有向图）-----\n");
    printf("访问序列：");
    DFS(G, start);
    printf("\n");

    // BFS 遍历
    printf("\n----- BFS 遍历结果（有向图）-----\n");
    printf("访问序列：");
    BFS(G, start);
    printf("\n");

    return 0;
}