#include<iostream>

using namespace std;
typedef struct node *tree;
typedef struct node{
    int data;
    tree left;
    tree right;
}tree_node;

tree Inset(tree T, int X){
    if(!T){
        T = new tree_node;
        T->data = X;
        T->left = NULL;
        T->right = NULL;
    }
    else{
        if(X > T->data){
            T->right = Inset(T->right, X);
        }
        else if(X < T->data){
            T->left = Inset(T->left, X);
        }
    }
    return T;
}

bool is_tree(tree T1, tree T_temp){
    bool result;
    if(T1 && T_temp){
        if(T1->data != T_temp->data){
            return false;
        }
        cout << T1->data << T_temp->data<<endl;
        result = (is_tree(T1->left, T_temp->left) && is_tree(T1->right, T_temp->right));
    }
    else if((T1 == NULL) && (T_temp == NULL)){
        result = true;
    }
    else
        result = false;
    return result;
}

void  PreOrderTraversal(tree BST,string &s){
	if(BST){
		s += BST->data+'0';  // 将结点值保存进字符串 
		PreOrderTraversal(BST->left,s);  // 进入左子树 
		PreOrderTraversal(BST->right,s);  // 进入右子树 
	}
}

int main(){
    bool flag = false;
    string s;
    while(1){
        int Num;
        cin  >> Num;
        if(Num){
            int K;
            cin >> K;
            cout << Num << ' ' << K << endl;
            tree T1;
            for(int i = 0; i < Num;i++){
                int x;
                cin >> x;
                T1 = Inset(T1,x);
            } 
            //PreOrderTraversal(T1, s);
            //cout << s << endl;
            for(int j = 0;j < K;j++){
                tree T_temp;
                for(int i = 0; i<Num;i++){
                    int x;
                    cin >> x;
                    T_temp = Inset(T_temp,x);
                } 
                if(!flag)
                    flag = true;
                else
                    cout << endl;
                if(is_tree(T1,T_temp))
                    cout << "Yes";
                else
                    cout << "No";
            }
        }
        else
            break;
    }


    return 0;
}