#include<iostream>
using namespace std;
#define maxsize 505
#define INF 10000

struct edge
{
   int length;
   int cost;
};
struct edge init_edge = {INF, INF};

int N,M,S,D;
struct edge G[maxsize][maxsize];
struct edge dict[maxsize];
bool collected[maxsize];

void build();
void Dijkstra();
int findmin();

int main(){
    cin>>N>>M>>S>>D;
    build();
    Dijkstra();
    return 0;
}

void build(){
    for(int i=0;i<N;i++){
        collected[i] = false;
        for(int j=0;j<N;j++){
            G[i][j] = init_edge;
            if(i==j) G[i][j].length = G[i][j].cost = 0;
        }
    }
    int t1,t2,w,c;
    for(int i=0;i<M;i++){
        cin >>t1>>t2>>w>>c;
        G[t1][t2].length = G[t2][t1].length = w;
        G[t1][t2].cost = G[t2][t1].cost = c;
    }
}

int findmin(){
    int min_i = N, min_length = INF;
    for(int i=0;i<N;i++){
        if(!collected[i] && dict[i].length < min_length){
            min_length = dict[i].length;
            min_i = i;
        }
    }
    return min_i;
}

void Dijkstra(){
    collected[S] = true;
    for(int i=0;i<N;i++)
        dict[i] = G[S][i];
    int temp_city;
    while(1){
        temp_city = findmin();
        if(temp_city == N) break;
        collected[temp_city] = true;
        if(temp_city == D) break;
        for(int i=0;i<N;i++){
            if(i != temp_city && G[temp_city][i].length != INF && !collected[i]){
                if(dict[i].length > G[temp_city][i].length + dict[temp_city].length){
                    dict[i].length = G[temp_city][i].length + dict[temp_city].length;
                    dict[i].cost = G[temp_city][i].cost + dict[temp_city].cost;
                }
                else if(dict[i].length == G[temp_city][i].length + dict[temp_city].length){
                    if(dict[i].cost > G[temp_city][i].cost + dict[temp_city].cost){
                        dict[i].cost = G[temp_city][i].cost + dict[temp_city].cost;
                    }
                }
            }
        }
    }
    cout << dict[temp_city].length << ' ' << dict[temp_city].cost;
}