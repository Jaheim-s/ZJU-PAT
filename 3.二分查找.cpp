#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(){ /* 裁判实现，细节不表。元素从下标1开始存储 */
    int Num;
    scanf("%d", &Num);
    List list = (List)malloc(sizeof(struct LNode));
    Position idx;
    for(idx = 1; idx< Num; ++idx){
        scanf("%d", &list->Data[idx]);
    }
    list->Last = idx;
    return list;
}

Position BinarySearch( List L, ElementType X ){
    Position left = 1;
    Position right =  L->Last ;
    Position center;
    while(left <= right){
        center = (Position)((left + right) / 2);
        if(L->Data[center] > X){
            right = center - 1;
        }
        else if (L->Data[center] < X){
            left = center + 1;
        }
        else
            return center;
    }
    return NotFound;
}

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}
