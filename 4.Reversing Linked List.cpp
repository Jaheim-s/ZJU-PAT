#include<iostream>
using namespace std;

#define maxsize 100002
typedef int address;


void printlist(const address head,const int *Data,const address *next){
    address temp;
    for(temp = head;next[temp] != -1;temp = next[temp]){
        printf("%05d %d %05d", temp, Data[temp], next[temp]);
        printf("\n");
    }
    printf("%05d %d %d", temp, Data[temp], next[temp]);
}

void printList(const int Num, const address *List, const int *Data, const address *next){
    address temp;
    for(int i = 0; i < Num - 1; ++i){
        temp = List[i];
        printf("%05d %d %05d", temp, Data[temp], List[i+1]);
        printf("\n");
    }
    temp = List[Num - 1];
    printf("%05d %d %d", temp, Data[temp], -1);
}

int main(){
    int Num, K;
    address head;
    int Data[maxsize];
    address next[maxsize];
    cin >> head >> Num >> K;
    int i;
    for(i = 0; i < Num; ++i){
        address temp;
        cin >> temp;
        cin >> Data[temp] >> next[temp];
    }
    address *List = new address[Num];
    address temp = head;
    for(i = 0;temp != -1; ++i){ //数组排列 方便反转,获取链表的有效节点
        List[i] = temp;
        temp = next[temp];
    }
    Num = i;
    for(int i = 0;i < Num / K;++i){
        int first = i * K;
        for(int j = 0;j < K / 2;++j){
            address t;
            address t1 = List[first + j];
            t = t1;
            List[first + j] = List[first + K - 1 - j];
            List[first + K - 1 - j] = t;
        }
    }
    printList(Num, List, Data, next);
}
