#include <string>
#include <vector>
using namespace std;
string solution(string my_string) {
    string answer = "";
    char gather[5]={'a','e','i','o','u'};
    for(char c : my_string){
        bool is_gather=0; 
        for(int i=0;i<5;i++)if(c==gather[i]){is_gather=1;}//모음이 맞다면
        if(!is_gather)answer+=c;
    }
    return answer;
}