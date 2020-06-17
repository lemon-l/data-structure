#include <iostream>
#include<Windows.h>
#include <stdio.h>
using namespace std;
typedef int KeyType;
typedef int InfoType;
typedef int ElemType;
typedef int Status;
#define OK 1
# define  MAXSIZE   100// 顺序表的最大长度

//顺序表定义存储表示
typedef struct
{
    KeyType key;
    InfoType otherinfo;
} SElemType;
typedef struct        //若后面不再用，可省略结构名
{
    SElemType *R;  //存储空间基址
    int    length;   //当前表长（特指元素个数）
} SSTable;
//定义操作函数1（初始化顺序表）
Status   InitList_ST(SSTable &ST)
{
    //构造一个空的线性表L。
    ST.R = new SElemType[MAXSIZE];
    if  ( ! ST.R )
        exit (2); // 存储分配失败
    ST.length = 0;           // 空表长度为0
    return 1;
}
int Length_ST(SSTable ST)
{
    return ST.length;
}
//顺序表插入
Status Insert_ST(SSTable &ST,int i,KeyType e)
{
    //ST.R[0].key=0;
    if((i<1)||(i>ST.length+1))
    {
        cout<<"位置不合法！"<<endl;
        return -1;   //i值不合法
    }
    else cout<<"插入成功！"<<endl;

    if(ST.length==MAXSIZE)
        return -1;
    for(int j=ST.length-1; j>=i; j--)
    {
        ST.R[j+1].key=ST.R[j].key;
    }
    ST.R[i-1].key=e;//将新元素e放入第i个位置
    ++ST.length;
    return 1;
}
//折半查找
int SearchBin(SSTable ST,KeyType key)
{
    int low=0;
    int high=ST.length-1;
    int seektime=1;
    int movetime=0;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(key==ST.R[mid].key)
        {
            cout<<"查找次数:"<<seektime<<endl;
            cout<<"移动次数:"<<movetime<<endl;
            return mid+1;
        }
        else if(key<ST.R[mid].key)
        {
            high=mid-1;
            seektime++;
            movetime=movetime+mid-(high+low)/2;
        }
        else
        {
            low=mid+1;
            seektime++;
            movetime=movetime-mid+(high+low)/2;
        }
    }
    return -1;
}
//定义操作函数2（销毁顺序表函数）
void Destroy_ST(SSTable &ST)
{
    if (ST.R)
        delete[ ] ST.R;    //释放存储空间
    ST.length=0;
    ST.R=NULL;
}
//二叉树的存储结构定义
typedef struct
{
    KeyType key;
    InfoType otherinfo;
} BElemType;

typedef struct BSTNode
{
    BElemType data;
    struct BSTNode *lchild,*rchild;
} BSTNode,*BSTree;

//二叉排序树的插入（）
void InsertBST(BSTree &T,BElemType e)
{
    BSTree S;
    if(!T)  //二叉树不空
    {
        S=new BSTNode;
        S->data=e;
        S->lchild=S->rchild=NULL;
        T=S;
    }
    else if(e.key<T->data.key)
        InsertBST(T->lchild,e);
    else if(e.key>T->data.key)
        InsertBST(T->rchild,e);
}
// 二叉排序树的创建
void CreatBST(BSTree &T)
{
    BElemType e;
    T=NULL;
    for(int i=1; i<=10; i++)
    {
        e.key=i;
        InsertBST(T,e);
    }
}
//二叉排序树的查找
int time=1;
BSTree SearchBST(BSTree BT,KeyType key)
{
    if(key==BT->data.key)
    {
        cout<<"查找次数为:"<<time<<endl;
        cout<<"移动次数为:"<<time-1<<endl;
        return BT;
    }
    else if(key<BT->data.key)
    {
        time++;
        return SearchBST(BT->lchild,key);
    }
    else
    {
        time++;
        return  SearchBST(BT->rchild,key);
    }
}
//二叉排序树的销毁
Status Destroy_BST(BSTree &BT)
{
    BSTree p,q;
    while(BT)
    {
        p=BT->rchild;
        q=BT->lchild;
        delete p;
        delete q;
    }
    return OK;
}
//显示二叉树
void show_BT(BSTree BT)
{
    if(BT)
    {
        show_BT(BT->lchild); //递归遍历左子树
        cout<<BT->data.key<<" "; //访问根结点
        show_BT(BT->rchild); //递归遍历右子树
    }
}
/*！！！排序*/
//直接插入排序
void InsertSort(SSTable &L)
{
    int comtime=0;//比较次数
    int movetime=0;//移动次数
    int m;
    for(int i=2; i<=L.length; ++i)
        if(L.R[i].key<L.R[i-1].key)//将L.r[i]插入有序子表
        {
            comtime++;
            L.R[0]=L.R[i]; // 复制为哨兵
            L.R[i]=L.R[i-1];//R[i-1]后移
            movetime++;
            for(m=i-2; L.R[0].key<L.R[m].key; --m)
            {
                comtime++;
                L.R[m+1]=L.R[m]; // 记录后移
                movetime++;
            }
            L.R[m+1]=L.R[0]; //插入到正确位置
        }
    cout<<"（比较次数:"<<comtime<<"  ";
    cout<<"移动次数:"<<movetime<<"）"<<endl;
}
//折半插入排序
void BInsertSort ( SSTable &L )
{
    int comtime=0;//比较次数
    int movetime=0;//移动次数
    for (int i = 2;  i <= L.length ; ++i )
    {
        L.R[0] = L.R[i];
        int low = 1 ;
        int high = i-1 ;
        int mid;
        while ( low <= high )
        {
            mid = ( low + high ) / 2 ;
            if(L.R[0].key < L.R[mid].key)
                high = mid -1 ;
            else
                low = mid + 1;
            comtime++;
        }
        for (int j=i-1; j>=high+1; --j )
        {
            movetime++;
            L.R[j+1] = L.R[j];
        }
        L.R[high+1] = L.R[0];
    }
    cout<<"（比较次数:"<<comtime<<"  ";
    cout<<"移动次数:"<<movetime<<"）"<<endl;
}

