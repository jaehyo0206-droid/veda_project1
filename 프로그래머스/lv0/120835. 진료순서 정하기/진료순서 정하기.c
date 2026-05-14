#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//using namespace std;
// emergency_len은 배열 emergency의 길이입니다.
int* solution(int emergency[], size_t emergency_len) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    int copy[10];
    for(int i=0;i<10;i++)copy[i]=-1;
    for(int i=0;i<emergency_len;i++){copy[i]=emergency[i];}
    for(int a=0;a<emergency_len-1;a++){
    for(int i=0;i<emergency_len-a-1;i++){
        if(copy[i]<copy[i+1]){
            int temp=copy[i];
            copy[i]=copy[i+1];
            copy[i+1]=temp;
            }//if문
        }//안쪽 for문
    }//바깥    
    int* answer = (int*)malloc(sizeof(int)*emergency_len);
    for(int i=0;i<emergency_len;i++){
        for(int j=0;j<emergency_len;j++){
            if(emergency[i]==copy[j]){
                answer[i]=j+1;
            }   
        }
    }
    return answer;
}