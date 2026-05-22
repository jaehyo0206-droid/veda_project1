#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> numbers) {
    sort(numbers.begin(),numbers.end());
    int max =numbers[0] * numbers[1];
    for(int i=0;i<numbers.size();i++){
        for(int j=i+1;j<numbers.size();j++){
            if(numbers[i]*numbers[j]>max)max=numbers[i]*numbers[j];
        }
    }
    return max;
}