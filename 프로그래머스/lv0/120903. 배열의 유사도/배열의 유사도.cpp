#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<string> s1, vector<string> s2) {
    int answer = 0;
    for(int i=0; i<s1.size();i++){
        //s2.end() 배열의 마지막 인덱스의 다음 칸을 가리키는 iterator
        //s2.end()와 값이 똑같다는 건 배열에서 일치하는 값을 못 찾았다는 것
        if(find(s2.begin(),s2.end(),s1[i])!=s2.end())answer++;
    }
    return answer;
}