#include<iostream>

using namespace std;
int Find(int, const int *);
void Union(int, int, int *);
int con_num(int *, int);

int main(){
    int Num;
    cin >> Num;
    int *data = new int[Num + 1]();
    for(int i = 1;i <= Num;i++)  data[i] = -1;
    char flag;
    int x, y;
    while(1){
        cin >> flag;
        if(flag == 'S') break;
        cin >> x >> y;
        if(flag == 'C'){
            int root1 = Find(x, data);
            int root2 = Find(y, data);
            if(root1 == root2){
                cout << "yes" << endl;
            }
            else{
                cout << "no" << endl;
            }
        }
        else if(flag == 'I'){
            Union(x, y, data);
        }
    }
    int num = con_num(data, Num);
    if(num == 1)
        cout << "The network is connected.";
    else
        cout << "There are " << num << " components.";
    return 0;
}

int Find(int child, const int *data){
    while(data[child] > 0)
        child = data[child];
    return child;
}

void Union(int x, int y, int * data){
    int root1 = Find(x, data);
    int root2 = Find(y, data);
    if(root1 == root2) return;
    if(data[root1] > data[root2]){
        data[root2] += data[root1];
        data[root1] = root2;
    }
    else{
        data[root1] += data[root2];
        data[root2] = root1;
    }
}

int con_num(int *data, int Num){
    int *root = new int[Num]();
    int con_num = 0;
    for(int i = 1;i <= Num;i++){
        int root_temp = Find(i, data);
        int j;
        for(j = 0;j < con_num;j++){
            if(root[j] == root_temp) break;
        }
        if(j == con_num) con_num++;
        root[j] = root_temp;
    }
    return con_num;
}