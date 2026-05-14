#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define cut 100000
int solution(int price) {
    if(price<cut) return (int)price; //10~10만 미만
    //10만 이상 30만 미만
    else if(price >=cut && price < (3*cut)){return(price-(price*0.05));} 
    //30만 이상 50만 미만
    else if(price >= (3*cut) && price < (5*cut) ){return (price-(price*0.1));}
    //50만 이상
    else if(price>=(5*cut)){return (price-(price*0.2));}
}