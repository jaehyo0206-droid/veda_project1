#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int solution(int hp) {
    int answer = 0;
    int dp[6]={0,1,2,1,2,1};
    if(hp<=5)return dp[hp];
    answer=(hp/5)+dp[hp%5];
    return answer;
}