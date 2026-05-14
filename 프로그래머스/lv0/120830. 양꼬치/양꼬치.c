#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
# define one_yang_price 12000
# define one_drink_price 2000
int solution(int n, int k) {
    int answer = 0;
    answer=(one_yang_price)*n+(one_drink_price)*k;
    if(n/10>0)answer-=((n/10)*one_drink_price);

    return answer;
}