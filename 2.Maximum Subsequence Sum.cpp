#include<iostream>
using namespace std;

void findmax(const int N, const int *List, int *max){
    int this_temp = 0;
    int temp_left = 0;
    max[2] = N-1;
    for(int i = 0; i < N; ++i){
        this_temp += List[i];
        if(0 > this_temp){
            this_temp = 0;
            temp_left = i + 1;
        }
        else if(this_temp > max[0]){
            max[0] = this_temp;
            max[1] = temp_left;
            max[2] = i;
        }
        else if(this_temp == 0){
            if(max[2] = N-1 & max[1] == 0){
                max[1] = temp_left;
                max[2] = i;
            }
        }
        

            /*
            else if(this_temp == max[0]){
                if(0 == max[2]){
                    max[1] = temp_left;
                    max[2] = i;
                }
                bool flag1 = temp_left >= max[1];
                bool flag2 = i >= max[2];
                max[1] = flag1?max[1]:temp_left;
                max[2] = (flag1&flag2)?max[2]:i;
            }*/
        

    }
    /*
    if(0 == max[1] & N == temp_left){
        max[1] = 0;
        max[2] = N - 1;
    }*/
    return;
}


int main(){
    int N;
    cin >> N;
    int *List = new int[N];
    int *max = new int[3](); //初始化为0
    for(int i = 0; i < N; ++i)
        cin >> List[i];
    findmax(N, List, max);
    cout << max[0] << ' ' << List[max[1]] << ' ' << List[max[2]];
    delete[] max;
    delete[] List;
    return 0;
}