//希尔排序(其中某一趟的排序操作)
void  ShellInsert (SSTable &L,int dk)  //对顺序表L进行一趟增量为dk的Shell排序，dk为步长因子
{
    int j;
    int comtime=0;//比较次数
    int movetime=0;//移动次数
    for(int i=dk+1; i<=L.length; ++ i)
        if (L.R[i].key < L.R[i-dk].key)   //开始将r[i] 插入有序增量子表
        {
            {
                L.R[0]=L.R[i];//暂存在r[0]
                comtime++;
            }
            for(j=i-dk; j>0 &&(L.R[0].key<L.R[j].key); j=j-dk )
            {
                L.R[ j+dk ]=L.R[j];//关键字较大的记录在子表中后移
                movetime++;
                comtime++;
            }
            L.R[ j+dk ]=L.R[0];//在本趟结束时将r[i]插入到正确位置
        }
    cout<<"（比较次数:"<<comtime<<"  ";
    cout<<"移动次数:"<<movetime<<"）"<<endl;
}
//显示顺序表
void show_ST(SSTable ST)
{
    cout<<"{";
    for(int i=1; i<=ST.length; i++)
    {
        cout<<ST.R[i].key<<" ";
    }
    cout<<"}"<<endl;
}
void show_menu()
{
    cout<<"1----折半查找"<<endl;
    cout<<"2----二叉排序树查找"<<endl;
    cout<<"3----直接插入排序"<<endl;
    cout<<"4----折半插入排序"<<endl;
    cout<<"5----希尔排序"<<endl<<endl;


    cout<<"6----求长度"<<endl;
    cout<<"7----显示顺序表"<<endl;
    cout<<"8----显示二叉排序树(中序遍历)"<<endl;
    cout<<"9----退出"<<endl<<endl;
}
void mcopy(SSTable L1,SSTable L2)//L2=L1
{
    for(int i=1; i<=L1.length; i++)
    {
        L2.R[i].key=L1.R[i].key;
    }
}
int main()
{
    int oprate_code;
    show_menu();
    //建表
    SSTable ST,ST1,ST2,ST3;//顺序表正序1-10
    SSTable L,L1,L2,L3;//顺序表逆序10-1
    SSTable Ra,Ra1,Ra2,Ra3;//随机顺序表
    BSTree BT;//二叉排序树表
    //初始化线性函数调用
    InitList_ST(ST);
    InitList_ST(L);
    InitList_ST(Ra);
    ST.length=10;
    L.length=10;
    Ra.length=10;

    InitList_ST(ST1);
    InitList_ST(L1);
    InitList_ST(Ra1);
    ST1.length=10;
    L1.length=10;
    Ra1.length=10;

    InitList_ST(ST2);
    InitList_ST(L2);
    InitList_ST(Ra2);
    ST2.length=10;
    L2.length=10;
    Ra2.length=10;

    InitList_ST(ST3);
    InitList_ST(L3);
    InitList_ST(Ra3);
    ST3.length=10;
    L3.length=10;
    Ra3.length=10;
    CreatBST(BT);
    KeyType key;
    int dk;
    int j=1;

    for(int i=1; i<=ST.length; i++)  //ST顺序表正序1-10
    {
        ST.R[i].key=i;
    }
    for(int i=10; i>0; i--) //L顺序表逆序10-1
    {
        L.R[j].key=i;
        j++;
    }
    for(int i=1; i<=Ra.length; i++)  //Ra随机顺序表
    {
        Ra.R[i].key=rand()%10;
    }

    mcopy(ST,ST1);
    mcopy(ST,ST2);
    mcopy(ST,ST3);
    mcopy(L,L1);
    mcopy(L,L2);
    mcopy(L,L3);
    mcopy(Ra,Ra1);
    mcopy(Ra,Ra2);
    mcopy(Ra,Ra3);
    while(1)
    {
        cout<<"请输入操作代码：";
        cin>>oprate_code;
        if (oprate_code==1)//折半查找
        {

            cout<<"请输入要查找的关键字：";
            cin>>key;
            int locate=SearchBin(ST,key);
            if(locate==-1)
                cout<<"顺序表不存在该关键字"<<endl;
            else
                cout<<"该关键字在顺序表中的位置为："<<locate-1<<endl;
        }
        else if(oprate_code==2)//二叉排序树查找
        {

            cout<<"请输入要查找的关键字：";
            cin>>key;
            cout<<"该关键字在顺序表中的结点地址为："<<SearchBST(BT,key)<<endl;
        }
        else if(oprate_code==3)//直接插入排序
        {
            cout<<"排序前的顺序表为："<<endl;
            cout<<"正序：";
            show_ST(ST);
            cout<<"逆序：";
            show_ST(L);
            cout<<"随机序列：";
            show_ST(Ra);

            cout<<"直接插入排序后的顺序表为："<<endl;
            cout<<"正序：";
            InsertSort(ST1);
            show_ST(ST1);

            cout<<"逆序：";
            InsertSort(L1);
            show_ST(L1);

            cout<<"随机序列：";
            InsertSort(Ra1);
            show_ST(Ra1);
        }
        else if(oprate_code==4)//折半插入排序
        {

            cout<<"排序前的顺序表为："<<endl;
            cout<<"正序：";
            show_ST(ST);
            cout<<"逆序：";
            show_ST(L);
            cout<<"随机序列：";
            show_ST(Ra);

            cout<<"折半插入排序后的顺序表为："<<endl;
            cout<<"正序：";
            BInsertSort(ST2);
            show_ST(ST2);
            cout<<"逆序：";
            BInsertSort(L2);
            show_ST(L2);
            cout<<"随机序列：";
            BInsertSort(Ra2);
            show_ST(Ra2);
        }
        else if(oprate_code==5)//哈希排序
        {

            cout<<"请输入步长因子：";
            cin>>dk;
            cout<<"排序前的顺序表为："<<endl;
            cout<<"正序：";
            show_ST(ST);
            cout<<"逆序：";
            show_ST(L);
            cout<<"随机序列：";
            show_ST(Ra);

            cout<<"希尔排序后的顺序表为："<<endl;
            cout<<"正序：";
            ShellInsert(ST3,dk);
            show_ST(ST3);
            cout<<"逆序：";
            ShellInsert(L3,dk);
            show_ST(L3);
            cout<<"随机序列：";
            ShellInsert(Ra3,dk);
            show_ST(Ra3);
        }
        else if(oprate_code==6)
        {
            cout<<"顺序表长度为："<<ST.length<<endl;
        }
        else if(oprate_code==7)
        {
            if(ST.length==0)
                cout<<"当前顺序表为空表！"<<endl;
            else
            {
                show_ST(ST);
            }
        }
        else if(oprate_code==8)
        {
            cout<<"当前二叉排序树按中序遍历为:{ ";
            show_BT(BT);
            cout<<"}"<<endl;
        }
        else if(oprate_code==9)//退出
        {
            break;
        }
        else
        {
            cout<<"输入错误，请重新输入！"<<endl;
        }
    }
    Destroy_ST(ST);
    Destroy_ST(L);
    Destroy_ST(Ra);
    Destroy_BST(BT);
    return 0;
}
