#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
// array_len은 배열 array의 길이입니다.
int solution(int array[], size_t array_len) {
    int arr[1000];
    for(int i=0;i<1000;i++)arr[i]=0;
    for(int i=0;i<array_len;i++){
        int idx=array[i];
        arr[idx]++;
    }
    int max_value_cnt=0;
    int max_value_inx=NULL;
    for(int i=0;i<1000;i++){if(max_value_cnt<arr[i]){max_value_cnt=arr[i];max_value_inx=i;}}
    for(int i=0;i<1000;i++){if(max_value_inx==i)continue;if(max_value_cnt==arr[i])return -1;}
    int answer = max_value_inx;
    return answer;
}