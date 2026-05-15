#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int solution(vector<int> array, int n) {
    int answer = 0;
    int big=101;
    sort(array.begin(),array.end());
    int compare=0;
    for(int i=0;i<array.size();i++){
        if(n>array[i]) compare=n-array[i];
        else compare=array[i]-n; 
        if(big>compare){answer=array[i];big=compare;}
    }
    
    return answer;
}