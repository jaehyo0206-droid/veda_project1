#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(pair<int,int>a, pair<int,int>b){
     // distance가 다르면
    if(a.first != b.first) return a.first < b.first;
    return a.second > b.second;
}
vector<int> solution(vector<int> numlist, int n) {
    vector<pair<int,int>>v;
    vector<int> answer;
    
    for(int i=0;i<numlist.size();i++){
        if(n>numlist[i]){
            int dis =n-numlist[i];
            v.push_back({dis,numlist[i]}); //거리, 값
        }
        else if(n<numlist[i]){
            int dis =numlist[i]-n;
            v.push_back({dis,numlist[i]}); //거리, 값
        }
        else if(n-numlist[i]==0)v.push_back({0,n});
    }//for문
    sort(v.begin(),v.end(),cmp);
    for(auto a:v)
        answer.push_back(a.second);
    return answer;
}