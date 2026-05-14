#include <string>
#include <vector>
using namespace std;
int solution(vector<int> numbers, int k) {
    int ball=0;
    int result=0;
    for(int i=0;i<k-1;i++){ //k-1번 던져서 직전에 던진 사람 찾기
        if(ball>(numbers.size()-1))ball=0;
        else if(ball==(numbers.size()-1)){ball=1;continue; }; //마지막 인덱스
        ball+=2; //다음 사람을 건너뛴다
    }
    return numbers[ball];
}