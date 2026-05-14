#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> solution(string my_string) {
    char c;
    vector<int> answer;
    for(char c:my_string){
        int num=c-'0';
        if(num>=0 && num<=9)
        answer.push_back(num);
    }
    sort(answer.begin(),answer.end());
    
    return answer;
}