#include <string>
#include <vector>
using namespace std;
vector<int> solution(vector<int> numbers, string direction) {
    int len=numbers.size();
    vector<int> answer;
    
    if(direction=="left"){
        for(int i=1;i<len;i++)answer.push_back(numbers[i]);
        answer.push_back(numbers[0]); //맨 앞 원소를 맨 뒤로
    }
    
    if(direction=="right"){
        answer.push_back(numbers[numbers.size()-1]); //맨 마지막 원소가 앞으로
        for(int i=0;i<len-1;i++)answer.push_back(numbers[i]);
    }
    
    return answer;
}