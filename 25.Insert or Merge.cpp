#include<iostream>

using namespace std;
typedef int ElementType;

int main(){
    int N;
    cin >> N;
    ElementType *list = new ElementType[N+1];
    for(int i = 0;i<N;i++){
        cin >> list[i];
    }
    return 0;
}