#include <string>
#include <vector>
using namespace std;

string solution(string s) {

    string answer = "";

    vector<pair<char,int>> v(256, {' ',0});

    for(char c : s){
        v[c].first = c;
        v[c].second++;
    }

    for(int i=0; i<256; i++){
        if(v[i].second == 1){
            answer += v[i].first;
        }
    }

    return answer;
}