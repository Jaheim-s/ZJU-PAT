#include<iostream>
#include<math.h>
using namespace std;
typedef int Vertex;
typedef struct node *Grape_node;
struct node{
    int x;
    int y;
    bool visit;
    bool land;
};

int distance(int x,int y,int i, int j);
Vertex addr(Vertex i, Vertex j);
bool get_land(Vertex *Grape, Grape_node croco);
bool DFS(Vertex *Grape, Grape_node croco, Vertex t);
int N,D;
int main(){
    cin >> N >> D;
    N = N + 1;
    Grape_node croco = new struct node[N];
    Vertex *Grape = new Vertex[N*(N+1) / 2];
    croco[0].x = croco[0].y = 0;
    croco[0].visit = croco[0].land = false;
    for(int i = 1;i < N;i++){
        cin >> croco[i].x; cin >> croco[i].y;
        croco[i].visit = croco[i].land = false;
        if((50 - abs(croco[i].x)) <= D || (50 - abs(croco[i].y) <= D)) croco[i].land = true;
    }
    for(int i = 0;i < N;i++){
        for(int j = 0;j <= i;j++){
            int dis = distance(croco[i].x, croco[i].y, croco[j].x, croco[j].y);
            Grape[addr(i, j)] = 0;
            if(j==0){
                if(dis <= D + 15 && dis > 0) Grape[addr(i, j)] = 1; //计算第一跳
            }
            else
                if(dis <= D && dis > 0) Grape[addr(i, j)] = 1;

        }
    }
    if(get_land(Grape, croco)){
        cout << "Yes";
    }
    else{
        cout << "No";
    }
    return 0; 
}

bool get_land(Vertex *Grape, Grape_node croco){
    return DFS(Grape, croco, 0);
}

bool DFS(Vertex *Grape, Grape_node croco, Vertex t){
    croco[t].visit = true;
    if(croco[t].land) return true;
    bool result = false;
    for(int i = 1;i < N;i++){
        if(croco[i].visit) continue;
        if(Grape[addr(t, i)] == 0) continue;
        result = DFS(Grape, croco, i);
        if(result) break;
    }
    return result;
}

Vertex addr(Vertex i, Vertex j){
    Vertex temp = j;
    if(i < j) {
        j = i;
        i = temp;
    }
    temp = i*(i+1) / 2 + j;
    return temp;
}

int distance(int x,int y,int i, int j){
    int temp = pow(j-y, 2) + pow(i-x, 2);
    return  ceil(sqrt(temp));
}