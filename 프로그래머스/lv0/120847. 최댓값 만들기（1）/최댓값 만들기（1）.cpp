#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> numbers) {
    int answer = 0;
    int idx=numbers.size()-1;
    sort(numbers.begin(),numbers.end());
    answer=numbers[idx]*numbers[idx-1];
    return answer;
}