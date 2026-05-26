#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(string my_string) {
    int answer = 0;
    string nmake = "";

    for(char c : my_string){

        // 숫자인 경우
        if(c - '0' >= 0 && c - '0' <= 9){
            nmake += c;
        }

        // 숫자가 아닌 경우
        else if(!nmake.empty()){
            answer += stoi(nmake);
            nmake = "";
        }
    }

    // 마지막 숫자 처리
    if(!nmake.empty()){
        answer += stoi(nmake);
    }

    return answer;
}