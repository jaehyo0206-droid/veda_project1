#include <stdio.h>

int main(void) {
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){ //n 번 사이클
        for(int a=0;a<i+1;a++){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}