#include<iostream>
using namespace std;

typedef struct{
    int *data;
    int Top;
    int MaxSize;
}snode;
typedef snode *Stack;

int stack_len, list_len, sequence_num;

bool IsFull(const Stack S)
{
    return (S->Top == S->MaxSize-1);
}

bool IsEmpty(const Stack S)
{
    return (S->Top == -1);
}

Stack init_stack(const int stack_len){
    Stack S = new snode;
    S->data = new int[stack_len];
    S->MaxSize = stack_len;
    S->Top = -1;
    return S;
}

int pop(Stack S){
    if(IsEmpty(S)){
        return 0;
    }
    int temp = S->data[S->Top];
    S->Top--;
    return temp;
}

bool push(Stack S, const int data){
    if(IsFull(S))
        return false;
    S->Top++;
    S->data[S->Top] = data;
    return true;
}

int is_stack(const int *sequence){
    Stack S = init_stack(stack_len);
    int data_top = list_len;
    for(int i = (list_len - 1);i >= 0;i--){
        if(IsEmpty(S))
            push(S, sequence[i]);
        else{
            if(S->data[S->Top] < sequence[i]){
                if(!push(S, sequence[i]))
                    return 0;
            }
            else{
                while((!IsEmpty(S)) && (S->data[S->Top] > sequence[i])){
                    int temp = pop(S);
                    if(temp != data_top)
                        return 0;
                    data_top -= 1;
                }
                push(S, sequence[i]);
            }
        }
    }
    while(!IsEmpty(S)){
        int temp = pop(S);
        if(temp != data_top)
            return 0;
        data_top -= 1;
    }
    return 1;
}

int main(){
    cin >> stack_len >> list_len >> sequence_num;
    int *result = new int[sequence_num];
    for(int i = 0; i < sequence_num; i++){
        int *sequence = new int[list_len];
        for(int j = 0;j < list_len;j++){
            cin >> sequence[j];
        }
        result[i] = is_stack(sequence);
        if(result[i])
            cout << "YES";
        else
            cout << "NO";
        if(i != (sequence_num - 1))
            cout << endl;
        delete[] sequence;
    }
    return 0;
}
