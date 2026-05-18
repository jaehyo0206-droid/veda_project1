#include <string>
#include <vector>
#include <map>
using namespace std;
string solution(string my_string, int num1, int num2) {
    string answer = "";
    int cnt=0;
    map<int,char>m;
    for(char c : my_string){
    if(cnt==num1){m[num2]=c;}
    else if(cnt==num2){m[num1]=c;}
    cnt++;
    }
    for(int i=0;i<my_string.size();i++){
        if(m[i]!=NULL){answer+=m[i];continue;}
        answer+=my_string[i];
    }    
    return answer;
}