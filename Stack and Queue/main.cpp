#include <iostream>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define size 100
#define incresize 10
#define MaxSize 10
#define SElemType int
#define Status int
using namespace std;
typedef int DataType;

/* 1. 顺序栈 */
typedef struct Stack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

// 初始化
Status InitStack(SqStack &s)
{
    s.base = new SElemType[size]; // 动态分分配最大容量
    if(!s.base) return FALSE;
    s.top = s.base;
    s.stacksize = size;
    return TRUE;
}

// 入栈
Status PushStack(SqStack &s,SElemType e)
{
    if(s.top - s.base == s.stacksize) return FALSE; // 栈满
    *(s.top++) = e;
    return TRUE;
}

// 出栈
Status PopStack(SqStack &s,SElemType &e)
{
    if(s.top == s.base) return FALSE;
    e=*(--s.top);
    cout << "出栈成功！" << endl;
    return TRUE;
}

// 取栈顶元素
Status GetTop(SqStack &s,SElemType &e)
{
    if(s.top == s.base) return FALSE;
    else e = *(s.top - 1);
    cout << "栈顶元素为：" << e << endl;
    return TRUE;
}

// 显示栈内元素
Status ShowStack(SqStack s)
{
    if(s.top == s.base) return FALSE;
    int *p;
    p = s.top;
    cout << "当前顺序栈元素有：";
    while(p>s.base)
    {
        p--;
        cout << *p << " ";
    }
    cout << endl;
}

void OperSqStack()
{
    int select;
    SElemType e;
    SqStack S;
    InitStack(S);
    cout << "1------入栈" << endl;
    cout << "2------出栈" << endl;
    cout << "3------取栈顶元素" << endl;
    cout << "选择操作：";
    cin >> select;
    while(select > 0)
    {
        switch(select)
        {
        case 1:
            cout << "输入入栈元素：";
            cin >> e;
            PushStack(S,e);
            ShowStack(S);
            break;
        case 2:
            PopStack(S,e);
            ShowStack(S);
            break;
        case 3:
            GetTop(S,e);
            break;
        default:
            cout << "输入错误"<< endl;
        }
        cout << "选择操作：";
        cin >> select;
    }
}
/* 2. 链栈 */
typedef struct SNode
{
    int data;
    struct SNode *next;
} SNode, *LinkStack;

LinkStack top, base;

int ShowLinkStack()
{
    LinkStack p;
    cout << "当前链栈元素有：";
    p = top;
    if(p == base)
        return FALSE;
    while(p != NULL)
    {
        cout << p->data<< " ";
        p = p->next;
    }
    cout << endl;
}

void PushLinkStack(int e)//入栈
{
    LinkStack p;
    p = (LinkStack)malloc(sizeof(SNode));
    p->data = e;
    p->next = top;
    top = p;
}

int PopLinkStack()//出栈
{
    LinkStack p;
    int e;
    if(top == base)
        return FALSE;
    p = top;
    e = p->data;
    top = top->next;
    free(p);
    cout << "出栈成功!" << endl;
}

void GetLinkTop()
{
    cout << "栈顶元素为：" << top->data << endl;
}

void OperLinkStack()
{
    int select,e;
    LinkStack p;
    cout << "1------入栈" << endl;
    cout << "2------出栈" << endl;
    cout << "3------取栈顶元素" << endl;
    cout << "选择操作：";
    cin >> select;
    while(select > 0)
    {
        switch(select)
        {
        case 1:
            cout << "输入入栈元素：";
            cin >> e;
            PushLinkStack(e);
            ShowLinkStack();
            break;
        case 2:
            PopLinkStack();
            ShowLinkStack();
            break;
        case 3:
            GetLinkTop();
            break;
        default:
            cout << "输入错误"<< endl;
            break;
        }
        cout << "选择操作：";
        cin >> select;
    }
}

/* 3. 链队列 */
typedef struct Node
{
    DataType data; /*数据域*/
    struct Node* next; /*指针域*/
} LinkQueueNode;
typedef struct
{
    LinkQueueNode* front;
    LinkQueueNode* rear;
} LinkQueue;

int InitLinkQueue(LinkQueue *Q)
{
    Q->front = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(Q->front != NULL)
    {
        Q->rear = Q->front; /*头指针和尾指针都指向头结点*/
        Q->front->next = NULL;
        return TRUE;
    }
    else return FALSE;
}

// 判空
int IsLinkQueueEmpty(LinkQueue* Q)
{
    if(Q->front->next == NULL) return TRUE;
    else return FALSE;
}

// 入队
int EnterLinkQueue(LinkQueue *Q,DataType x)
{
    LinkQueueNode* NewNode = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
    if(NewNode != NULL)
    {
        NewNode->data = x; /*将数据元素赋值给结点的数据域*/
        NewNode->next = NULL; /*将结点的指针域置空*/
        Q->rear->next = NewNode; /*在队尾插入节点*/
        Q->rear = NewNode; /*修改队尾指针*/
        return TRUE;
    }
    else return FALSE;
}

