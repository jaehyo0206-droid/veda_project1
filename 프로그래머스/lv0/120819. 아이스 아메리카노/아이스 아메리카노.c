#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define one_ice 5500
int* solution(int money) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int* answer = (int*)malloc(sizeof(int)*2);
    if((money/one_ice)==0){answer[0]=0;answer[1]=money;return answer;}
    answer[0]=(money/one_ice);
    answer[1]=(money%one_ice);
    return answer;
}