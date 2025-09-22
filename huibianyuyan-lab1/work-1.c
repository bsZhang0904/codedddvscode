#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct city{
    char cityname[30];
    double x,y;
    struct city*next;
}city;//定义城市
city* initlist(){
    city*head = (city*)malloc(sizeof(city));
    head->next = NULL;
    return head;
}//初始化链表
void insertnewcity(city *head, const char *cityname, double x, double y)
{    city *newcity = (city *)malloc(sizeof(city));
    strcpy(newcity->cityname, cityname);
    newcity->x = x;
    newcity->y = y;
    newcity->next = NULL;
    /* 找到当前链表末尾 */
    city *p = head;
    while (p->next != NULL)        // 一直走到最后一个结点
        p = p->next;
    p->next = newcity;             // 挂在尾巴
}//实现链表的插入
int findcity(city*head,const char*cityname,double *x,double *y){
    city*p = head->next;
    while(p != NULL){
        if(strcmp(p->cityname,cityname)== 0){
            *x = p->x;
            *y = p->y;
            return 1;
            //通过比较名字来确定是否找到坐标
        }
        p = p->next;//指针后移继续寻找
    }
    printf_s("未找到城市对应坐标");
    return 0;//未找到城市
}//依据城市名字找对应坐标
void finddistance(city*head,double px,double py,double D){
    city*p = head->next;
    int find = 0;
    while(p != NULL){
        double distance = sqrt((p->x-px)*(p->x-px)+(p->y - py) * (p->y - py));
        if (distance<=D){
            printf("城市：%s,坐标:(%.2f, %.2f)，距离：%.2f\n", 
                p->cityname, p->x, p->y, distance);
                find++;
        }
        p = p->next;        
    }
    if(find = 0){        
        printf("在 %.2f 范围内未找到城市。\n", D);
    }
}//给定一个位置坐标P和一个距离D，返回所有与P的距离小于等于D的城市。
int deletecity(city*head,const char*cityname){
    city*p = head;
    while(p->next != NULL){
        if (strcmp(p->next->cityname, cityname) == 0) {
            city* temp = p->next;
            p->next = temp->next;
            free(temp);//通过定义一个temp来实现数据的删除
            return 1; // 删除成功
        }
        p = p->next;
    }
    return 0;//未找到城市的情况
}//删除一个城市
int updatecity(city* head,const char* cityname, double newX, double newY) {
    city* p = head->next;
    while (p != NULL) {
        if (strcmp(p->cityname, cityname) == 0) {
            p->x = newX;
            p->y = newY;
            return 1; // 更新成功
        }
        p = p->next;
    }
    return 0; // 未找到
}
int main(){
city *list = initlist();
insertnewcity(list, "北京",  116.4, 39.9);
insertnewcity(list, "上海",  121.5, 31.2);
insertnewcity(list, "广州",  113.3, 23.1);
insertnewcity(list, "深圳",  114.1, 22.5);
insertnewcity(list, "成都",  104.1, 30.6);
insertnewcity(list, "杭州",  120.2, 30.3);
insertnewcity(list, "武汉",  114.3, 30.6);
insertnewcity(list, "西安",  108.9, 34.3);
insertnewcity(list, "苏州",  120.6, 31.3);
insertnewcity(list, "天津",  117.2, 39.1);
insertnewcity(list, "南京",  118.8, 32.1);
insertnewcity(list, "重庆",  106.6, 29.6);
insertnewcity(list, "长沙",  112.9, 28.2);
insertnewcity(list, "郑州",  113.6, 34.7);
insertnewcity(list, "青岛",  120.4, 36.1);
insertnewcity(list, "大连",  121.6, 38.9);
    double x,y;
    if(findcity(list, "上海", &x, &y)){
        printf("上海坐标：%.2f, %.2f\n", x, y);
    }
    printf("\n距离 (120, 30) 200km 内的城市：\n");
    finddistance(list, 120, 30, 200);
    deletecity(list, "青岛");
    updatecity(list, "北京", 116.4074, 39.9042);
}

