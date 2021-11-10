#include<iostream>
#include<queue>
using namespace std;

typedef struct Node{
    int data;
    int left;
    int right;
}node;
typedef node *tree_node;

int Num;
int no = '-' - '0';

int main(){
    cin >> Num;
    tree_node tree = new node[Num];
    int root;
    for(int i= 0; i<Num; i++){
        tree[i].data = i;
        char left,right;
        cin >> left >> right;
        tree[i].left = left - '0';
        tree[i].right = right - '0';
        root += i;
        if(tree[i].left != no)
            root -= tree[i].left;
        if(tree[i].right != no)
            root -= tree[i].right;
    }
    queue<node> Tree;
    Tree.push(tree[root]);
    node temp;
    while(!Tree.empty()){
        temp = Tree.front();
        Tree.pop();
        if(temp.left != no){
            Tree.push(tree[temp.left]);
        }
        if(temp.right != no){
            Tree.push(tree[temp.right]);
        }
        if(temp.right == no && temp.left == no){
            cout << temp.data;
            if(!Tree.empty())
                cout << ' ';
        }
    }
    return 0;
}