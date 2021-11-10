#include<iostream>

using namespace std;

typedef struct{
    char data;
    int left;
    int right;
}tree_node;
typedef tree_node *node;
int null = '-' - '0';


int read(const int Num, node tree){
    int root = 0;
    for(int i = 0;i < Num;i++){
        cin >> tree[i].data;
        char left,right;
        cin >> left >> right;
        tree[i].left = left - '0';
        tree[i].right = right - '0';
        root += i;
        if(tree[i].left != null)
            root -= tree[i].left;
        if(tree[i].right != null)
            root -= tree[i].right;
    }
    return root;
}

bool is_tong(const node tree1, const int n1, const node tree2, const int n2){
    if(n1 == null || n2 == null){
        if(n1 == n2)
            return true;
        else
            return false;
    }
    if(tree1[n1].data != tree2[n2].data)
        return false;
    bool s1 = (is_tong(tree1, tree1[n1].left, tree2, tree2[n2].left) && is_tong(tree1, tree1[n1].right, tree2, tree2[n2].right));
    bool s2 = (is_tong(tree1, tree1[n1].left, tree2, tree2[n2].right) && is_tong(tree1, tree1[n1].right, tree2, tree2[n2].left));
    return (s1 || s2);
}

int main(){
    int Num1,Num2;
    cin >> Num1;
    node tree1 = new tree_node[Num1];
    int root1 = read(Num1, tree1);
    cin >> Num2;
    node tree2 = new tree_node[Num2];
    int root2 = read(Num2, tree2);
    if(Num1 == 0 && Num2 ==0)
        cout << "Yes";
    else{
        if(is_tong(tree1, root1, tree2, root2))
            cout << "Yes";
        else
            cout << "No";
    }

    return 0;
}