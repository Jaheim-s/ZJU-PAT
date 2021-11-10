#include<iostream>
#include<vector>
#include<queue>
using namespace std;
#define maxsize 1005
#define INF 10000

struct Node{
	int c1;
	int c2;
	int weight; // 权重 
	// 重载运算符成最大堆 
	bool operator < (const Node &a) const
	{
		return weight>a.weight;
	}
};

int G[maxsize][maxsize];
int parent[maxsize];
vector<Node> MST;
priority_queue<Node> q;
int N, M, sum_w;

void build();
void Kruskal();
bool is_round(struct Node &);
int find_parent(int);
void Union(int, int);

int main(){
    cin >> N >> M;
    build();
    Kruskal();
    return 0;
}

void build(){
    for(int i=1;i<=N;i++){
        parent[i] = -1;
        for(int j=1;j<=N;j++){
            G[i][j] = INF;
        }
    }
    int c1, c2, weight;
    for(int i=1;i<=M;i++){
        cin >> c1 >> c2 >> weight;
        G[c1][c2] = G[c2][c1] = weight;
        struct Node node_temp;
        node_temp.c1 = c1;
        node_temp.c2 = c2;
        node_temp.weight = weight;
        q.push(node_temp);
    }
}

int find_parent(int c){ //路径压缩查找
    if(parent[c] < 0) return c;
    return parent[c] = find_parent(parent[c]);
}

void Union(int root1, int root2){ //按规模归并
    if(parent[root1] < parent[root2]){
        parent[root1] += parent[root2];
        parent[root2] = root1;
    }
    else{
        parent[root2] += parent[root1];
        parent[root1] = root2;
    }
}

bool is_round(struct Node &node_min){
    int c1_parent = find_parent(node_min.c1);
    int c2_parent = find_parent(node_min.c2);
    if(c1_parent == c2_parent) return true;
    Union(c1_parent, c2_parent);
    return false;
}

void Kruskal(){
    sum_w = 0;
    while(MST.size() < N-1 && q.size()){
        struct Node node_min = q.top();
        q.pop();
        if(!is_round(node_min)){
            MST.push_back(node_min);
            sum_w += node_min.weight;
        }
    }
    if(MST.size() < N-1){
        cout << -1;
    }
    else{
        cout << sum_w;
    }
}