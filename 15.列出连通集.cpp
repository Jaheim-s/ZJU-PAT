#include<iostream>
#include<queue>
using namespace std;

typedef int Vertex;

void insert(Vertex *, int, int);
Vertex switch_Vertex(Vertex,Vertex);
void DFS(Vertex *, Vertex, int *);//深度优先搜索
void BFS(Vertex *, Vertex, int *);//广度优先搜索

int N, E;
int main(){
    cin >> N >> E;
    Vertex *Grape = new Vertex[N * (N + 1) / 2];
    int *visit = new int[N];
    for(int i = 0; i < N * (N + 1) / 2; i++){
        if(i < N) visit[i] = 0;
        Grape[i] = 0;
    }
    Vertex t1, t2;
    for(int i = 0; i < E;i++){
        cin >> t1 >> t2;
        insert(Grape, t1, t2);
    }
    for(int i = 0;i<N;i++){
        if(!visit[i]){
            cout << '{' << ' ';
            DFS(Grape, i, visit);
            cout << '}' << endl;
        }
    }
    for(int i = 0;i<N;i++) visit[i] = 0;
    for(int i = 0;i<N;i++){
        if(!visit[i]){
            cout << '{' << ' ';
            BFS(Grape, i, visit);
            cout << '}' << endl;
        }
    }
    
    return 0;
}

void BFS(Vertex *Grape, Vertex t, int *visit){
    if(visit[t]) return;
    queue<Vertex> q;
    q.push(t);
    while(!q.empty()){
        Vertex temp = q.front();
        q.pop();
        cout << temp << ' ';
        for(int j = temp;j<N;j++){
            if(Grape[switch_Vertex(temp, j)] && visit[j]==0){
                q.push(j);
                visit[j] = 1;
            }
        }
    }
    
}

void DFS(Vertex *Grape, Vertex t, int *visit){
    if(visit[t]) return;
    visit[t] = 1;
    cout << t <<' ';
    for(int j = t;j < N;j++){
        if(Grape[switch_Vertex(t, j)]){
            DFS(Grape, j, visit);
        }
    }
}

void insert(Vertex *Grape,Vertex t1,Vertex t2){
    Vertex addr = switch_Vertex(t1, t2);
    Grape[addr] = 1;
}

Vertex switch_Vertex(Vertex t1, Vertex t2){
    Vertex temp = t2;
    if(t1 > t2){
        t2 = t1;
        t1 = temp;
    }
    temp = (2*N-t1+1)*t1/2+t2-t1;
    return temp;
}