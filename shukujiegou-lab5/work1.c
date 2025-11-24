#include <stdio.h>
#include <stdlib.h>

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

    // u → v 尾插
    if (!G->vertices[u].firstedge)
        G->vertices[u].firstedge = p;
    else {
        ArcNode *q = G->vertices[u].firstedge;
        while (q->next) q = q->next;
        q->next = p;
    }

    // v → u 尾插（无向图）
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


//DFS 
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

//BFS
int visitedBFS[MaxVertexNum];

typedef struct {
    int data[100];
    int front, rear;
} Queue;

void InitQueue(Queue *Q) { Q->front = Q->rear = 0; }
int QueueEmpty(Queue Q) { return Q.front == Q.rear; }
void EnQueue(Queue *Q, int x) { Q->data[++Q->rear] = x; }
int DeQueue(Queue *Q) { return Q->data[++Q->front]; }

void BFS(ALGraph G, int v) {
    Queue Q;
    InitQueue(&Q);

    visitedBFS[v] = 1;
    printf("%d ", v);
    EnQueue(&Q, v);

    while (!QueueEmpty(Q)) {
        int u = DeQueue(&Q);
        ArcNode *p = G.vertices[u].firstedge;
        while (p) {
            int w = p->adjvex;
            if (!visitedBFS[w]) {
                visitedBFS[w] = 1;
                printf(" %d ",w); // BFS 生成树边 + 访问序列
                EnQueue(&Q, w);
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

    printf("\n----- DFS 遍历结果 -----\n访问序列：");
    for (int i = 1; i <= n; i++) visitedDFS[i] = 0;
    DFS(G, start);
    printf("\n");

    printf("\n----- BFS 遍历结果 -----\n访问序列 + 生成树边：");
    for (int i = 1; i <= n; i++) visitedBFS[i] = 0;
    BFS(G, start);
    printf("\n");

    return 0;
}
