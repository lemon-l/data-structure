#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef char Elemtype;
typedef int Status;

// 二叉树的链表结点存储类型定义
typedef struct Node
{
    Elemtype data;
    struct Node *Lchild; // 左孩子
    struct Node *Rchild; // 右孩子
} BitNode,*BiTree;

//栈的顺序存储定义
typedef BiTree SElemType;
typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

// 初始化二叉树
Status InitBiTree(BiTree &T)
{
    T = NULL;
    return OK;
}
// 创建二叉树
Status CreateBiTree(BiTree &T)
{
    Elemtype ch;
    ch=getchar();
    if (ch==' ') T = NULL;
    else
    {
        if(!(T=(BitNode *)malloc(sizeof(BitNode))))
            exit(OVERFLOW);
        T->data = ch;              // 生成根结点
        CreateBiTree(T->Lchild);      // 构造左子树
        CreateBiTree(T->Rchild);      // 构造右子树
    }
    return OK;
}

// 先序遍历
Status PreOrderTraverse(BiTree T,Status(*Visit)(Elemtype e))
{
    if(T)
    {
        if(Visit(T->data))
            if(PreOrderTraverse(T->Lchild,Visit))
                if(PreOrderTraverse(T->Rchild,Visit))
                    return OK;
        return ERROR;
    }
    else return OK;
}

// 中序遍历
Status InOrderTraverse(BiTree T,Status(*Visit)(Elemtype e))
{
    if(T)
    {
        if(InOrderTraverse(T->Lchild,Visit))
            if(Visit(T->data))
                if(InOrderTraverse(T->Rchild,Visit))
                    return OK;
        return ERROR;
    }
    else return OK;
}

// 后序遍历
Status PostOrderTraverse(BiTree T,Status(*Visit)(Elemtype e))
{
    if(T)
    {
        if(PostOrderTraverse(T->Lchild,Visit))
            if(PostOrderTraverse(T->Rchild,Visit))
                if(Visit(T->data)) return OK;
        return ERROR;
    }
    else return OK;
}

// 层次遍历,采用队列作为辅助结构
Status LevelOrderTraverse(BiTree T,Status(*Visit)(Elemtype e))
{
    BitNode *Queue[100],*p = T;
    int front = 0,rear = 0;
    if(p!= NULL)
    {
        Queue[++rear] = p;
        while(front < rear)
        {
            p = Queue[++front];
            Visit(p->data);
            if(p->Lchild != NULL)
                Queue[++rear] = p->Lchild; // 左结点入队
            if(p->Rchild != NULL)
                Queue[++rear] = p->Rchild; // 右结点入队
        }
        return OK;
    }
    return ERROR;
}

// 非递归中序遍历
/*1. 构造一个空栈*/
Status InitStack(SqStack S)
{
    S.base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!S.base)
    {
        printf("栈溢出!\n");
        exit(OVERFLOW);
    }
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return OK;
}
/*2. 进栈*/
Status Push(SqStack S,SElemType e)
{
    if(S.top - S.base >= S.stacksize)
    {
        S.base = (SElemType *)realloc(S.base,(S.stacksize + STACKINCREMENT) *sizeof(SElemType));
        if(!S.base)
        {
            printf("栈溢出!\n");
            return OVERFLOW;
        }
        S.top = S.base + S.stacksize;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return OK;
}

Status StackEmpty(SqStack S)
{
    if(S.top == S.base)
        return TRUE;
    else return FALSE;
}

/*3. 出栈*/
Status Pop(SqStack S,SElemType e)
{
    if(StackEmpty(S))
        return ERROR;
    e = *(--S.top);
    return OK;
}


Status AnotherInOrderTraverse(BiTree T,Status(*Visit)(Elemtype e))
{
    SqStack S;
    BiTree p;
    p = T;
    InitStack(S);
    while(p || !StackEmpty(S))
    {
        if(p)
        {
            Push(S,p);
            p = p->Lchild;
        }
        else
        {
            Pop(S,p);
            if(!Visit(p->data)) return ERROR;
            p = p->Rchild;
        }
    }
    return OK;
}

// 高度
Status CountLevels(BiTree T)
{
    int l = 0;
    int r = 0;
    if(T)
    {
        l = CountLevels(T->Lchild);
        r = CountLevels(T->Rchild);
        if(l > r) return l+1;
        else return r+1;
    }
    else return 0;
}

// 叶子结点个数
Status CountLeafs(BiTree T,int &leaves)
{
    if(T)
    {
        if(T->Lchild == NULL && T->Rchild == NULL)
            leaves++;
        CountLeafs(T->Lchild,leaves);
        CountLeafs(T->Rchild,leaves);
        return OK;
    }
    else return ERROR;
}

// 显示元素
Status PrintElement(Elemtype e)
{
    printf("%c",e);
    return OK;
}

int main()
{
    BiTree T;
    int i,n = 0;
    printf("请输入数据（0代表空树）：");
    CreateBiTree(T);
    CountLeafs(T,n);
    printf("叶子结点的个数为：%d",n);
    printf("\n树的高度为：%d\n",CountLevels(T));
    printf("\n先序遍历：");
    PreOrderTraverse(T,PrintElement);
    printf("\n中序遍历：");
    InOrderTraverse(T,PrintElement);
    printf("\n后序遍历：");
    PostOrderTraverse(T,PrintElement);
    printf("\n层次遍历：");
    LevelOrderTraverse(T,PrintElement);
    printf("\n非递归中序遍历：");
    AnotherInOrderTraverse(T,PrintElement);
    return 0;
}
