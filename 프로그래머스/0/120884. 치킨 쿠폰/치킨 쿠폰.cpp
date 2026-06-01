#include <string>
#include <vector>
using namespace std;
int solution(int chicken) {
    int answer = 0;
    int coupon = chicken;
    while (coupon >= 10) {
        int free = coupon / 10;
        answer += free;
        coupon = free + (coupon % 10); //free치킨도 쿠폰을 준다
    }

    return answer;
}