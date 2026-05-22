#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> array) {
    int answer = 0;
    for(int i=0; i<array.size();i++){
        string st=to_string(array[i]);
        for(char c : st){
            if(c=='7')answer++;
        }
    }
    return answer;
}