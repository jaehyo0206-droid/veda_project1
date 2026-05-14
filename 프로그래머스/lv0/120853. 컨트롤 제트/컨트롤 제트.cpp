//stringstream 초기화 시 문자 하나를 넣어줘야한다
//문자열,문자 "" '' 구분
//문자열을 숫자로 바꿀 때는 stoi 함수를 사용한다
#include <string>
#include <vector>
#include <sstream>
using namespace std;
int solution(string s) {
    int answer = 0;
    int before=0;
    string c;
    stringstream ss(s);
    while(ss >> c){
        if(c == "Z"){ answer-=before; continue;}
            answer += stoi(c);
            before = stoi(c);
    }    
    return answer;
}