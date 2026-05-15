#include <string>
#include <vector>
#include <map>
using namespace std;

string solution(string my_string) {
    map<char,bool> m;
    string answer = "";
    for(char c : my_string){
        if(m.find(c)!=m.end())continue;
        m[c]=true;
        answer+=c;
    }
    return answer;
}