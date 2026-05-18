#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
long long solution(string numbers) {
    long long answer = 0;
    string plus="";
    string ctos="";
    map<string,char>m;
    m["zero"]='0';
    m["one"]='1';
    m["two"]='2';
    m["three"]='3';
    m["four"]='4';
    m["five"]='5';
    m["six"]='6';
    m["seven"]='7';
    m["eight"]='8';
    m["nine"]='9';
    for(char c:numbers){
        //위치 주의 마지막 하나 씹힘
        plus+=c;
        if(m[plus]-'0'>=0 && m[plus]-'0'<=9){ctos+=m[plus];plus="";}
    }
    answer=stoll(ctos);
    return answer;
}