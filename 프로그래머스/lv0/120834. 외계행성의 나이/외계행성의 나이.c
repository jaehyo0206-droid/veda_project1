#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
char* solution(int age) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(4);
    for(int i=0;i<4;i++)answer[i]=NULL;
    char alpha[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int re_number[4]={0,0,0,0};
    int i=0;
    int num_size=10; //자리수로 활용
    //1000이라면
    //if(age==1000)
    //{answer[0]='b';answer[1]='a';answer[2]='a';answer[3]='a';return answer;}    
    //최대 3자리(999)
    int cnt_size=0;
    while(1){
    cnt_size++;//마지막에'\0'넣을 위치 크기 구할 때 사용
    int remainder=age%num_size;
    int quoter=age/num_size;
    if(quoter==0){re_number[i]=remainder;break;}//전부 끝났다면
    re_number[i++]=remainder;
    //크기 조정
    age=quoter;
    }//while 문
    int back_idx=cnt_size-1;
    for(int i=0;i<cnt_size;i++){
        answer[i]=alpha[re_number[back_idx--]];
    }
    //answer[cnt_size]='\0';
    return answer;
}