#include <string>
#include <vector>

using namespace std;

int solution(string my_string) {
    int answer = 0;
    for(char c : my_string){
        int num=c-'0';
        if(num>=0 && num<=9){
            answer+=num;
        }
    }
    return answer;
}