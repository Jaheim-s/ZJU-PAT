#include<iostream>
#include<stack>
using namespace std;

typedef struct node *tree;
typedef struct node{
    int data;
    tree left;
    tree right;
}tree_node;

tree creat(){
    tree temp = new tree_node;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

tree get_tree(const int Num){
    tree root;
    root = creat();
    tree node_temp;
    stack<tree> s;
    string op;
    int data;
    cin >> op >> data;
    root->data = data;
    node_temp = root;
    s.push(root);
    for(int i = 1;i<Num*2;i++){
        cin >> op;
        if(op == "Push"){
            cin >> data;
            tree temp = creat();
            temp->data = data;
            if(!node_temp->left)
                node_temp->left = temp;
            else if(!node_temp->right)
                node_temp->right = temp;
            node_temp = temp;
            s.push(temp);
        }
        else{ //pop
            node_temp = s.top();
            s.pop();
        }
    }
    return root;
}

void read(const tree T, bool &flag){
    tree temp = T;
    if(temp){
        read(temp->left, flag);
        read(temp->right, flag);
        if(!flag){
            flag = true;
        }
        else
            cout << " ";
        cout << temp->data;
    }
}

int main(){
    stack<int> s;
    int Num;
    cin >> Num;
    tree T = get_tree(Num);
    bool flag = false;
    read(T, flag);
    return 0;
}