#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// 최대공약수 함수 추가
int gcd(int a, int b){
    while(b != 0){
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int* solution(int numer1, int denom1, int numer2, int denom2) {
    int result_up = 0;
    int result_down = 0;

    int* answer = (int*)malloc(sizeof(int) * 2);

    if(denom1 < denom2){
        if((denom2 % denom1) == 0){
            int same = denom2 / denom1;

            int left_up = numer1 * same;

            result_up = left_up + numer2;
            result_down = denom2;
        }
        else{
            result_up = numer1 * denom2 + numer2 * denom1;
            result_down = denom1 * denom2;
        }
    }
    else if(denom1 > denom2){
        if((denom1 % denom2) == 0){
            int same = denom1 / denom2;

            int right_up = numer2 * same;

            result_up = right_up + numer1;   // += → = 로 수정
            result_down = denom1;            // += → = 로 수정
        }
        else{
            result_up = numer1 * denom2 + numer2 * denom1;
            result_down = denom1 * denom2;
        }
    }
    else{ // denom1 == denom2
        result_up = numer1 + numer2;   // += → = 로 수정
        result_down = denom1;
    }

    // 🔥 기약분수 처리 (핵심 수정)
    int g = gcd(result_up, result_down);
    result_up /= g;
    result_down /= g;

    answer[0] = result_up;
    answer[1] = result_down;

    return answer;
}