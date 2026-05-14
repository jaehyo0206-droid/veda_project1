#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
int solution(int n) {
    int i=6; //피자 조각 수
    int cnt=0;
    while(1){ //딱 떨어지는 피자 조각을 찾는다
        cnt++;
        if(i%n==0){return cnt;} //딱 떨어짐
         i=i+6; //피자 조각 수
    }
}