#include<iostream>

using namespace std;
typedef int_fast64_t Vertex;

void print_list(Vertex *, int);

void Bubble_sort(Vertex *, int); // 冒泡排序


int main(){
    int N;
    cin >> N;
    Vertex *list = new Vertex[N];
    for(int i = 0;i<N;i++){
        cin >> list[i];
    }
    Bubble_sort(list, N);
    print_list(list, N);
    return 0;
}


void print_list(Vertex *list, int N){
    for(int i=0;i<N;i++){
        if(i) cout << ' ';
        cout << list[i];
    }
}

void Bubble_sort(Vertex *list, int N){
    for(int i=N;i>0;i--){
        bool flag = false;
        for(int j=0;j<i-1;j++){
            if(list[j] > list[j+1]){
                flag = true;
                Vertex temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
        if(flag == false) break;
    }
}
