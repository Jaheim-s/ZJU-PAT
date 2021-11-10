#include<iostream>

using namespace std;
typedef struct node *Tree;
typedef struct node{
    int data;
    int height;
    Tree left;
    Tree right;
}tree_node;

int AVL_height(Tree);
int get_BalanceFactor(Tree);
Tree AVL_RotateRight(Tree);
Tree AVL_RotateLeft(Tree);
Tree Tree_insert(Tree, int);
Tree Tree_delete(Tree, int);
Tree AVL_Reblance(Tree);
int Find_max(Tree);

int main(){
    int Num;
    cin >> Num;
    int data;
    Tree AVL = NULL;
    for(int i = 0;i < Num;i++){
        cin >> data;
        AVL = Tree_insert(AVL, data);
    }
    cout << AVL->data;
    cin >> data;
    AVL = Tree_delete(AVL, data);
    return 0;
}

Tree AVL_Rebalance(Tree AVL){
    int factor = get_BalanceFactor(AVL);
    if(factor > 1 || factor < -1){
        if(factor > 1){
            if(get_BalanceFactor(AVL->left) > 0){ //左左
                AVL = AVL_RotateRight(AVL);
            }
            else{ //左右
                AVL->left = AVL_RotateLeft(AVL->left);
                AVL = AVL_RotateRight(AVL);
            }
        }
        else{
            if(get_BalanceFactor(AVL->right) < 0){ //右右
                AVL = AVL_RotateLeft(AVL);
            }
            else{ //右左
                AVL->right = AVL_RotateRight(AVL->right);
                AVL = AVL_RotateLeft(AVL);
            }
        }
    }
    return AVL;
}

int Find_max(Tree AVL){
    if(!AVL){
        return 0;
    }
    if(AVL->left)
        return Find_max(AVL->left);
    return AVL->data;
}

Tree Tree_delete(Tree AVL, int data){
    if(AVL){
        if(AVL->data > data)
            AVL->left = Tree_delete(AVL->left, data);
        if(AVL->data < data)
            AVL->right = Tree_delete(AVL->right, data);
        else{
            if(AVL->left && AVL->right){
                int data_temp = Find_max(AVL->left);
                AVL->data = data_temp;
                AVL->left = Tree_delete(AVL->left, data_temp);
            }
            else{
                Tree temp = AVL;
                if(AVL->left)
                    AVL = AVL->left;
                else if(AVL->right)
                    AVL = AVL->right;
                else
                    AVL = NULL;
                free(temp);
            }
        }
        AVL = AVL_Rebalance(AVL);
    }
    AVL->height = -1;
    AVL->height = AVL_height(AVL);
    return AVL;
}

Tree Tree_insert(Tree AVL, int data){
    if(!AVL){
        AVL = new tree_node;
        AVL->data = data;
        AVL->left = NULL;
        AVL->right = NULL;
    }
    else{
        if(AVL->data > data)
                AVL->left = Tree_insert(AVL->left, data);
        else if(AVL->data < data)
                AVL->right = Tree_insert(AVL->right, data);
        else
            return AVL;
    }
    AVL->height = -1;
    AVL->height = AVL_height(AVL);
    AVL = AVL_Rebalance(AVL);
    return AVL;
}

int AVL_height(Tree AVL){
    int height_left, height_right;
    if(AVL){
        if(AVL->height > -1){
            return AVL->height;
        }
        height_left = AVL_height(AVL->left);
        height_right = AVL_height(AVL->right);
        return (height_right > height_left? height_right:height_left) + 1;
    }
    else{
        return -1;
    }
}

int get_BalanceFactor(Tree AVL){
    if(!AVL){
        return 0;
    }
    else{
        if(AVL->left == NULL || AVL->right==NULL){
            int null = -1;
            if(AVL->left){
                return AVL->left->height - null;
            }
            else if(AVL->right){
                return null - AVL->right->height;
            }
            else
                return null - null;
        }
        return AVL->left->height - AVL->right->height;
    }
}

Tree AVL_RotateRight(Tree AVL){ //右旋
    Tree temp = AVL->left;
    AVL->left = temp->right;
    temp->right = AVL;
    AVL->height = -1; //需要更新高度
    temp->height = -1; // 需要更新高度
    AVL->height = AVL_height(AVL);
    temp->height = AVL_height(temp);
    return temp;
}

Tree AVL_RotateLeft(Tree AVL){ //左旋
    Tree temp = AVL->right;
    AVL->right = temp->left;
    temp->left = AVL;
    AVL->height = -1;
    temp->height = -1;
    AVL->height = AVL_height(AVL);
    temp->height = AVL_height(temp);
    return temp;

}