#include <string>
#include <vector>

using namespace std;

string solution(string my_string) {
    string answer = "";
    for(char c : my_string){
        if(c >='a' && c<='z')answer += (c-'a');
        else answer +=(c+'a');
    }
    return answer;
}