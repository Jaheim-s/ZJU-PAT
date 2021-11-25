#include<iostream>

using namespace std;
typedef int ElementType;

void print_list(ElementType *, int);

void Bubble_sort(ElementType *, int); // 冒泡排序
void Insertion_Sort(ElementType *, int); // 直接插入排序
void shell_sort(ElementType *, int); //原始希尔排序
void Heap_sort(ElementType *, int); //堆排序
void PrecDown(ElementType *list, int i, int Num);
void Merge_sort(ElementType *list, int N);
void Merge_pass(ElementType *list, ElementType *list_temp, int length, int N);
void quick_sort(ElementType *list, int Num);
void quicksort(ElementType *list, int left, int right);
int get_pivot(ElementType *list, int left, int right);
void swap(ElementType &x, ElementType &y);

int main(){
    int N;
    cin >> N;
    ElementType *list = new ElementType[N+1];
    for(int i = 0;i<N;i++){
        cin >> list[i];
    }
    quick_sort(list, N);
    print_list(list, N);
    return 0;
}


void print_list(ElementType *list, int N){
    for(int i=0;i<N;i++){
        if(i) cout << ' ';
        cout << list[i];
    }
}

// 快速排序开始
void quick_sort(ElementType *list, int Num){
    quicksort(list, 0, Num - 1);
}

void quicksort(ElementType *list, int left, int right){
    if(left >= right)
        return;
    int pivot = get_pivot(list, left, right);
    int i = left, j = right - 1;
    while(i < j){
        while(list[++i] < pivot){}
        while(list[--j] > pivot){}
        if(i < j)
            swap(list[i], list[j]);
    }
    swap(list[i], list[right - 1]);
    quicksort(list, left, i - 1);
    quicksort(list, i + 1, right);
}

int get_pivot(ElementType *list, int left, int right){
    int center = (left + right) / 2;
    if(list[center] < list[left])
        swap(list[center], list[left]);
    if(list[right] < list[left])
        swap(list[right], list[left]);
    if(list[right] < list[center])
        swap(list[right], list[center]);
    swap(list[right - 1], list[center]);
    return list[right - 1];
}

void swap(ElementType &x, ElementType &y){
    if(x == y)
        return;
    ElementType temp = x;
    x = y;
    y = temp;
}
// 快速排序结束

void Bubble_sort(ElementType *list, int N){
    for(int i=N;i>0;i--){
        bool flag = false;
        for(int j=0;j<i-1;j++){
            if(list[j] > list[j+1]){
                flag = true;
                ElementType temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
        if(flag == false) break;
    }
}

void Insertion_Sort(ElementType *list, int N){
    for (int i = 1; i < N;i++){
        ElementType temp = list[i];
        int j = i;
        for (;temp < list[j - 1] && j > 0;j--)
            list[j] = list[j - 1];
        list[j] = temp;
    }
}

void shell_sort(ElementType *list, int N){
    for (int D = N / 2; D > 0; D /= 2){ //原始希尔增量序列
        for (int i = D; i < N; i++){ //插入排序
            ElementType temp = list[i];
            int j = i;
            for (; j >= D && temp < list[j - D] ;j -= D) // j>=D判断一定在后面判断的前面，确保list[j-D]有值
                list[j] = list[j - D];
            list[j] = temp;
        }
    }
}

// 最大堆 堆排序 开始
void PrecDown(ElementType *list, int i, int Num){
    ElementType temp = list[i];
    int parent = i;
    int child = 2 * parent + 1;
    for (; child < Num; child = 2 * parent + 1)
    {
        if(child < Num-1 && list[child] < list[child+1]) child++;
        if(list[child] > temp){
            list[parent] = list[child];
            parent = child;
        }
        else break;
    }
    list[parent] = temp;
}

void Heap_sort(ElementType *list, int N){//堆排序
    for (int i = N / 2; i >= 0;i--){ //调整建最大堆
        PrecDown(list, i, N);
    }
    for (int i = N - 1; i > 0;i--){
        ElementType temp = list[0];
        list[0] = list[i];
        list[i] = temp;
        PrecDown(list, 0, i);
    }
} 
//最大堆排序结束


//归并排序 递归 start
void Merge(ElementType *list, ElementType *list_temp, int left, int right, int right_end){
    int left_end = right - 1;
    int i_temp = left;
    int t, end, start = left;
    while(1){
        if(list[left] < list[right]) t = left++;
        else t = right++;
        list_temp[i_temp++] = list[t];
        if(t == left_end){
            t = right;
            end = right_end;
            break;
        }
        else if(t == right_end){
            t = left;
            end = left_end;
            break;
        }
    }
    for (; t<=end; t++)
        list_temp[i_temp++] = list[t];
    for (int i = start; i <= right_end;i++)
        list[i] = list_temp[i];
}

void Msort(ElementType *list, ElementType *list_temp, int start, int end){
    if(start < end){
        int center = (start + end) / 2;
        Msort(list, list_temp, start, center);
        Msort(list, list_temp, center + 1, end);
        Merge(list, list_temp, start, center + 1, end);
    }
}
/*
void Merge_sort(ElementType *list, int N){
    ElementType *list_temp = new ElementType[N + 1];
    Msort(list, list_temp, 0, N - 1);
    delete[] list_temp;
}*/
//归并排序 递归 end

//归并排序 非递归 start
void Merge_pass(ElementType *list, ElementType *list_temp, int length, int N){
    int left = 0;
    int right_end = left + 2 * length - 1;
    while (right_end < N){
        Merge(list, list_temp, left, left + length, right_end);
        left = right_end + 1;
        right_end = left + 2 * length - 1;
    }
    if(left + length < N){
        Merge(list, list_temp, left, left + length, N - 1);
    }
}

void Merge_sort(ElementType *list, int N){
    int length = 1;
    ElementType *list_temp = new ElementType[N + 1];
    while(length < N){
        Merge_pass(list, list_temp, length, N);
        length *= 2;
    }
    delete[] list_temp;
}
//归并排序 非递归 end