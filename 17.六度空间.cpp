#include<iostream>
#include<queue>
using namespace std;
typedef int Vertex;
typedef struct node* human_node;
struct node{
    Vertex human_code;
    bool visit;
};
typedef struct grape_node* Grape;
struct grape_node{
    human_node data;
    Grape next;
};

int BFS(Grape grape, Vertex t);

int N,E;
int main(){
    cin >> N >> E;
    human_node humen = new struct node[N + 1];
    Grape grape = new struct grape_node[N + 1];
    for(int i = 1;i <= N;i++){
        humen[i].human_code = i;
        humen[i].visit = false;
        grape[i].data = &humen[i];
        grape[i].next = NULL;
    }
    Vertex t1, t2;
    Grape temp = NULL;
    for(int i = 1;i <= E;i++){
        cin >> t1 >> t2;
        temp = new struct grape_node;
        temp->data = &humen[t2];
        temp->next = grape[t1].next;
        grape[t1].next = temp;
        temp = NULL;
        temp = new struct grape_node;
        temp->data = &humen[t1];
        temp->next = grape[t2].next;
        grape[t2].next = temp;
        temp = NULL;
    }
    for(int i = 1;i <= N;i++){
        int num = BFS(grape, i);
        printf("%d: %.2f%\n", i, (float)num/N*100);
        for(int j = 1;j <= N;j++) humen[j].visit = false;
    }
    return 0;
}

int BFS(Grape grape, Vertex t){
    queue<human_node> q1, q2;
    int num = 1, depth = 0;
    human_node temp;
    Grape temp_g;
    q1.push(grape[t].data);
    grape[t].data->visit = true;
    while((!q1.empty()) || (!q2.empty())){
        if(depth >= 6) break;
        if(!q1.empty()){
            depth++;
            while(!q1.empty()){
                temp = q1.front();
                q1.pop();
                temp_g = &grape[temp->human_code];
                while(temp_g->next){
                    temp_g = temp_g->next;
                    if(temp_g->data->visit) continue;
                    q2.push(temp_g->data);
                    temp_g->data->visit = true;
                    num++;
                }
            }
        }
        else{
            depth++;
            while(!q2.empty()){
                temp = q2.front();
                q2.pop();
                temp_g = &grape[temp->human_code];
                while(temp_g->next){
                    temp_g = temp_g->next;
                    if(temp_g->data->visit) continue;
                    q1.push(temp_g->data);
                    temp_g->data->visit = true;
                    num++;
                }
            }
        }
    }
    return num;
}