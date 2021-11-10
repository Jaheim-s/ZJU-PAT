#include<iostream>

using namespace std;
typedef int ElementType;

typedef struct HeapStruct{
    ElementType *data;
    int size;
    int Capacity;
}Heap;

Heap creatheap(int);
void sortHeap(Heap&);
void insert(Heap&, ElementType);
bool IS_full(Heap&);
bool IS_empty(Heap&);
void heap_print(Heap&, int);

int main(){
    int N, M;
    cin >> N >> M;
    Heap minHeap = creatheap(N);
    ElementType data;
    for(int i = 1;i <= N;i++){
        cin >> data;
        insert(minHeap, data);
    }
    for(int i = 0;i < M;i++){
        int j;
        cin >> j;
        heap_print(minHeap, j);
        if(i < M -1) cout << endl;
    }

    return 0;

}

void heap_print(Heap& minHeap, int j){
    if(j > minHeap.size) return;
    for(int parent = j ;parent > 0;parent = parent / 2){
        cout << minHeap.data[parent];
        if(parent > 1) cout << ' ';
    }
}

void insert(Heap& minHeap, ElementType data){
    if(IS_full(minHeap)) return;
    if(IS_empty(minHeap)){
        minHeap.data[++minHeap.size] = data;
        minHeap.data[0] = data;
        return;
    }
    minHeap.data[++minHeap.size] = data;
    int  child = minHeap.size;
    int parent;
    for(parent = child / 2;parent > 0;parent = parent / 2){
        if(minHeap.data[parent] > data){
            minHeap.data[child] = minHeap.data[parent];
            minHeap.data[parent] = data;
            child = parent;
        }
        else break;
    }
}

bool IS_full(Heap& heap){
    if(heap.size == heap.Capacity) return true;
    else return false;
}

bool IS_empty(Heap& heap){
    if(heap.size == 0) return true;
    else return false;
}

Heap creatheap(int MaxSize){
    Heap temp;
    temp.data = new ElementType[MaxSize + 1];
    temp.Capacity = MaxSize;
    temp.size = 0;
    return temp;
}



void sortHeap(Heap& minHeap){
    int last = minHeap.size;
    for(int parent =  last / 2;parent > 0;parent--){
        int child;
        for(int parent_t = parent;parent_t <= minHeap.size;parent_t = child){
            child = parent_t * 2;
            if(child != minHeap.size){
                if(minHeap.data[child] > minHeap.data[child + 1])
                    child++;
            }
            if(minHeap.data[parent_t] > minHeap.data[child]){
                ElementType temp = minHeap.data[parent_t];
                minHeap.data[parent_t] = minHeap.data[child];
                minHeap.data[child] = temp;
                parent_t = child;
            }
            else break;
        }
    }
    minHeap.data[0] = minHeap.data[1];
}