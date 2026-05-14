#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int n) {
    int answer=0;
    if(n<=7)return 1;
    if(n%7!=0)answer=(n/7)+1;
    else answer=n/7;
    return answer;
}