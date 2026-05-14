#include <string>
#include <vector>
using namespace std;    
vector<vector<int>> solution(vector<int>num_list, int n) {
    vector<vector<int>> answer;
    int inx=0;
    int len=num_list.size()/n;
    
    for(int i=0;i<len;i++){
        vector<int>v;
        for(int j=0;j<n;j++){
            v.push_back(num_list[inx++]);
        }//안쪽 for문
        answer.push_back(v);
    }
    return answer;
}