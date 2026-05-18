#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> array) {
    vector<int> answer(2);
    answer[0]=0;
    answer[1]=0;
    int cmp=0;
    for(int i=0; i<array.size();i++){
        if(cmp<array[i]){
            answer[0]=array[i];
            answer[1]=i;
            cmp=array[i];
        }
    }
    return answer;
}