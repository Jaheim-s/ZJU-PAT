#include <iostream>
using namespace std;
#define MaxVertex 102
#define INF 100000

int G[MaxVertex][MaxVertex]; 
int dict[MaxVertex][MaxVertex];
int path[MaxVertex][MaxVertex];
int N, M;

void build();
void Floyd();
void findmax();

int main(){
    build();
    Floyd();
    findmax();
    return 0;
}

void build(){
    cin >> N >> M;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++){
            G[i][j] = INF;
            if(i==j) G[i][j] = 0;
        }
    }
    for(int i=0;i<M;i++){
        int x,y, edge;
        cin >> x >> y >> edge;
        G[x][y] = G[y][x] = edge;
    }
}

void Floyd(){
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++){
            dict[i][j] = G[i][j];
            path[i][j] = -1;
        }
    for(int k=1;k<=N;k++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=N;j++)
                if((dict[i][k] + dict[k][j]) < dict[i][j]){
                    dict[i][j] = dict[i][k] + dict[k][j];
                    path[i][j] = k;
                }
}

void findmax(){
    int *max_list = new int[N+1];
    int i,j,max=0;
    for(i=1;i<=N;i++){
        max = 0;
        for(j=1;j<=N;j++){
            if(j==i) continue;
            if(dict[i][j] == INF){
                max = 0;
                break;
            }
            else if(dict[i][j] > max) max = dict[i][j];
        }
        max_list[i] = max;
    }
    int min_in_max_list = INF;
    int i_min = 0;
    for(i=1;i<=N;i++){
        if(max_list[i]==0) continue;
        if(max_list[i]<min_in_max_list) {
            min_in_max_list=max_list[i];
            i_min = i;
        }
    }
    if(i_min==0){
        cout << 0;
    }
    else{
        cout << i_min << ' ' << min_in_max_list;
    }
}