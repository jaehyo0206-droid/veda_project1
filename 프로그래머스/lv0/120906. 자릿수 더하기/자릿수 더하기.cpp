#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 0;
    string ntos=to_string(n);
    for(char c : ntos)answer+=(c-'0');
    
    return answer;
}