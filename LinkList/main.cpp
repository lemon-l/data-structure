#include <iostream>
#include <stdlib.h>
using namespace std;
#define OK 1
#define ERROR 0
typedef int Status;
typedef int ElemType;

// 定义一个页面可以选择操作
void show_function()
{
    cout << "0----创建单链表" << endl;
    cout << "1----按序号查找" << endl;
    cout << "2----按值查找" << endl;
    cout << "3----插入数据元素" << endl;
    cout << "4----删除指定数据" << endl;
    cout << "5----有序链表归并" << endl;
    cout << "     退出，输出一个负数！" << endl;
}

// 链表存储结构
typedef struct LNode
{
    ElemType data; // 数据域
    struct LNode *next; // 指针域
} LNode, *LinkList;

// 初始化单链表
Status InitList(LinkList &L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}

// 0. 尾插法创建单链表
void CreateList(LinkList &L,int n)
{
    LinkList p;
    L = new LNode;
    L->next = NULL;
    LinkList q = L;
    for(int i=1; i<=n; i++)
    {
        p = new LNode;
        cin >> p->data;
        p->next = NULL;
        q->next = p;
        q = p;
    }
}

// 单链表长度
int LengthList(LinkList L,int i)
{
    i = 0;
    LinkList p = L->next;
    while(p)
    {
        ++i;
        p = p->next;
    }
    return i;
}

// 1. 按序号查找
Status GetElem(LinkList L,int i, ElemType &e)
{
    LinkList p = L->next;
    int j = 1;
    while(p && j <i)
    {
        // 向后扫描，直到p指向第i个元素或p为空
        p = p->next;
        ++j;
    }
    if(!p || j > i) return ERROR;
    e = p->data;
    return e;
}

// 2. 按值查找
LNode *LocateElem(LinkList L, ElemType e)
{
    LNode *p;
    p = L->next;
    while(p && p->data != e)
        p = p->next;
    return p; // 返回L中值为e的数据元素位置，查找失败返回NULL
}

// 3. 插入数据元素
Status ListInsert(LinkList L,int i, ElemType e)
{
    LinkList p = L;
    int j = 0;
    while(p && j < i-1)
    {
        p = p->next;
        ++j;
    }
    if(!p || j > i-1)
        return ERROR;    // 小于1或者大于表长加1
    LinkList s = new LNode; // 生成新节点
    s->data = e;   // 将结点*s的数据域置为e
    s->next = p->next; // 将结点*s插入L中
    p->next = s;
    return OK;
}

// 4. 删除指定数据
Status ListDelete(LinkList L, int i,ElemType &e)
{
    LinkList p = L;
    LinkList r;
    int j = 0;
    while(p->next && j < i-1)
    {
        p = p->next;
        ++j;
    }
    if(!(p->next) || j > i-1) return ERROR; //删除位置不合理
    r = p->next; //临时保存被删结点的地址以备释放
    p->next = r->next; //改变删除结点前驱节点的指针域
    e = r->data;
    delete r; //释放结点
    return OK;
}

// 5. 有序链表合并
void MergeList(LinkList &La, LinkList &Lb, LinkList &Lc)
{
    LinkList pa,pb,pc;
    pa = La->next;
    pb = Lb->next;
    Lc = pc = La;
    while(pa && pb)
    {
        if(pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
        pc->next = pa?pa:pb;
        delete Lb;
    }
}

// 显示单链表
void ShowList(LinkList L)
{
    LinkList p;
    p = L->next;
    while(p)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// 调用合并
void InvokeMerge()
{
    int a, b;
    LinkList La,Lb,Lc;
    InitList(La);
    InitList(Lb);
    InitList(Lc);
    cout << "请输入第一个有序链表的长度: ";
    cin >> a;
    CreateList(La,a);
    ShowList(La);
    cout << "请输入第二个有序链表的长度: ";
    cin >> b;
    CreateList(Lb,b);
    ShowList(Lb);
    MergeList(La,Lb,Lc);
    cout << "合并后的有序链表为：";
    ShowList(Lc);
}

int main()
{
    int choice;
    int i;
    int s;
    ElemType e;
    LinkList L;
    InitList(L);
    show_function();

    while(1)
    {
        cout << "请输入操作代码：";
        cin >> choice;
        if(choice < 0)
            break;
        switch(choice)
        {
        case 0:
            cout << "创建的单链表的长度：";
            cin >> s;
            CreateList(L,s);
            cout << "创建的单链表为：";
            ShowList(L);
            break;
        case 1:
            cout << "请输入指定的位置：";
            cin >> i;
            while(i<0 || i>LengthList(L,s))
            {
                cout << "输入有误，请重新输入" << endl;
                cout << "请输入指定的位置：";
                cin >> i;
            }
            cout << GetElem(L,i,e) << endl;
            break;
        case 2:
            cout << "请输入你要查找的值：";
            cin >> e;
            cout << LocateElem(L,e) << endl;
            break;
        case 3:
            cout << "请选择要插入的位置：";
            cin >> i;
            while(i<0 || i>LengthList(L,s))
            {
                cout << "输入有误，请重新输入" << endl;
                cout << "请输入插入的位置：";
                cin >> i;
            }
            cout << "请输入要插入的元素值：";
            cin >> e;
            ListInsert(L,i,e);
            cout << "插入后单链表为：";
            ShowList(L);
            cout << endl;
            break;
        case 4:
            cout << "请选择要删除的位置：";
            cin >> i;
            while(i<0 || i>LengthList(L,s))
            {
                cout << "输入有误，请重新输入" << endl;
                cout << "请输入删除的位置：";
                cin >> i;
            }
            ListDelete(L,i,e);
            cout << "删除后单链表为：";
            ShowList(L);
            break;
        case 5:
            InvokeMerge();
            break;
        default:
            cout << "输入有误，请重新选择" << endl;
            break;
        }
    }
}

