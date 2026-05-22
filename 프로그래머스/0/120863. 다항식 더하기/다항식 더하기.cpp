#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string solution(string polynomial) {
    string answer = "";
    //find함수
    stringstream ss (polynomial);
    string temp="";
    string get="";
    int x_val=0;
    int n_val=0;
    while(ss>>temp){
       if(temp.find("x")!=string::npos){ //x를 찾았다면
           //x의 상수항이 1일 때
           if(temp.find("x")==0){x_val+=1;continue;} 
           //x의 상수항 더하기
           for(int i=0;i<temp.find("x");i++)get+=temp[i];
           x_val+=stoi(get);
           get="";
       }//if문
       else if (temp=="+")continue;
       else{ //그냥 상수면
            for(int i=0;i<temp.size();i++)get+=temp[i];
            n_val+=stoi(get);
           get="";
       }
    }//while 문
  if(x_val > 0){
    if(x_val == 1) answer += "x";
    else answer += to_string(x_val) + "x";
}

if(n_val > 0){
    if(!answer.empty()) answer += " + ";
    answer += to_string(n_val);
}  return answer;
}