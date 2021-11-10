#include<iostream>
#include<vector>
using namespace std;
#define maxsize 1005
#define INF 10000

int G[maxsize][maxsize];
int dist[maxsize];
int parent[maxsize];
int N, M;
int sum_w;
vector<int> MST;

void build();
void Prime(int);
void InitMST(int);
int findmin();

int main(){
    cin >> N >> M;
    build();
    Prime(1);
    return 0;
}

void build(){
    sum_w = 0;
    for(int i=1;i<=N;i++){
        dist[i] = INF;
        parent[i] = -1; // 初始化路径的并查集
        for(int j=1;j<=N;j++)
            G[i][j] = INF;
    }
    int c1,c2,w;
    for(int i=1;i<=M;i++){
        cin >> c1 >> c2 >> w;
        G[c1][c2] = G[c2][c1] = w;
    }
}

void InitMST(int c){
    dist[c] = 0;
    MST.push_back(c);
    for(int i=1;i<=N;i++){
        if(i!=c){
            dist[i] = G[c][i];
        }
    }
}

int findmin(){
    int min_dist = INF, min_i = -1;
    for(int i=1;i<=N;i++)
        if(dist[i] && dist[i] < min_dist){
            min_dist = dist[i];
            min_i = i;
        }
    return min_i;
}

void Prime(int c){
    InitMST(c);
    while(1){
        int temp_c = findmin();
        if(temp_c == -1) break;
        sum_w += dist[temp_c];
        dist[temp_c] = 0;
        MST.push_back(temp_c);
        for(int i=1;i<=N;i++){
            if(dist[i] && G[temp_c][i] < dist[i]){
                dist[i] = G[temp_c][i];
                parent[i] = temp_c;
            }
        }
    }
    if(MST.size() < N){
        cout << -1;
    }
    else{
        cout << sum_w;
    }
}