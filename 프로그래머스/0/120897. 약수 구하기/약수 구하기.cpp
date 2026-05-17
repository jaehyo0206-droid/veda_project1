#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<int> solution(int n) {
    vector<int> answer;
    for(int i=1; i<=sqrt(n);i++){
        if(n%i==0){
            answer.push_back(i);
            if(i!=sqrt(n)){
                answer.push_back(n/i);
            }
        }
    }
    sort(answer.begin(),answer.end());
    return answer;
}