#include <string>
#include <vector>

using namespace std;

int solution(vector<int> common) {
    int answer;
    int is_c=common[1]-common[0];
    int diff = common[2]-common[1];
    if(is_c ==diff)//이건 등차
        answer=common[common.size()-1]+diff;
    else answer=common[common.size()-1]*(common[1]/common[0]);
    return answer;
    
}