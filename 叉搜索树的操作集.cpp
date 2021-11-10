#include<iostream>
using namespace std;

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );


Position Find( BinTree BST, ElementType X ){
    if(BST){
        if(X > BST->Data){
            return Find(BST->Right, X);
        }
        else if(X < BST->Data){
            return Find(BST->Left, X);
        }
        else{
            return BST;
        }
    }
    else 
        return NULL;
}

Position FindMin( BinTree BST ){
    if(BST){
        if(BST->Left)
            return FindMin(BST->Left);
        else
            return BST;
    }
    else{
        return NULL;
    }
}

Position FindMax( BinTree BST ){
    if(BST){
        if(BST->Right){
            return FindMax(BST->Right);
        }
        else{
            return BST;
        }
    }
    else{
        return NULL;
    }
}

BinTree Insert( BinTree BST, ElementType X ){
    if(BST){
        if(X > BST->Data){
            BST->Right = Insert(BST->Right, X);
        }
        else if(X < BST->Data){
            BST->Left = Insert(BST->Left, X);
        }
    }
    else{
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    return BST;
}

BinTree Delete( BinTree BST, ElementType X ){
    if(!BST){
        printf("Not Found\n");
        return NULL;
    }
    else{
        BinTree temp;
        if(X > BST->Data){
            BST->Right = Delete(BST->Right, X);
        }
        else if(X < BST->Data){
            BST->Left = Delete(BST->Left, X);
        }
        else{
            if(BST->Left == NULL && BST->Right == NULL){
                temp = BST;
                free(temp);
                BST = NULL;
            }
            else if(BST->Left != NULL && BST->Right != NULL){
                temp = FindMin(BST->Right);
                BST->Data = temp->Data;
                BST->Right = Delete(BST->Right, temp->Data);
            }
            else{
                temp = BST;
                if(BST->Left){
                    BST = BST->Left;
                }
                else
                    BST = BST->Right;
                free(temp);
            }
        }
        return BST;
    }
    //return BST;
}