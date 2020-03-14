#include <iostream>
#include <stdlib.h>
using namespace std;
typedef int ElemType;
typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define LIST_INIT_SIZE 100  // 线性表存储空间的初始分配量
#define LISTINCREMENT 10    // 线性表存储空间的分配增量
ElemType * newbase, *p, *q;
// 定义一个页面输出所有操作的函数
void show_function()
{
    cout << "1----清空线性表" << endl;
    cout << "2----判断线性表是否为空" << endl;
    cout << "3----求线性表长度" << endl;
    cout << "4----获取线性表指定位置元素" << endl;
    cout << "5----求前驱" << endl;
    cout << "6----求后继" << endl;
    cout << "7----在线性表指定位置插入元素" << endl;
    cout << "8----删除线性表指定位置元素" << endl;
    cout << "9----显示线性表" << endl;
    cout << "     退出，输出一个负数！" << endl;
}

// 顺序表的结构
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} SqList;

// 线性表初始化
Status InitList(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)exit(OVERFLOW);  //存储分配失败
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;  //初始存储容量
    return OK;
}

// 线性表的销毁
void DesList(SqList &L)
{
    if(L.elem) delete[]L.elem;
    L.length = 0;
    L.listsize = 0;
}

//1.清空线性表
Status ClearList(SqList &L)
{
    L.length = 0;
    return OK;
}

//2.判断线性表是否为空
bool IsEmpty(SqList L)
{
    if(L.length == 0)
        return true;
    else
        return false;
}

//3.求线性表长度
int ListLength(SqList L)
{
    return L.length;
}

//4.获取指定位置元素
Status GetElem(SqList L,int i, ElemType &e)
{
    if(i<1 || i>L.length)
        cout << "不存在" << endl;
    else
    {
        e = L.elem[i-1];
        return e;
    }
}

//5.求前驱
Status GetBefore(SqList L,int i,ElemType &e)
{
    if(i<1 || i>L.length)
    {
        cout << "不存在" << endl;
    }
    else
    {
        e = L.elem[i-2];
        return e;
    }
}

//6.求后继
Status GetAfter(SqList L,int i,ElemType &e)
{
    if(i<1 || i>L.length)
    {
        cout << "i值不合法" << endl;
    }
    else
    {
        e = L.elem[i];
        return e;
    }
}

//7.插入元素
Status InsList(SqList &L,int i,ElemType e)
{
    if(i<1 || i > L.length + 1)
    {
        cout << "i值不合法" << endl;
    }
    if(L.length >= L.listsize) // 存储空间不足，需要增加分配
    {
        newbase = (ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[i-1]);  //q为插入位置
    for(p=&(L.elem[L.length-1]); p>=q; --p)
        *(p+1)=*p;  // 插入位置之后的元素右移
    *q=e;
    ++L.length;  // 表的长度增加
    return OK;
}

//8.删除元素
Status DeList(SqList &L, int i, ElemType e)
{
    if(i<1 || i>L.length+1)
    {
        cout << "i值不合法" << endl;
        return ERROR;
    }
    q = &(L.elem[L.length-1]);
    for(p =&(L.elem[i-1]); p<=q; p++)
        *p = *(p+1);
    e = *q;
    --L.length;
    return OK;
}

//9.显示线性表
void ShowList(SqList L)
{
    for(int i=0; i<L.length; i++)
        cout << L.elem[i]<<" ";
    cout << endl;
}

// 主函数
int main()
{
    int choice;
    int i;
    ElemType e;
    show_function();
    SqList L;
    InitList(L);
    while(1)
    {
        cout << "请输入操作代码：";
        cin >> choice;
        if(choice < 0)
            break;
        switch(choice)
        {
        case 1:
            ClearList(L);
            break;
        case 2:
            if(IsEmpty(L))
                cout << "The List is empty." << endl;
            else
                cout << "The list is not empty." << endl;
            break;
        case 3:
            cout << "The length of the list is: " << ListLength(L) << endl;
            break;
        case 4:
            cout << "请输入指定的位置:";
            cin >> i;
            cout << GetElem(L,i,e) << endl;
            break;
        case 5:
            cout << "请输入指定的位置:";
            cin >> i;
            cout << GetBefore(L,i,e) << endl;
            break;
        case 6:
            cout << "请输入指定的位置:";
            cin >> i;
            cout << GetAfter(L,i,e) << endl;
            break;
        case 7:
            cout << "请输入插入位置及元素:";
            cin >> i >> e;
            InsList(L,i,e);
            break;
        case 8:
            cout << "请输入删除的位置：";
            cin >> i;
            DeList(L,i,e);
            break;
        case 9:
            cout << "The elements are: ";
            ShowList(L);
            break;
        default:
            cout << "输入有误，请重新选择" << endl;
            break;
        }
    }
    DesList(L);
    return 0;
}
