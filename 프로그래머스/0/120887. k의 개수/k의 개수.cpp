#include <string>
#include <vector>

using namespace std;

int solution(int i, int j, int k) {
    int answer = 0;
    for(;i<=j;i++){
        string change=to_string(i);        
        for(char val: change)
            if(val==k+'0')answer++;
    }
    return answer;
}