#include <string>
#include <vector>
#include <deque>    
//A,B를 dqueu화 시키기
//A의 맨 끝 원소를 맨 앞에 넣기
         //A의 원소 배치가 맨 처음과 같을 때까지 반복(while(a.size()))
//만일 A와B가 같아지면 return result
//while이 끝날떄 까지 return result가 없다면 return -1
using namespace std;

int solution(string A, string B) {
    int answer = 0;
    int cnt=A.length();
    deque <char> d_A;
    deque <char> d_B;
    for(char x : A)d_A.push_back(x);
    for(char x : B)d_B.push_back(x);
    if(d_A==d_B) return answer;  
    while(cnt--){
        answer++;
        int back=d_A.size()-1;
        char x = d_A[back];
        d_A.pop_back();
        d_A.push_front(x);
        if(d_A==d_B) return answer;
    }
    return -1;
}