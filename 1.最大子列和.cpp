#include<iostream>
using namespace std;

//算法2
/*
int findmax(int N, int *List)
{
    int temp = 0;
    int max = 0;
    int i , j ;
    for(i = 0; i < N; ++i){
        temp = 0;
        for(j = i;j < N;++j){
                temp += List[j];
                if(temp > max){
                    max = temp;
                }
        }
    }
    return max;
}


//算法3
int findmax(int left, int right, int *List){
    if (left == right) {
        if(0 > List[left])
            return 0;
        return List[left];
    }
    int max = 0;
    int max_L = 0;
    int max_R = 0;
    int temp = int((left + right)/2);
    max_L = findmax(left, temp, List);
    max_R = findmax(temp+1, right, List);
    int max_mid_1 = 0;
    int max_mid_temp = 0;
    for(int i = temp; i>=left ; i--){
        max_mid_temp += List[i];
        if(max_mid_temp > max_mid_1){
            max_mid_1 = max_mid_temp;
        }
    }
    max_mid_temp = 0;
    int max_mid_2 = 0;
    for(int i = temp+1; i <= right ;++i){
        max_mid_temp += List[i];
        if(max_mid_temp > max_mid_2){
            max_mid_2 = max_mid_temp;
        }
    }
    max_mid_temp = max_mid_1 + max_mid_2; //中间的最大子序列
    max = (max_L > max_mid_temp)?max_L:max_mid_temp;
    max = (max > max_R)?max:max_R;
    return max;
}
*/

//算法4
int findmax(int N, int *List){
    int max = 0;
    int temp = 0;
    for(int i = 0; i<N; ++i){
        temp += List[i];
        if (temp < 0)
            temp = 0;
        else{
            if (temp > max)
                max = temp;
        }
    }
    return max;
}

int main(){
    int N;
    cin >> N;
    int *List = new int[N];
    for(int i = 0; i<N; ++i){
        cin >> List[i];
    }

    int max = findmax(N, List);
    cout << max;
    delete[] List;
    return 0;
}