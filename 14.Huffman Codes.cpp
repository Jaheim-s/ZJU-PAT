#include<iostream>
#include<string>
using namespace std;
#define MinData -1000
typedef struct huff_node* huff_tree;
typedef struct minHeap_node{
    huff_tree* data;
    int size;
    int cap;
}minHeap;

struct huff_node {
    int weight;
    huff_tree left;
    huff_tree right;
};

typedef struct data_node
{
    char cr;
    int freq;
}Data;

typedef struct stu_data
{
    char cr;
    string huff_code;
}Stu;


minHeap& creat_heap(int);
minHeap& heap_build(int);
void sort_heap(minHeap&);
void Insert_heap(minHeap&, huff_tree);
huff_tree Delete_heap(minHeap& heap, int addr = 1);
bool ISfull(minHeap&);
bool ISempty(minHeap&);
huff_tree creat_huffnode(int weight = 0);
huff_tree hufftree_build(minHeap&);
int huffcode_w(huff_tree, int k = 0);
void read_studata(Stu *, int);
bool IS_studata(Stu *, int, int);

Data* Data_node;

int main() {
    int Num;
    cin >> Num;
    Data_node = new Data[Num];;
    minHeap& heap = heap_build(Num);
    huff_tree root = hufftree_build(heap);
    int w_k = huffcode_w(root);
    int stu_num;
    cin >> stu_num;
    Stu *studata = new Stu[Num];
    for(int i = 0;i < stu_num; i++){
        read_studata(studata, Num);
        if(IS_studata(studata, Num, w_k))
            cout << "Yes";
        else
            cout << "No";
        if(i < stu_num - 1) cout << endl;
    }
    return 0;
}

bool IS_studata(Stu *studata, int Num, int w_k){
    int huffcode_len = 0;
    huff_tree Tree_stu = creat_huffnode();
    huff_tree temp = NULL;
    for(int i = 0; i < Num;i++){
        temp = Tree_stu;
        string tmp = studata[i].huff_code;
        int k = tmp.length();
        huffcode_len += Data_node[i].freq * k;
        for(int j = 0;j < k;j++){
            if(tmp.at(j) == '0'){
                if(!temp->left) temp->left = creat_huffnode();
                else{
                    if(temp->left->weight) return false;
                }
                temp = temp->left;
            }
            else{
                if(!temp->right) temp->right = creat_huffnode();
                else{
                    if(temp->right->weight) return false;
                }
                temp = temp->right;
            }
        }
        if(temp->left != NULL || temp->right != NULL) return false;
        temp->weight = Data_node[i].freq;
    }
    if(huffcode_len > w_k) return false;
    return true;
}

void read_studata(Stu *studata, int Num){
    for(int i = 0;i < Num; i++)
        cin >> studata[i].cr >> studata[i].huff_code;
}

int huffcode_w(huff_tree root, int k){
    int w_k = 0;
    if(root){
        if(root->left == NULL && root->right == NULL) w_k = root->weight * k;
        k++;
        w_k += huffcode_w(root->left, k);
        w_k += huffcode_w(root->right, k);
    }
    return w_k;
}

minHeap& heap_build(int Num) {
    minHeap& heap = creat_heap(Num);
    int weight;
    char cr;
    huff_tree temp;
    for (int i = 0; i < Num; i++) {
        cin >> cr >> weight;
        Data_node[i].cr = cr;
        Data_node[i].freq = weight;
        temp = creat_huffnode(weight);
        heap.data[++heap.size] = temp;
    }
    sort_heap(heap);
    return heap;
}

void sort_heap(minHeap& heap) {
    int parent = heap.size / 2;
    for (;parent > 0; parent--) {
        huff_tree temp = heap.data[parent];
        int parent_t = parent;
        int child;
        for (;parent_t * 2 <= heap.size;parent_t = child) {
            child = parent_t * 2;
            if (child != heap.size && heap.data[child]->weight > heap.data[child + 1]->weight) child++;
            if (temp->weight <= heap.data[child]->weight) break;
            heap.data[parent_t] = heap.data[child];
        }
        heap.data[parent_t] = temp;
    }
}

minHeap& creat_heap(int Num) {
    minHeap* temp = new minHeap;
    minHeap& heap = *temp;;
    heap.cap = Num + 1;
    heap.data = new huff_tree[heap.cap];
    heap.data[0] = creat_huffnode(MinData);
    heap.size = 0;
    return heap;
}

huff_tree hufftree_build(minHeap& heap) {
    huff_tree temp = NULL;
    while (heap.size > 1) {
        temp = creat_huffnode();
        temp->left = Delete_heap(heap);
        temp->right = Delete_heap(heap);
        temp->weight = temp->left->weight + temp->right->weight;
        Insert_heap(heap, temp);
    }
    temp = Delete_heap(heap);
    return temp;
}

huff_tree creat_huffnode(int weight) {
    huff_tree temp = new struct huff_node;
    temp->weight = weight;
    temp->left = temp->right = NULL;
    return temp;
}

void Insert_heap(minHeap& heap, huff_tree tree) {
    if (ISfull(heap)) return;
    int child = ++heap.size;
    for (;heap.data[child / 2]->weight > tree->weight;child /= 2) {
        heap.data[child] = heap.data[child / 2];
    }
    heap.data[child] = tree;
}

huff_tree Delete_heap(minHeap& heap, int addr) {
    if (ISempty(heap)) return NULL;
    huff_tree min = heap.data[addr];
    huff_tree temp = heap.data[heap.size--];
    int child;
    int parent;
    for (parent = addr; parent * 2 <= heap.size;parent = child) {
        child = parent * 2;
        if (child != heap.size && heap.data[child]->weight > heap.data[child + 1]->weight) child++;
        if (temp->weight < heap.data[child]->weight) break;
        heap.data[parent] = heap.data[child];
    }
    heap.data[parent] = temp;
    return min;
}

bool ISfull(minHeap& heap) {
    if (heap.size == heap.cap) return true;
    return false;
}

bool ISempty(minHeap& heap) {
    if (heap.size == 0) return true;
    return false;
}