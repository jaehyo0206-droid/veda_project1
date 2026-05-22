#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> array, int n) {
    int answer = 0;
    sort(array.begin(),array.end());
    for(int num : array){
        if(num==n)answer++;
        else if(num>n) break;
    }
    return answer;
}