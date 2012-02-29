//#include<iostream>
#include<stdio.h>
#include<stdlib.h>


/*
    Object : Binary Tree of Integers
    
    Date : 25/02/2012
    Author : particle.mania
    
    Insert : 
    Delete : 
    Query : 
    Additional Operations :
*/

//using namespace std;

typedef struct node{
        int data;
        int tag;
        struct node * left;
        struct node * right;
        }tree;
        
typedef struct cons{
        tree* alpha;
        struct cons * next;
        int tag;
        }cons;
        
typedef struct queue{
        cons* head;
        cons* tail;
        }Q;

tree* create(int d)
{
    tree* p =(tree*)malloc(sizeof(tree));
    p->left=NULL;
    p->right=NULL;
    p->data=d;
    return p;
}
    
void print(tree* T, int mode)
{
    if(T==NULL)
        return;
    switch(mode)
    {
        case 0: print(T->left,0);
                printf("%d ",T->data);
                print(T->right,0); break;
        case 1: printf("%d ",T->data);
                print(T->left,1);
                print(T->right,1); break;
        case 2: print(T->left,2);
                print(T->right,2);
                printf("%d ",T->data); break;
    }
}

Q* createQ(tree* T)
{
    Q* q=(Q*)malloc(sizeof(Q));
    q->head=(cons*)malloc(sizeof(cons));
    q->tail=q->head;
    q->head->alpha=T;
    q->head->next=NULL;
    return q;
}

void EnQ(Q* qu, tree* T)
{
    if(T==NULL)
        return;
    cons* C = (cons*)malloc(sizeof(cons));
    C->alpha=T;
    C->next=NULL;
    qu->tail->next=C;
    qu->tail=C;
    if(qu->head==NULL)
        qu->head=qu->tail;
}

tree* DeQ(Q* qu)
{
    if(qu->head==NULL)
        return NULL;
    cons* C = qu->head;
    qu->head=qu->head->next;
    return C->alpha;
}

void depthorder(tree* T)
{
    Q* q = createQ(T);
    while(1)
    {
        tree* t = DeQ(q);
        if(t==NULL)
            break;
        printf("%d ",t->data);
        EnQ(q,t->left);
        EnQ(q,t->right);
    }
}

tree* BST_insert(tree* T, int d)
{
    if(T==NULL)
        return create(d);
    else
    {
        if(d > T->data)
            T->right=BST_insert(T->right,d);
        else
            T->left=BST_insert(T->left,d);
    }
    return T;
}
             
tree* Unique(int* preorder, int* inorder, int size)
{
    if(size==0)
        return NULL;
    int p=preorder[0];
    int i;
    for(i=0;i<size;i++)
        if(inorder[i]==p)
            break;
    tree* T = create(p);
    T->left=Unique(preorder+1,inorder,i);
    T->right=Unique(preorder+i+1,inorder+i+1,size-i-1);
    return T;
}

tree* Cartesian(int* space, int size)
{
    if(size==0)
        return NULL;
    int i, min=0;
    for(i=0;i<size;i++)
        if(space[i]<space[min])
            min=i;
    tree* T=create(space[min]);
    T->left=Cartesian(space,min);
    T->right=Cartesian(space+min+1,size-min-1);
    return T;
}

void d_order_func(tree* T, Q* qu, int m)
{
    if(T==NULL)
        return;
    if(m==0)
    {
        EnQ(qu,T);
        return;
    }
    d_order_func(T->left,qu,m-1);
    d_order_func(T->right,qu,m-1);    
}

void d_order_print(tree* T, int m)
{
    if(T==NULL)
        return;
    if(m==0)
        return;
    else
    {
        printf("%d ",T->data);
        d_order_print(T->left,m-1);
        d_order_print(T->right,m-1);
    }
}

void d_order(tree* T, int L)
{
    Q* q = createQ(T);
    tree* tmp = DeQ(q);
    while(1)
    {
        tree* t = DeQ(q);
        if(t==NULL)
            break;
        d_order_func(t,q,L);
        d_order_print(t,L);
    }
}

int DP_fillmax(tree* T)
{
    if(T==NULL)
        return -10000;
    int L = DP_fillmax(T->left);
    int R = DP_fillmax(T->right);
    T->tag = (L>R)?(L):(R);
    int M = (T->tag > T->data)?(T->tag):(T->data);
    T->tag = M;
    return M;
}

int DP_fillmin(tree* T)
{
    if(T==NULL)
        return 10000;
    int L = DP_fillmin(T->left);
    int R = DP_fillmin(T->right);
    T->tag = (L<R)?(L):(R);
    int M = (T->tag < T->data)?(T->tag):(T->data);
    T->tag = M;
    return M;
}

int DP_fillheight(tree* T)
{
    if(T==NULL)
        return -1;
    int L = DP_fillheight(T->left);
    int R = DP_fillheight(T->right);
    int M = (L>R)?(L):(R);
    T->tag = M+1;
    return M+1;
}

int ifBST_left(tree* T)
{
    // Pre-requisite : DP_fillmax
    if(T==NULL)
        return 1;
    if(T->left==NULL)
        return 1;
    if(T->data > T->left->tag)
    {
        int L = ifBST_left(T->left);
        int R = ifBST_left(T->right);
        return L&&R;
    }
    else return 0;
}

int ifBST_right(tree* T)
{
    // Pre-requisite : DP_fillmin
    if(T==NULL)
        return 1;
    if(T->right==NULL)
        return 1;
    if(T->data < T->right->tag)
    {
        int L = ifBST_right(T->left);
        int R = ifBST_right(T->right);
        return L&&R;
    }
    else return 0;
}

int ifBST(tree* T)
{
    int tmp=DP_fillmax(T);
    int L = ifBST_left(T);
    int tmp1=DP_fillmin(T);
    int R = ifBST_right(T);
    return L&&R;
}

int AVLfailnot(tree* T)
{
    // Pre-requisite : DP_fillheight
    if(T==NULL)
        return 1;
    if((T->left==NULL)&&(T->right==NULL))
        return 1;
    if(T->left==NULL)
        return (T->right->tag==0);
    if(T->right==NULL)
        return (T->left->tag==0);
    return ((T->right->tag - T->left->tag)*(T->right->tag - T->left->tag)==1);    
}    

int AVLfailEnQ(tree* T, int* A)
{
    int count=0;
    int tmp=DP_fillheight(T);
    Q* q = createQ(T);
    while(1)
    {
        tree* t = DeQ(q);
        if(t==NULL)
            break;
        if(AVLfailnot(t)==0)
            A[count++]=t->data;
        EnQ(q,t->left);
        EnQ(q,t->right);
    }
    return count;
}
     
    
    
int main()
{
    int N,T, A[1000], B[1000], C[1000], i, p, q, L;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(i=0;i<N;i++)
            scanf("%d",&A[i]);
        for(i=0;i<N;i++)
            scanf("%d",&B[i]);
        tree* t=Unique(B,A,N);
        p = AVLfailEnQ(t,C);
        q = ifBST(t);
        printf("%d\n%d\n",ifBST(t),(q==0)?(0):(p==0));
        if((p>0)&&(q==1))
        {
            for(i=0;i<p;i++)
                printf("%d ",C[i]);
            printf("\n");
        }
    }
    //scanf("%d",&T);
    return 0;
} 
       
