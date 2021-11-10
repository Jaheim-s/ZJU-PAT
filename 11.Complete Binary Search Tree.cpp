#include<iostream>
#include<math.h>
#include<queue>

using namespace std;
typedef struct node *Tree;
typedef struct node{
    int data;
    Tree left;
    Tree right;
}tree_node;

void Quicksort(Tree, int, int);
int Paritition(Tree, int, int);
Tree CBT(Tree, int, int);
int center(int, int);

int main(){
    int Num;
    cin >> Num;
    int data;
    Tree tree = new tree_node[Num];
    for (int i = 0; i<Num;i++){
        cin >> data;
        tree[i].data = data;
        tree[i].left = NULL;
        tree[i].right = NULL;
    }
    Quicksort(tree, 0, Num - 1);
    Tree root = CBT(tree, 0, Num - 1);
    queue<Tree> q;
    q.push(root);
    Tree temp;
    while(!q.empty()){
        temp = q.front();
        q.pop();
        if(temp->left != NULL){
            q.push(temp->left);
        }
        if(temp->right != NULL){
            q.push(temp->right);
        }
        cout << temp->data;
        if(!q.empty())
            cout << ' ';
    }
    return 0;
}

int center(int left, int right){
    int num = right - left + 1;
    int k = (int)log2(num + 1);
    int remain = num - pow(2, k) + 1;
    if(remain > pow(2, k)/2)
        remain = pow(2, k) / 2;
    return (pow(2, k) - 1) / 2 + remain + left;
}

Tree CBT(Tree tree, int left, int right){
    Tree root = NULL;
    if(left <= right){
        int pivot = center(left, right);
        root = &tree[pivot];
        root->left = CBT(tree, left, pivot - 1);
        root->right = CBT(tree, pivot + 1, right);
    }
    return root;
}

int Paritition(Tree tree, int left, int right){
    int pivot = tree[left].data;
    while(left < right){
        while(left < right && tree[right].data >= pivot){
            --right;
        }
        tree[left].data = tree[right].data;
        while(left < right && tree[left].data <= pivot){
            ++left;
        }
        tree[right].data = tree[left].data;
    }
    tree[left].data = pivot;
    return left;
}

void Quicksort(Tree tree, int left, int right){
    if(left < right){
        int pivot = Paritition(tree, left, right);
        Quicksort(tree, left, pivot - 1);
        Quicksort(tree, pivot + 1, right);
    }
    return;
}