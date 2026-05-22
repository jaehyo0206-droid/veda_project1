#include <string>
#include <vector>
using namespace std;
vector<string> solution(string my_str, int n) {
    vector<string> answer;
    string a=" ";
    int start=0;
    int cnt=0;
    if (my_str.length()%n==0)cnt=(my_str.length()/n);
    else cnt=(my_str.length()/n)+1;
    while(cnt--){
        answer.push_back(my_str.substr(start,n));
        start+=n;
    }
    return answer;
}