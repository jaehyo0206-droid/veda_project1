#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> array, int height) {
    int answer = 0;
    //int cnt_small=0;
    //sort(array.begin(),array.end());
    for(int n : array){
        if(n>height)answer++;
    }
    return answer;
}