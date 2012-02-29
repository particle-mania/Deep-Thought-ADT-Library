//#include<iostream>
#include<stdio.h>
#include<stdlib.h>


/*
    Object : Binary Tree of Integers
    
    Date : 26/01/2012
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

tree* create(int d)
{
    tree* p =(tree *)malloc(sizeof(tree));
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
                print(T->left,0);
                print(T->right,0); break;
        case 2: print(T->left,0);
                print(T->right,0);printf("%d ",T->data);
                printf("%d ",T->data); break;
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
             

    
int main()
{
    int I;
    scanf("%d",&I);
    tree* T = create(I);
    while(I!=10)
    {
        scanf("%d",&I);
        BST_insert(T,I);
        print(T,0);
    }
    scanf("%d",&I);
    return 0;
} 
       
