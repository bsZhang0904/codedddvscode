#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 2  // 停车场最大容量
#define PRICE_PER_HOUR 5  // 每小时费用
// 汽车结构体
typedef struct {
    int license;    // 车牌号
    int arriveTime; // 到达时间
} Car;
// 栈结构（停车场）
typedef struct {
    Car data[MAX_SIZE];
    int top;
} Stack;
// 队列节点
typedef struct QueueNode {
    Car car;
    struct QueueNode* next;
} QueueNode;
// 队列结构（便道）
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;
// 栈操作函数
void initStack(Stack* s) {
    s->top = -1;
}
int isStackEmpty(Stack* s) {
    return s->top == -1;
}
int isStackFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}
int push(Stack* s, Car car) {
    if (isStackFull(s)) return 0;
    s->data[++(s->top)] = car;
    return 1;
}
Car pop(Stack* s) {
    Car emptyCar = {-1, -1};
    if (isStackEmpty(s)) return emptyCar;
    return s->data[(s->top)--];
}
Car peek(Stack* s) {
    Car emptyCar = {-1, -1};
    if (isStackEmpty(s)) return emptyCar;
    return s->data[s->top];
}
// 队列操作函数
void initQueue(Queue* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}
int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}
void enqueue(Queue* q, Car car) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->car = car;
    newNode->next = NULL;   
    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}
Car dequeue(Queue* q) {
    Car emptyCar = {-1, -1};
    if (isQueueEmpty(q)) return emptyCar;
    
    QueueNode* temp = q->front;
    Car car = temp->car;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return car;
}
// 显示停车场状态
void displayStatus(Stack* parkingLot, Queue* waitingLine) {
    printf("\n=== 当前状态 ===\n");
    
    // 显示停车场
    printf("停车场(%d/%d): ", parkingLot->top + 1, MAX_SIZE);
    if (isStackEmpty(parkingLot)) {
        printf("空");
    } else {
        for (int i = 0; i <= parkingLot->top; i++) {
            printf("%d号车 ", parkingLot->data[i].license);
        }
    }
    printf("\n");   
    // 显示便道
    printf("便道: ");
    if (isQueueEmpty(waitingLine)) {
        printf("空");
    } else {
        QueueNode* current = waitingLine->front;
        while (current != NULL) {
            printf("%d号车 ", current->car.license);
            current = current->next;
        }
    }
    printf("\n================\n\n");
}
// 处理车辆到达
void handleArrival(Stack* parkingLot, Queue* waitingLine, int license, int time) {
    Car newCar = {license, time};
    
    if (!isStackFull(parkingLot)) {
        // 停车场有空位
        push(parkingLot, newCar);
        printf("车牌%d的汽车停入停车场，位置：%d\n", license, parkingLot->top + 1);
    } else {
        // 停车场已满，进入便道
        enqueue(waitingLine, newCar);
        printf("车牌%d的汽车停入便道，排队位置：%d\n", license, waitingLine->size);
    }
}
// 处理车辆离开
void handleDeparture(Stack* parkingLot, Stack* tempStack, Queue* waitingLine, 
                    int license, int time) {
    int found = 0;
    int movedCars = 0;
    
    // 在停车场中查找要离开的车辆
    while (!isStackEmpty(parkingLot)) {
        Car currentCar = pop(parkingLot);
        
        if (currentCar.license == license) {
            // 找到要离开的车
            found = 1;
            int parkingTime = time - currentCar.arriveTime;
            int fee = parkingTime * PRICE_PER_HOUR;
            
            printf("车牌%d的汽车离开停车场\n", license);
            printf("停留时间：%d小时，应交费用：%d元\n", parkingTime, fee);
            break;
        } else {
            // 不是要离开的车，暂时移到临时栈
            push(tempStack, currentCar);
            movedCars++;
        }
    }  
    // 将临时栈中的车移回停车场
    while (!isStackEmpty(tempStack)) {
        Car car = pop(tempStack);
        push(parkingLot, car);
    }    
    if (!found) {
        printf("错误：未找到车牌%d的汽车\n", license);
        return;
    }   
    // 如果便道有车，让第一辆车进入停车场
    if (!isQueueEmpty(waitingLine)) {
        Car nextCar = dequeue(waitingLine);
        nextCar.arriveTime = time; // 更新进入停车场的时间
        push(parkingLot, nextCar);
        printf("车牌%d的汽车从便道进入停车场\n", nextCar.license);
    }
}
int main() {
    Stack parkingLot;    // 停车场栈
    Stack tempStack;     // 临时栈（用于车辆离开时）
    Queue waitingLine;   // 等待队列（便道）    
    // 初始化数据结构
    initStack(&parkingLot);
    initStack(&tempStack);
    initQueue(&waitingLine);   
    printf("=== 停车场管理系统 ===\n");
    printf("停车场容量：%d辆车\n", MAX_SIZE);
    printf("收费标准：%d元/小时\n", PRICE_PER_HOUR);
    printf("命令格式：A 车牌号 时间（到达）或 D 车牌号 时间（离开）或 E 0 0（结束）\n\n");   
    char command;
    int license, time;    
    while (1) {
        printf("请输入命令: ");
        scanf(" %c", &command);
        
        if (command == 'E') {
            scanf("%d %d", &license, &time);
            printf("程序结束\n");
            break;
        }      
        scanf("%d %d", &license, &time);
        switch (command) {
            case 'A': // 车辆到达
                handleArrival(&parkingLot, &waitingLine, license, time);
                break;
                
            case 'D': // 车辆离开
                handleDeparture(&parkingLot, &tempStack, &waitingLine, license, time);
                break;
                
            default:
                printf("错误命令！请使用 A（到达）、D（离开）或 E（结束）\n");
                continue;
        }       
        // 显示当前状态
        displayStatus(&parkingLot, &waitingLine);
    } 
    // 清理便道内存
    while (!isQueueEmpty(&waitingLine)) {
        dequeue(&waitingLine);
    }  
    return 0;
}