// 出队
void DeleteQueue(LinkQueue *Q,DataType* x)
{
    if(IsLinkQueueEmpty(Q)) cout << "队列为空" << endl;
    LinkQueueNode* p = Q->front->next;
    *x = p->data; /*将要出对的元素赋给data*/
    Q->front->next = p->next;
    if(Q->rear == p)
        Q->rear = Q->front;
    free(p);
    cout << "出队列成功!" << endl;
}

// 获取队头元素
DataType LinkQueueFront(LinkQueue *Q)
{
    if(Q->front == Q->rear) return FALSE;
    return Q->front->next->data;
}

// 显示队列
int PrintLinkQueue(LinkQueue *Q)
{
    LinkQueueNode *p;
    p = Q->front->next;
    if(p == NULL)
        return FALSE;
    cout << "当前链队列元素有：";
    while(p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void OperLinkQueue()
{
    int select;
    DataType e;
    LinkQueue Q;
    InitLinkQueue(&Q);
    cout << "1------入队" << endl;
    cout << "2------出队" << endl;
    cout << "3------取队头元素" << endl;
    cout << "选择操作：";
    cin >> select;
    while(select > 0)
    {
        switch(select)
        {
        case 1:
            cout << "输入入栈元素：";
            cin >> e;
            EnterLinkQueue(&Q,e);
            PrintLinkQueue(&Q);
            break;
        case 2:
            DeleteQueue(&Q,&e);
            PrintLinkQueue(&Q);
            break;
        case 3:
            cout << "队头的元素为：" << LinkQueueFront(&Q) << endl;
            break;
        default:
            cout << "输入错误"<< endl;
        }
        cout << "选择操作：";
        cin >> select;
    }
}

/* 4. 循环队列 */
typedef struct SeqQueue
{
    DataType Queue[MaxSize];
    int front;
    int rear;
} SeqCirQueue;

void InitSeqCirQueue(SeqCirQueue *Q)
{
    Q->front = Q->rear = 0;
}

// 入队
int EnterSeqCirQueue(SeqCirQueue *Q,DataType x)
{
    if((Q->rear+1)%MaxSize == Q->front) return FALSE; // 队列已满
    Q->Queue[Q->rear] = x;
    Q->rear = (Q->rear+1)%MaxSize; /*重新设置队尾指针*/
}

// 出队
int DeleteSeqCirQueue(SeqCirQueue *Q,DataType* x)
{
    if(Q->front == Q->rear) return FALSE; /*队列为空*/
    *x = Q->Queue[Q->front];
    Q->front = (Q->front + 1)%MaxSize; /*重新设置头指针*/
    cout << "出队列成功！" << endl;
    return TRUE;
}

// 取队首元素
int GetHead(SeqCirQueue *Q,DataType* x)
{
    if(Q->front == Q->rear) return FALSE; /*队列为空*/
    *x = Q->Queue[Q->front];
    return *x;
}

void PrintSeqCirQueue(SeqCirQueue *Q)
{
    int i = Q->front;
    cout << "当前循环队列元素有：";
    if(Q->front < Q->rear)
    {
        for(; i<Q->rear; i++)
            cout << Q->Queue[i] << " ";
    }
    else
    {
        for(; i<Q->rear+MaxSize; i++)
            cout << Q->Queue[i] << " ";
    }
    cout << endl;
}

void OperSeqCirQueue()
{
    int select;
    DataType e;
    SeqCirQueue Q;
    InitSeqCirQueue(&Q);
    cout << "1------入队" << endl;
    cout << "2------出队" << endl;
    cout << "3------取队头元素" << endl;
    cout << "选择操作：";
    cin >> select;
    while(select > 0)
    {
        switch(select)
        {
        case 1:
            cout << "输入入栈元素：";
            cin >> e;
            EnterSeqCirQueue(&Q,e);
            PrintSeqCirQueue(&Q);
            break;
        case 2:
            DeleteSeqCirQueue(&Q,&e);
            PrintSeqCirQueue(&Q);
            break;
        case 3:
            cout << "队头的元素为：" << GetHead(&Q,&e) << endl;
            break;
        default:
            cout << "输入错误"<< endl;
        }
        cout << "选择操作：";
        cin >> select;
    }
}

int main()
{
    cout << "1------顺序栈操作" << endl;
    cout << "2------链栈操作" << endl;
    cout << "3------链队列操作" << endl;
    cout << "4------循环队列操作" << endl;
    cout << "     退出，输出一个负数！" << endl;
    cout << "请输入操作代码：";
    int choice;
    cin >> choice;
    while(choice > 0)
    {
        switch(choice)
        {
        case 1:
            OperSqStack();
            break;
        case 2:
            OperLinkStack();
            break;
        case 3:
            OperLinkQueue();
            break;
        case 4:
            OperSeqCirQueue();
        default:
            cout << "输入有误，请重新选择" << endl;
            break;
        }
        cout << "请输入操作代码：";
        cin >> choice;
    }
    return 0;
}
