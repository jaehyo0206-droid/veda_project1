#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int solution(int slice, int n){
    int pizza_cnt=1;
    int slice_cnt=slice;
    while(1){
        //if에서작음,큼,작거나 같음, 크거나 같음 전부 고려하기
        if(slice_cnt>=n)return pizza_cnt; 
        slice_cnt+=slice; //이거 배수가 아니라 제곱 수 느낌으로 커진다        
        pizza_cnt++;
    }
}